/***************************************************************************
 *   Copyright (c) 2019 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com      *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <sstream>

#include "Base/GeometryPyCXX.h"
#include "Base/VectorPy.h"

#include "Geometry.h"
#include "BoundedCurvePy.h"
#include "BoundedCurvePy.cpp"


using namespace Part;

// returns a string which represents the object e.g. when printed in python
std::string BoundedCurvePy::representation(void) const
{
    return "<Curve object>";
}

PyObject *BoundedCurvePy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // never create such objects with the constructor
    PyErr_SetString(PyExc_RuntimeError,
                    "You cannot create an instance of the abstract class 'BoundedCurve'.");
    return 0;
}

// constructor method
int BoundedCurvePy::PyInit(PyObject* /*args*/, PyObject* /*kwd*/)
{
    return 0;
}

Py::Object BoundedCurvePy::getStartPoint(void) const
{
    return Py::Vector(getGeomBoundedCurvePtr()->getStartPoint());
}

Py::Object BoundedCurvePy::getEndPoint(void) const
{
    return Py::Vector(getGeomBoundedCurvePtr()->getEndPoint());
}

PyObject *BoundedCurvePy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int BoundedCurvePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
