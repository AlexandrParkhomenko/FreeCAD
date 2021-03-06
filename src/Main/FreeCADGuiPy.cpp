/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include <FCConfig.h>

#include <QApplication>
#include <QIcon>
#include <QThread>
// FreeCAD Base header
#include <CXX/WrapPython.h>
#include "Base/Exception.h"
#include "Base/Factory.h"
#include "Base/Interpreter.h"
#include "App/Application.h"
#include "Gui/Application.h"
#include "Gui/BitmapFactory.h"
#include "Gui/MainWindow.h"
#include "Gui/SoFCDB.h"
#include "Gui/Quarter/Quarter.h"
#include <Inventor/SoDB.h>

static
QWidget* setupMainWindow();

class GUIThread : public QThread
{
public:
    GUIThread()
    {
    }
    void run()
    {
        static int argc = 0;
        static char **argv = {0};
        QApplication app(argc, argv);
        if (setupMainWindow()) {
            app.exec();
        }
    }
};

#if defined(Q_OS_WIN)
HHOOK hhook;

LRESULT CALLBACK
FilterProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (qApp)
        qApp->sendPostedEvents(0, -1); // special DeferredDelete
    return CallNextHookEx(hhook, nCode, wParam, lParam);
}
#endif

static PyObject *
FreeCADGui_showMainWindow(PyObject * /*self*/, PyObject *args)
{
    PyObject* inThread = Py_False;
    if (!PyArg_ParseTuple(args, "|O!", &PyBool_Type, &inThread))
        return NULL;

    static GUIThread* thr = 0;
    if (!qApp) {
        if (PyObject_IsTrue(inThread)) {
            if (!thr) thr = new GUIThread();
            thr->start();
        }
        else {
#if defined(Q_OS_WIN)
            static int argc = 0;
            static char **argv = {0};
            (void)new QApplication(argc, argv);
            // When QApplication is constructed
            hhook = SetWindowsHookEx(WH_GETMESSAGE,
                FilterProc, 0, GetCurrentThreadId());
#elif !defined(QT_NO_GLIB)
            static int argc = 0;
            static char **argv = {0};
            (void)new QApplication(argc, argv);
#else
            PyErr_SetString(PyExc_RuntimeError, "Must construct a QApplication before a QPaintDevice\n");
            return NULL;
#endif
        }
    }
    else if (!qobject_cast<QApplication*>(qApp)) {
        PyErr_SetString(PyExc_RuntimeError, "Cannot create widget when no GUI is being used\n");
        return NULL;
    }

    if (!thr) {
        if (!setupMainWindow()) {
            PyErr_SetString(PyExc_RuntimeError, "Cannot create main window\n");
            return NULL;
        }
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
FreeCADGui_exec_loop(PyObject * /*self*/, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    if (!qApp) {
        PyErr_SetString(PyExc_RuntimeError, "Must construct a QApplication before a QPaintDevice\n");
        return NULL;
    }
    else if (!qobject_cast<QApplication*>(qApp)) {
        PyErr_SetString(PyExc_RuntimeError, "Cannot create widget when no GUI is being used\n");
        return NULL;
    }

    qApp->exec();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
FreeCADGui_setupWithoutGUI(PyObject * /*self*/, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    if (!Gui::Application::Instance) {
        static Gui::Application *app = new Gui::Application(false);
        Q_UNUSED(app);
    }
    else {
        PyErr_SetString(PyExc_RuntimeError, "FreeCADGui already initialized");
        return 0;
    }

    if (!SoDB::isInitialized()) {
        // init the Inventor subsystem
        SoDB::init();
        SIM::Coin3D::Quarter::Quarter::init();
    }
    if (!Gui::SoFCDB::isInitialized()) {
        Gui::SoFCDB::init();
    }

    Py_INCREF(Py_None);
    return Py_None;
}

struct PyMethodDef FreeCADGui_methods[] = { 
    {"showMainWindow",FreeCADGui_showMainWindow,METH_VARARGS,
     "showMainWindow() -- Show the main window\n"
     "If no main window does exist one gets created"},
    {"exec_loop",FreeCADGui_exec_loop,METH_VARARGS,
     "exec_loop() -- Starts the event loop\n"
     "Note: this will block the call until the event loop has terminated"},
    {"setupWithoutGUI",FreeCADGui_setupWithoutGUI,METH_VARARGS,
     "setupWithoutGUI() -- Uses this module without starting\n"
     "an event loop or showing up any GUI\n"},
    {NULL, NULL, 0, NULL}  /* sentinel */
};

static
QWidget* setupMainWindow()
{
    if (!Gui::Application::Instance) {
        static Gui::Application *app = new Gui::Application(true);
        Q_UNUSED(app);
    }

    if (!Gui::MainWindow::getInstance()) {
        static bool hasMainWindow = false;
        if (hasMainWindow) {
            // if a main window existed and has been deleted it's not supported
            // to re-create it
            return 0;
        }

        Base::PyGILStateLocker lock;
        PyObject* input = PySys_GetObject("stdin");
        Gui::MainWindow *mw = new Gui::MainWindow();
        mw->setAttribute(Qt::WA_DeleteOnClose);
        hasMainWindow = true;

        QIcon icon = qApp->windowIcon();
        if (icon.isNull())
            qApp->setWindowIcon(Gui::BitmapFactory().pixmap(App::Application::Config()["AppIcon"].c_str()));
        mw->setWindowIcon(qApp->windowIcon());
        QString appName = qApp->applicationName();
        if (!appName.isEmpty())
            mw->setWindowTitle(appName);
        else
            mw->setWindowTitle(QString(App::Application::Config()["ExeName"].c_str()));

        if (!SoDB::isInitialized()) {
            // init the Inventor subsystem
            SoDB::init();
            SIM::Coin3D::Quarter::Quarter::init();
            Gui::SoFCDB::init();
        }

        static bool init = false;
        if (!init) {
            try {
                Base::Console().Log("Run Gui init script\n");
                Base::Interpreter().runString(Base::ScriptFactory().ProduceScript("FreeCADGuiInit"));
            }
            catch (const Base::Exception& e) {
                PyErr_Format(Base::BaseExceptionFreeCADError, "Error in FreeCADGuiInit.py: %s\n", e.what());
                return 0;
            }
            init = true;
        }

        qApp->setActiveWindow(mw);

        // Activate the correct workbench
        std::string start = App::Application::Config()["StartWorkbench"];
        Base::Console().Log("Init: Activating default workbench %s\n", start.c_str());
        start = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")->
                               GetASCII("AutoloadModule", start.c_str());
        // if the auto workbench is not visible then force to use the default workbech
        // and replace the wrong entry in the parameters
        QStringList wb = Gui::Application::Instance->workbenches();
        if (!wb.contains(QString(start.c_str()))) {
            start = App::Application::Config()["StartWorkbench"];
            App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/General")->
                                  SetASCII("AutoloadModule", start.c_str());
        }

        Gui::Application::Instance->activateWorkbench(start.c_str());
        mw->loadWindowSettings();
        PySys_SetObject("stdin", input);
    }
    else {
        Gui::getMainWindow()->show();
    }

    return Gui::getMainWindow();
}

PyMOD_INIT_FUNC(FreeCADGui)
{
    try {
        Base::Interpreter().loadModule("FreeCAD");
        App::Application::Config()["AppIcon"] = "freecad-path";
        // it's possible that the GUI is already initialized when the Gui version of the executable
        // is started in command mode
        if (Base::Type::fromName("Gui::BaseView").isBad())
            Gui::Application::initApplication();
        static struct PyModuleDef FreeCADGuiModuleDef = {
            PyModuleDef_HEAD_INIT,
            "FreeCADGui", "FreeCAD GUI module\n", -1,
            FreeCADGui_methods,
            NULL, NULL, NULL, NULL
        };
        PyObject* module = PyModule_Create(&FreeCADGuiModuleDef);
        return module;

    }
    catch (const Base::Exception& e) {
        PyErr_Format(PyExc_ImportError, "%s\n", e.what());
    }
    catch (...) {
        PyErr_SetString(PyExc_ImportError, "Unknown runtime error occurred");
    }
    return 0;

}

