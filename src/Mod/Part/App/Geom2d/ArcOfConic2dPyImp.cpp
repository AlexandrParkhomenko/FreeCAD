/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <Geom2d_Conic.hxx>
# include <Geom2d_TrimmedCurve.hxx>

#include "Mod/Part/App/Geometry2d.h"
#include "Mod/Part/App/Geom2d/ArcOfConic2dPy.h"
#include <Mod/Part/App/Geom2d/ArcOfConic2dPy.cpp>
#include "Mod/Part/App/OCCError.h"

#include "Base/GeometryPyCXX.h"

using namespace Part;

// returns a string which represents the object e.g. when printed in python
std::string ArcOfConic2dPy::representation(void) const
{
    return "<Arc of conic2d object>";
}

PyObject *ArcOfConic2dPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // never create such objects with the constructor
    PyErr_SetString(PyExc_RuntimeError,
        "You cannot create an instance of the abstract class 'ArcOfConic2d'.");
    return 0;
}

// constructor method
int ArcOfConic2dPy::PyInit(PyObject* /*args*/, PyObject* /*kwds*/)
{
    return -1;
}

Py::Object ArcOfConic2dPy::getLocation(void) const
{
    Base::Vector2d loc = getGeom2dArcOfConicPtr()->getLocation();

    Py::Module module("__FreeCADBase__");
    Py::Callable method(module.getAttr("Vector2d"));
    Py::Tuple arg(2);
    arg.setItem(0, Py::Float(loc.x));
    arg.setItem(1, Py::Float(loc.y));
    return method.apply(arg);
}

void  ArcOfConic2dPy::setLocation(Py::Object arg)
{
    Base::Vector2d loc = Py::toVector2d(arg.ptr());
    getGeom2dArcOfConicPtr()->setLocation(loc);
}

Py::Float ArcOfConic2dPy::getEccentricity(void) const
{
    Handle(Geom2d_TrimmedCurve) curve = Handle(Geom2d_TrimmedCurve)::DownCast(getGeom2dArcOfConicPtr()->handle());
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(curve->BasisCurve());
    return Py::Float(conic->Eccentricity());
}

Py::Object ArcOfConic2dPy::getXAxis(void) const
{
    Handle(Geom2d_TrimmedCurve) curve = Handle(Geom2d_TrimmedCurve)::DownCast(getGeom2dArcOfConicPtr()->handle());
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(curve->BasisCurve());
    gp_Dir2d xdir = conic->XAxis().Direction();
    Py::Module module("__FreeCADBase__");
    Py::Callable method(module.getAttr("Vector2d"));
    Py::Tuple arg(2);
    arg.setItem(0, Py::Float(xdir.X()));
    arg.setItem(1, Py::Float(xdir.Y()));
    return method.apply(arg);
}

void  ArcOfConic2dPy::setXAxis(Py::Object arg)
{
    Handle(Geom2d_TrimmedCurve) curve = Handle(Geom2d_TrimmedCurve)::DownCast(getGeom2dArcOfConicPtr()->handle());
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(curve->BasisCurve());
    Base::Vector2d dir = Py::toVector2d(arg.ptr());
    gp_Ax2d xaxis = conic->XAxis();
    xaxis.SetDirection(gp_Dir2d(dir.x, dir.y));
    conic->SetXAxis(xaxis);
}

Py::Object ArcOfConic2dPy::getYAxis(void) const
{
    Handle(Geom2d_TrimmedCurve) curve = Handle(Geom2d_TrimmedCurve)::DownCast(getGeom2dArcOfConicPtr()->handle());
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(curve->BasisCurve());
    gp_Dir2d ydir = conic->YAxis().Direction();
    Py::Module module("__FreeCADBase__");
    Py::Callable method(module.getAttr("Vector2d"));
    Py::Tuple arg(2);
    arg.setItem(0, Py::Float(ydir.X()));
    arg.setItem(1, Py::Float(ydir.Y()));
    return method.apply(arg);
}

void  ArcOfConic2dPy::setYAxis(Py::Object arg)
{
    Handle(Geom2d_TrimmedCurve) curve = Handle(Geom2d_TrimmedCurve)::DownCast(getGeom2dArcOfConicPtr()->handle());
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(curve->BasisCurve());
    Base::Vector2d dir = Py::toVector2d(arg.ptr());
    gp_Ax2d yaxis = conic->YAxis();
    yaxis.SetDirection(gp_Dir2d(dir.x, dir.y));
    conic->SetYAxis(yaxis);
}

PyObject *ArcOfConic2dPy::getCustomAttributes(const char* ) const
{
    return 0;
}

int ArcOfConic2dPy::setCustomAttributes(const char* , PyObject *)
{
    return 0; 
}
