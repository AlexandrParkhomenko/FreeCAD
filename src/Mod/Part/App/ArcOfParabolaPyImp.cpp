/***************************************************************************
 *   Copyright (c) 2014 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com      *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <gp_Parab.hxx>
# include <Geom_Parabola.hxx>
# include <GC_MakeArcOfParabola.hxx>
# include <gce_MakeParab.hxx>
# include <Geom_TrimmedCurve.hxx>

#include "Geometry.h"
#include "Mod/Part/App/ArcOfParabolaPy.h"
#include <Mod/Part/App/ArcOfParabolaPy.cpp>
#include "Mod/Part/App/ParabolaPy.h"
#include "OCCError.h"

#include "Base/GeometryPyCXX.h"
#include "Base/VectorPy.h"

using namespace Part;

extern const char* gce_ErrorStatusText(gce_ErrorType et);

// returns a string which represents the object e.g. when printed in python
std::string ArcOfParabolaPy::representation(void) const
{
    Handle(Geom_TrimmedCurve) trim = Handle(Geom_TrimmedCurve)::DownCast
        (getGeomArcOfParabolaPtr()->handle());
    Handle(Geom_Parabola) parabola = Handle(Geom_Parabola)::DownCast(trim->BasisCurve());

    gp_Ax1 axis = parabola->Axis();
    gp_Dir dir = axis.Direction();
    gp_Pnt loc = axis.Location();
    Standard_Real fFocal = parabola->Focal();
    Standard_Real u1 = trim->FirstParameter();
    Standard_Real u2 = trim->LastParameter();
    
    gp_Dir normal = parabola->Axis().Direction();
    gp_Dir xdir = parabola->XAxis().Direction();
    
    gp_Ax2 xdirref(loc, normal); // this is a reference XY for the parabola
    
    Standard_Real fAngleXU = -xdir.AngleWithRef(xdirref.XDirection(),normal);
    

    std::stringstream str;
    str << "ArcOfParabola (";
    str << "Focal : " << fFocal << ", "; 
    str << "AngleXU : " << fAngleXU << ", ";
    str << "Position : (" << loc.X() << ", "<< loc.Y() << ", "<< loc.Z() << "), "; 
    str << "Direction : (" << dir.X() << ", "<< dir.Y() << ", "<< dir.Z() << "), "; 
    str << "Parameter : (" << u1 << ", " << u2 << ")"; 
    str << ")";

    return str.str();
}

PyObject *ArcOfParabolaPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of ArcOfParabolaPy and the Twin object 
    return new ArcOfParabolaPy(new GeomArcOfParabola);
}

// constructor method
int ArcOfParabolaPy::PyInit(PyObject* args, PyObject* /*kwds*/)
{
    PyObject* o;
    double u1, u2;
    PyObject *sense=Py_True;
    if (PyArg_ParseTuple(args, "O!dd|O!", &(Part::ParabolaPy::Type), &o, &u1, &u2, &PyBool_Type, &sense)) {
        try {
            Handle(Geom_Parabola) parabola = Handle(Geom_Parabola)::DownCast
                (static_cast<ParabolaPy*>(o)->getGeomParabolaPtr()->handle());
            GC_MakeArcOfParabola arc(parabola->Parab(), u1, u2, PyObject_IsTrue(sense) ? Standard_True : Standard_False);
            if (!arc.IsDone()) {
                PyErr_SetString(PartExceptionOCCError, gce_ErrorStatusText(arc.Status()));
                return -1;
            }

            getGeomArcOfParabolaPtr()->setHandle(arc.Value());
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
        "ArcOfParabola constructor expects an parabola curve and a parameter range");
    return -1;
}

Py::Float ArcOfParabolaPy::getFocal(void) const
{
    return Py::Float(getGeomArcOfParabolaPtr()->getFocal()); 
}

void  ArcOfParabolaPy::setFocal(Py::Float arg)
{
    getGeomArcOfParabolaPtr()->setFocal((double)arg);
}

Py::Object ArcOfParabolaPy::getParabola(void) const
{
    Handle(Geom_TrimmedCurve) trim = Handle(Geom_TrimmedCurve)::DownCast
        (getGeomArcOfParabolaPtr()->handle());
    Handle(Geom_Parabola) parabola = Handle(Geom_Parabola)::DownCast(trim->BasisCurve());
    return Py::Object(new ParabolaPy(new GeomParabola(parabola)), true);
}

PyObject *ArcOfParabolaPy::getCustomAttributes(const char* ) const
{
    return 0;
}

int ArcOfParabolaPy::setCustomAttributes(const char* , PyObject *)
{
    return 0; 
}
