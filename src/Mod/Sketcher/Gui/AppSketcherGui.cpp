/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel (juergen.riegel@web.de)              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include "FCConfig.h"

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

#include "Base/Console.h"
#include "Base/Interpreter.h"
#include "Gui/Application.h"
#include "Gui/WidgetFactory.h"
#include "Workbench.h"
#include "ViewProviderSketch.h"
#include "ViewProviderPython.h"
#include "SoDatumLabel.h"
#include "SoZoomTranslation.h"
#include "SketcherSettings.h"
#include "PropertyConstraintListItem.h"


// create the commands
void CreateSketcherCommands(void);
void CreateSketcherCommandsCreateGeo(void);
void CreateSketcherCommandsConstraints(void);
void CreateSketcherCommandsConstraintAccel(void);
void CreateSketcherCommandsAlterGeo(void);
void CreateSketcherCommandsBSpline(void);
void CreateSketcherCommandsVirtualSpace(void);

void loadSketcherResource()
{
    // add resources and reloads the translators
    Q_INIT_RESOURCE(Sketcher);
}


namespace SketcherGui {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("SketcherGui")
    {
        initialize("This module is the SketcherGui module."); // register with Python
    }

    virtual ~Module() {}

private:
};

PyObject* initModule()
{
    return (new Module)->module().ptr();
}

} // namespace SketcherGui

/* Python entry */
PyMOD_INIT_FUNC(SketcherGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(0);
    }
    try {
        Base::Interpreter().runString("import PartGui");
        Base::Interpreter().runString("import Sketcher");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(0);
    }

    PyObject* mod = SketcherGui::initModule();
    Base::Console().Log("Loading GUI of Sketcher module... done\n");

    // instantiating the commands
    CreateSketcherCommands();
    CreateSketcherCommandsCreateGeo();
    CreateSketcherCommandsConstraints();
    CreateSketcherCommandsAlterGeo();
    CreateSketcherCommandsConstraintAccel();
    CreateSketcherCommandsBSpline();
    CreateSketcherCommandsVirtualSpace();

    SketcherGui::Workbench::init();

    // init objects
    SketcherGui::ViewProviderSketch         ::init();
    SketcherGui::ViewProviderPython         ::init();
    SketcherGui::ViewProviderCustom         ::init();
    SketcherGui::ViewProviderCustomPython   ::init();
    SketcherGui::SoDatumLabel               ::initClass();
    SketcherGui::SoZoomTranslation          ::initClass();
    SketcherGui::PropertyConstraintListItem ::init();

    (void)new Gui::PrefPageProducer<SketcherGui::SketcherSettings>        ( QT_TRANSLATE_NOOP("QObject","Sketcher") );
    (void)new Gui::PrefPageProducer<SketcherGui::SketcherSettingsColors>  ( QT_TRANSLATE_NOOP("QObject","Sketcher") );

     // add resources and reloads the translators
    loadSketcherResource();

    PyMOD_Return(mod);
}
