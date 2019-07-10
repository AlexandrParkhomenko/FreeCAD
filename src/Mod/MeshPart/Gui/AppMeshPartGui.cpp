/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel (juergen.riegel@web.de)              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include "FCConfig.h"

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

#include "Base/Console.h"
#include "Gui/Application.h"
#include "CurveOnMesh.h"
#include "Workbench.h"

// use a different name to CreateCommand()
void CreateMeshPartCommands(void);

void loadMeshPartResource()
{
    // add resources and reloads the translators
    Q_INIT_RESOURCE(MeshPart);
}

namespace MeshPartGui {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("MeshPartGui")
    {
        initialize("This module is the MeshPartGui module."); // register with Python
    }

    virtual ~Module() {}

private:
};

PyObject* initModule()
{
    return (new Module)->module().ptr();
}

} // namespace MeshPartGui


/* Python entry */
PyMOD_INIT_FUNC(MeshPartGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(0);
    }

    PyObject* mod = MeshPartGui::initModule();
    Base::Console().Log("Loading GUI of MeshPart module... done\n");

    // instantiating the commands
    CreateMeshPartCommands();
    MeshPartGui::Workbench                  ::init();
    MeshPartGui::ViewProviderCurveOnMesh    ::init();

     // add resources and reloads the translators
    loadMeshPartResource();

    PyMOD_Return(mod);
}
