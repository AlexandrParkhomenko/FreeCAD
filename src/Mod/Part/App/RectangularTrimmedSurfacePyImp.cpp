/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <Geom_RectangularTrimmedSurface.hxx>
# include <Geom_Curve.hxx>

#include "Mod/Part/App/Geometry.h"
#include "OCCError.h"

// inclusion of the generated files (generated out of RectangularTrimmedSurfacePy.xml)
#include "RectangularTrimmedSurfacePy.h"
#include "RectangularTrimmedSurfacePy.cpp"
#include "GeometryCurvePy.h"

using namespace Part;

// returns a string which represents the object e.g. when printed in python
std::string RectangularTrimmedSurfacePy::representation(void) const
{
    return std::string("<RectangularTrimmedSurface object>");
}

PyObject *RectangularTrimmedSurfacePy::PyMake(struct _typeobject *, PyObject *, PyObject *)
{
    // create a new instance of RectangularTrimmedSurfacePy and the Twin object 
    return new RectangularTrimmedSurfacePy(new GeomTrimmedSurface);
}

// constructor method
int RectangularTrimmedSurfacePy::PyInit(PyObject* args, PyObject* /*kwd*/)
{
    PyObject* surf;
    double u1,u2,v1,v2;
    PyObject *usense=Py_True, *vsense=Py_True;
    if (PyArg_ParseTuple(args, "O!dddd|O!O!",&(Part::GeometrySurfacePy::Type),&surf,
                         &u1,&u2,&v1,&v2,&PyBool_Type,&usense,&PyBool_Type,&vsense)) {
        getGeomTrimmedSurfacePtr()->setHandle(new Geom_RectangularTrimmedSurface(
            Handle(Geom_Surface)::DownCast(static_cast<GeometrySurfacePy*>(surf)->
                getGeomSurfacePtr()->handle()),
            u1, u2, v1, v2,
            PyObject_IsTrue(usense) ? Standard_True : Standard_False,
            PyObject_IsTrue(vsense) ? Standard_True : Standard_False
        ));
        return 0;
    }

    PyErr_Clear();
    double param1,param2;
    PyObject *utrim=Py_False, *sense=Py_True;
    if (PyArg_ParseTuple(args, "O!ddO!|O!",&(Part::GeometrySurfacePy::Type),&surf,
                         &param1,&param2,&PyBool_Type,&utrim,&PyBool_Type,&sense)) {
        Standard_Boolean UTrim = PyObject_IsTrue(utrim) ? Standard_True : Standard_False;
        Standard_Boolean Sense = PyObject_IsTrue(sense) ? Standard_True : Standard_False;
        getGeomTrimmedSurfacePtr()->setHandle(new Geom_RectangularTrimmedSurface(
            Handle(Geom_Surface)::DownCast(static_cast<GeometrySurfacePy*>(surf)->
                getGeomSurfacePtr()->handle()),
            param1, param2, UTrim, Sense
        ));
        return 0;
    }

    PyErr_SetString(PartExceptionOCCError, "A surface and the trim parameters must be given");
    return -1;
}

PyObject* RectangularTrimmedSurfacePy::uIso(PyObject * args)
{
    double v;
    if (!PyArg_ParseTuple(args, "d", &v))
        return 0;

    try {
        Handle(Geom_Surface) surf = Handle(Geom_Surface)::DownCast
            (getGeometryPtr()->handle());
        Handle(Geom_Curve) c = surf->UIso(v);
        if (c->IsKind(STANDARD_TYPE(Geom_TrimmedCurve))) {
            Handle(Geom_TrimmedCurve) aCurve = Handle(Geom_TrimmedCurve)::DownCast(c);
            return new GeometryCurvePy(new GeomTrimmedCurve(aCurve));
        }

        PyErr_Format(PyExc_NotImplementedError, "Iso curve is of type '%s'",
            c->DynamicType()->Name());
        return 0;
    }
    catch (Standard_Failure& e) {

        PyErr_SetString(PartExceptionOCCError, e.GetMessageString());
        return 0;
    }
}

PyObject* RectangularTrimmedSurfacePy::vIso(PyObject * args)
{
    double v;
    if (!PyArg_ParseTuple(args, "d", &v))
        return 0;

    try {
        Handle(Geom_Surface) surf = Handle(Geom_Surface)::DownCast
            (getGeometryPtr()->handle());
        Handle(Geom_Curve) c = surf->VIso(v);
        if (c->IsKind(STANDARD_TYPE(Geom_TrimmedCurve))) {
            Handle(Geom_TrimmedCurve) aCurve = Handle(Geom_TrimmedCurve)::DownCast(c);
            return new GeometryCurvePy(new GeomTrimmedCurve(aCurve));
        }

        PyErr_Format(PyExc_NotImplementedError, "Iso curve is of type '%s'",
            c->DynamicType()->Name());
        return 0;
    }
    catch (Standard_Failure& e) {

        PyErr_SetString(PartExceptionOCCError, e.GetMessageString());
        return 0;
    }
}

PyObject *RectangularTrimmedSurfacePy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int RectangularTrimmedSurfacePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}
