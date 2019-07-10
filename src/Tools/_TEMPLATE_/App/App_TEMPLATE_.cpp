/***************************************************************************
 *   Copyright (c) YEAR YOUR NAME         <Your e-mail address>            *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include "FCConfig.h"

#include "Base/Console.h"
#include "Base/PyObjectBase.h"

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>


namespace _TEMPLATE_ {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("_TEMPLATE_")
    {
        initialize("This module is the _TEMPLATE_ module."); // register with Python
    }

    virtual ~Module() {}

private:
};

PyObject* initModule()
{
    return (new Module)->module().ptr();
}


} // namespace _TEMPLATE_


/* Python entry */
PyMOD_INIT_FUNC(_TEMPLATE_)
{
    // ADD YOUR CODE HERE
    //
    //
    PyObject* mod = _TEMPLATE_::initModule();
    Base::Console().Log("Loading _TEMPLATE_ module... done\n");
    PyMOD_Return(mod);
}
