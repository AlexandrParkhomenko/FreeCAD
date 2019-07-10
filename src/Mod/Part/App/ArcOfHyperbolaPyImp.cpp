/***************************************************************************
 *   Copyright (c) 2014 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com      *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <gp_Hypr.hxx>
# include <Geom_Hyperbola.hxx>
# include <GC_MakeArcOfHyperbola.hxx>
# include <GC_MakeHyperbola.hxx>
# include <Geom_TrimmedCurve.hxx>

#include "Geometry.h"
#include "Mod/Part/App/ArcOfHyperbolaPy.h"
#include <Mod/Part/App/ArcOfHyperbolaPy.cpp>
#include "Mod/Part/App/HyperbolaPy.h"
#include "OCCError.h"

#include "Base/GeometryPyCXX.h"
#include "Base/VectorPy.h"

using namespace Part;

extern const char* gce_ErrorStatusText(gce_ErrorType et);

// returns a string which represents the object e.g. when printed in python
std::string ArcOfHyperbolaPy::representation(void) const
{
    Handle(Geom_TrimmedCurve) trim = Handle(Geom_TrimmedCurve)::DownCast
        (getGeomArcOfHyperbolaPtr()->handle());
    Handle(Geom_Hyperbola) hyperbola = Handle(Geom_Hyperbola)::DownCast(trim->BasisCurve());

    gp_Ax1 axis = hyperbola->Axis();
    gp_Dir dir = axis.Direction();
    gp_Pnt loc = axis.Location();
    Standard_Real fMajRad = hyperbola->MajorRadius();
    Standard_Real fMinRad = hyperbola->MinorRadius();
    Standard_Real u1 = trim->FirstParameter();
    Standard_Real u2 = trim->LastParameter();
    
    gp_Dir normal = hyperbola->Axis().Direction();
    gp_Dir xdir = hyperbola->XAxis().Direction();
    
    gp_Ax2 xdirref(loc, normal); // this is a reference XY for the hyperbola
    
    Standard_Real fAngleXU = -xdir.AngleWithRef(xdirref.XDirection(),normal);
    

    std::stringstream str;
    str << "ArcOfHyperbola (";
    str << "MajorRadius : " << fMajRad << ", "; 
    str << "MinorRadius : " << fMinRad << ", ";
    str << "AngleXU : " << fAngleXU << ", ";
    str << "Position : (" << loc.X() << ", "<< loc.Y() << ", "<< loc.Z() << "), "; 
    str << "Direction : (" << dir.X() << ", "<< dir.Y() << ", "<< dir.Z() << "), "; 
    str << "Parameter : (" << u1 << ", " << u2 << ")"; 
    str << ")";

    return str.str();
}

PyObject *ArcOfHyperbolaPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of ArcOfHyperbolaPy and the Twin object 
    return new ArcOfHyperbolaPy(new GeomArcOfHyperbola);
}

// constructor method
int ArcOfHyperbolaPy::PyInit(PyObject* args, PyObject* /*kwds*/)
{
    PyObject* o;
    double u1, u2;
    PyObject *sense=Py_True;
    if (PyArg_ParseTuple(args, "O!dd|O!", &(Part::HyperbolaPy::Type), &o, &u1, &u2, &PyBool_Type, &sense)) {
        try {
            Handle(Geom_Hyperbola) hyperbola = Handle(Geom_Hyperbola)::DownCast
                (static_cast<HyperbolaPy*>(o)->getGeomHyperbolaPtr()->handle());
            GC_MakeArcOfHyperbola arc(hyperbola->Hypr(), u1, u2, PyObject_IsTrue(sense) ? Standard_True : Standard_False);
            if (!arc.IsDone()) {
                PyErr_SetString(PartExceptionOCCError, gce_ErrorStatusText(arc.Status()));
                return -1;
            }

            getGeomArcOfHyperbolaPtr()->setHandle(arc.Value());
            return 0;
        }
        catch (Standard_Failure& e) {
            PyErr_SetString(PartExceptionOCCError, e.GetMessageString());
            return -1;
        }
        catch (...) {
            PyErr_SetString(PartExceptionOCCError, "creation of arc failed");
            return -1;
        }
    }
    
    // All checks failed
    PyErr_SetString(PyExc_TypeError,
        "ArcOfHyperbola constructor expects an hyperbola curve and a parameter range");
    return -1;
}

Py::Float ArcOfHyperbolaPy::getMajorRadius(void) const
{
    return Py::Float(getGeomArcOfHyperbolaPtr()->getMajorRadius()); 
}

void  ArcOfHyperbolaPy::setMajorRadius(Py::Float arg)
{
    getGeomArcOfHyperbolaPtr()->setMajorRadius((double)arg);
}

Py::Float ArcOfHyperbolaPy::getMinorRadius(void) const
{
    return Py::Float(getGeomArcOfHyperbolaPtr()->getMinorRadius()); 
}

void  ArcOfHyperbolaPy::setMinorRadius(Py::Float arg)
{
    getGeomArcOfHyperbolaPtr()->setMinorRadius((double)arg);
}

Py::Object ArcOfHyperbolaPy::getHyperbola(void) const
{
    Handle(Geom_TrimmedCurve) trim = Handle(Geom_TrimmedCurve)::DownCast
        (getGeomArcOfHyperbolaPtr()->handle());
    Handle(Geom_Hyperbola) hyperbola = Handle(Geom_Hyperbola)::DownCast(trim->BasisCurve());
    return Py::Object(new HyperbolaPy(new GeomHyperbola(hyperbola)), true);
}

PyObject *ArcOfHyperbolaPy::getCustomAttributes(const char* ) const
{
    return 0;
}

int ArcOfHyperbolaPy::setCustomAttributes(const char* , PyObject *)
{
    return 0; 
}
