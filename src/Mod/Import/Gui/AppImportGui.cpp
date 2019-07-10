/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2002                        *   
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 *   Juergen Riegel 2002                                                   *
 ***************************************************************************/



#include "App/Application.h"
#include "Base/Console.h"
#include "Base/Interpreter.h"

#include "Gui/Application.h"

#include "Workbench.h"

// use a different name to CreateCommand()
void CreateImportCommands(void);


namespace ImportGui {
extern PyObject* initModule();
}

PyMOD_INIT_FUNC(ImportGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(0);
    }

    try {
        Base::Interpreter().loadModule("PartGui");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(0);
    }

    PyObject* mod = ImportGui::initModule();
    Base::Console().Log("Loading GUI of Import module... done\n");

    CreateImportCommands();
    ImportGui::Workbench::init();

    PyMOD_Return(mod);
}
