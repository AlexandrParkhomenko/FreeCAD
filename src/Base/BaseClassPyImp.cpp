/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2007     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "BaseClass.h"

// inclusion of the generated files (generated out of BaseClassPy.xml)
#include "BaseClassPy.h"
#include "BaseClassPy.cpp"

using namespace Base;

// returns a string which represent the object e.g. when printed in python
std::string BaseClassPy::representation(void) const
{
    return std::string("<binding object>");
}


PyObject*  BaseClassPy::isDerivedFrom(PyObject *args)
{
    char *name;
    if (!PyArg_ParseTuple(args, "s", &name))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception

    Base::Type type = Base::Type::fromName(name);
    bool v = (type != Base::Type::badType() && getBaseClassPtr()->getTypeId().isDerivedFrom(type));
    return PyBool_FromLong(v ? 1 : 0);
}

PyObject*  BaseClassPy::getAllDerivedFrom(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception
    
    std::vector<Base::Type> ary;
    Base::Type::getAllDerivedFrom(getBaseClassPtr()->getTypeId(), ary);
    Py::List res;
    for (std::vector<Base::Type>::iterator it = ary.begin(); it != ary.end(); ++it)
        res.append(Py::String(it->getName()));
    return Py::new_reference_to(res);
}

Py::String BaseClassPy::getTypeId(void) const
{
    return Py::String(std::string(getBaseClassPtr()->getTypeId().getName()));
}

Py::String BaseClassPy::getModule(void) const
{
    std::string module(getBaseClassPtr()->getTypeId().getName());
    std::string::size_type pos = module.find_first_of("::");

    if (pos != std::string::npos)
        module = std::string(module, 0, pos);
    else
        module.clear();

    return Py::String(module);
}

PyObject *BaseClassPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int BaseClassPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}


