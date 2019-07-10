/***************************************************************************
 *   Copyright (c) 2011 Juergen Riegel                                     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "Axis.h"
#include "GeometryPyCXX.h"

// inclusion of the generated files (generated out of AxisPy.xml)
#include "AxisPy.h"
#include "AxisPy.cpp"

#include "VectorPy.h"
#include "PlacementPy.h"

using namespace Base;

// returns a string which represents the object e.g. when printed in python
std::string AxisPy::representation(void) const
{
    AxisPy::PointerType ptr = reinterpret_cast<AxisPy::PointerType>(_pcTwinPointer);
    std::stringstream str;
    str << "Axis [Base=(";
    str << ptr->getBase().x << ","<< ptr->getBase().y << "," << ptr->getBase().z;
    str << "), Direction=(";
    str << ptr->getDirection().x << ","<< ptr->getDirection().y << "," << ptr->getDirection().z << ")]";

    return str.str();
}

PyObject *AxisPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of AxisPy and the Twin object
    return new AxisPy(new Axis);
}

// constructor method
int AxisPy::PyInit(PyObject* args, PyObject* /*kwd*/)
{
    PyObject* o;
    if (PyArg_ParseTuple(args, "")) {
        return 0;
    }

    PyErr_Clear();
    if (PyArg_ParseTuple(args, "O!", &(Base::AxisPy::Type), &o)) {
        Base::Axis *a = static_cast<Base::AxisPy*>(o)->getAxisPtr();
        *(getAxisPtr()) = *a;
        return 0;
    }

    PyErr_Clear();
    PyObject* d;
    if (PyArg_ParseTuple(args, "O!O", &(Base::VectorPy::Type), &o,
                                      &(Base::VectorPy::Type), &d)) {
        // NOTE: The first parameter defines the base (origin) and the second the direction.
        *getAxisPtr() = Base::Axis(static_cast<Base::VectorPy*>(o)->value(),
                                   static_cast<Base::VectorPy*>(d)->value());
        return 0;
    }

    PyErr_SetString(Base::BaseExceptionFreeCADError, "empty parameter list, axis or base and direction expected");
    return -1;
}

PyObject* AxisPy::move(PyObject * args)
{
    PyObject *vec;
    if (!PyArg_ParseTuple(args, "O!", &(VectorPy::Type), &vec))
        return NULL;
    getAxisPtr()->move(static_cast<VectorPy*>(vec)->value());
    Py_Return;
}

PyObject* AxisPy::multiply(PyObject * args)
{
    PyObject *plm;
    if (!PyArg_ParseTuple(args, "O!", &(PlacementPy::Type), &plm))
        return NULL;
    Axis mult = (*getAxisPtr()) * (*static_cast<PlacementPy*>(plm)->getPlacementPtr());
    return new AxisPy(new Axis(mult));
}

PyObject* AxisPy::copy(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    return new AxisPy(new Axis(*getAxisPtr()));
}

PyObject* AxisPy::reversed(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;
    Base::Axis a = getAxisPtr()->reversed();
    return new AxisPy(new Axis(a));
}

Py::Object AxisPy::getBase(void) const
{
    return Py::Vector(getAxisPtr()->getBase());
}

void AxisPy::setBase(Py::Object arg)
{
    getAxisPtr()->setBase(Py::Vector(arg).toVector());
}

Py::Object AxisPy::getDirection(void) const
{
    return Py::Vector(getAxisPtr()->getDirection());
}

void AxisPy::setDirection(Py::Object arg)
{
    getAxisPtr()->setDirection(Py::Vector(arg).toVector());
}

PyObject *AxisPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int AxisPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

