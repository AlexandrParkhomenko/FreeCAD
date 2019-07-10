/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

#include "ViewProvider.h"
#include "Workbench.h"

#include "Base/Console.h"
#include "Base/Interpreter.h"
#include "Gui/Application.h"
#include "Mod/Points/App/PropertyPointKernel.h"

// use a different name to CreateCommand()
void CreatePointsCommands(void);

void loadPointsResource()
{
    // add resources and reloads the translators
    Q_INIT_RESOURCE(Points);
}

namespace PointsGui {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("PointsGui")
    {
        initialize("This module is the PointsGui module."); // register with Python
    }

    virtual ~Module() {}

private:
};

PyObject* initModule()
{
    return (new Module)->module().ptr();
}

} // namespace PointsGui


/* Python entry */
PyMOD_INIT_FUNC(PointsGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(0);
    }

    // load dependent module
    try {
        Base::Interpreter().loadModule("Points");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(0);
    }

    Base::Console().Log("Loading GUI of Points module... done\n");
    PyObject* mod = PointsGui::initModule();

    // instantiating the commands
    CreatePointsCommands();

    PointsGui::ViewProviderPoints       ::init();
    PointsGui::ViewProviderScattered    ::init();
    PointsGui::ViewProviderStructured   ::init();
    PointsGui::ViewProviderPython       ::init();
    PointsGui::Workbench                ::init();
    Gui::ViewProviderBuilder::add(
        Points::PropertyPointKernel::getClassTypeId(),
        PointsGui::ViewProviderPoints::getClassTypeId());

    // add resources and reloads the translators
    loadPointsResource();

    PyMOD_Return(mod);
}
