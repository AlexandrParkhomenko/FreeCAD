/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <Geom2d_Conic.hxx>

#include "Mod/Part/App/OCCError.h"
#include "Mod/Part/App/Geom2d/Conic2dPy.h"
#include <Mod/Part/App/Geom2d/Conic2dPy.cpp>

#include "Base/GeometryPyCXX.h"

using namespace Part;

// returns a string which represents the object e.g. when printed in python
std::string Conic2dPy::representation(void) const
{
    return "<Conic2d object>";
}

PyObject *Conic2dPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // never create such objects with the constructor
    PyErr_SetString(PyExc_RuntimeError,
        "You cannot create an instance of the abstract class 'Conic2d'.");
    return 0;
}

// constructor method
int Conic2dPy::PyInit(PyObject* /*args*/, PyObject* /*kwds*/)
{
    return 0;
}

Py::Object Conic2dPy::getLocation(void) const
{
    Base::Vector2d loc = getGeom2dConicPtr()->getLocation();

    Py::Module module("__FreeCADBase__");
    Py::Callable method(module.getAttr("Vector2d"));
    Py::Tuple arg(2);
    arg.setItem(0, Py::Float(loc.x));
    arg.setItem(1, Py::Float(loc.y));
    return method.apply(arg);
}

void  Conic2dPy::setLocation(Py::Object arg)
{
    Base::Vector2d loc = Py::toVector2d(arg.ptr());
    getGeom2dConicPtr()->setLocation(loc);
}

Py::Float Conic2dPy::getEccentricity(void) const
{
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(getGeom2dConicPtr()->handle());
    return Py::Float(conic->Eccentricity());
}

Py::Object Conic2dPy::getXAxis(void) const
{
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(getGeom2dConicPtr()->handle());
    gp_Dir2d xdir = conic->XAxis().Direction();
    Py::Module module("__FreeCADBase__");
    Py::Callable method(module.getAttr("Vector2d"));
    Py::Tuple arg(2);
    arg.setItem(0, Py::Float(xdir.X()));
    arg.setItem(1, Py::Float(xdir.Y()));
    return method.apply(arg);
}

void  Conic2dPy::setXAxis(Py::Object arg)
{
    Base::Vector2d dir = Py::toVector2d(arg.ptr());
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(getGeom2dConicPtr()->handle());
    gp_Ax2d xaxis = conic->XAxis();
    xaxis.SetDirection(gp_Dir2d(dir.x, dir.y));
    conic->SetXAxis(xaxis);
}

Py::Object Conic2dPy::getYAxis(void) const
{
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(getGeom2dConicPtr()->handle());
    gp_Dir2d ydir = conic->YAxis().Direction();
    Py::Module module("__FreeCADBase__");
    Py::Callable method(module.getAttr("Vector2d"));
    Py::Tuple arg(2);
    arg.setItem(0, Py::Float(ydir.X()));
    arg.setItem(1, Py::Float(ydir.Y()));
    return method.apply(arg);
}

void  Conic2dPy::setYAxis(Py::Object arg)
{
    Base::Vector2d dir = Py::toVector2d(arg.ptr());
    Handle(Geom2d_Conic) conic = Handle(Geom2d_Conic)::DownCast(getGeom2dConicPtr()->handle());
    gp_Ax2d yaxis = conic->YAxis();
    yaxis.SetDirection(gp_Dir2d(dir.x, dir.y));
    conic->SetYAxis(yaxis);
}

PyObject *Conic2dPy::getCustomAttributes(const char* ) const
{
    return 0;
}

int Conic2dPy::setCustomAttributes(const char* , PyObject *)
{
    return 0; 
}
