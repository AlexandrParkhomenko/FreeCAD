/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <gp_Elips2d.hxx>
# include <Geom2d_Ellipse.hxx>
# include <GCE2d_MakeArcOfEllipse.hxx>
# include <GCE2d_MakeEllipse.hxx>
# include <Geom2d_TrimmedCurve.hxx>

#include "Mod/Part/App/Geometry2d.h"
#include "Mod/Part/App/Geom2d/ArcOfEllipse2dPy.h"
#include <Mod/Part/App/Geom2d/ArcOfEllipse2dPy.cpp>
#include "Mod/Part/App/Geom2d/Ellipse2dPy.h"
#include "Mod/Part/App/OCCError.h"

#include "Base/GeometryPyCXX.h"

using namespace Part;

extern const char* gce_ErrorStatusText(gce_ErrorType et);

// returns a string which represents the object e.g. when printed in python
std::string ArcOfEllipse2dPy::representation(void) const
{
    return "<Arc of ellipse2d object>";
}

PyObject *ArcOfEllipse2dPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of ArcOfEllipse2dPy and the Twin object
    return new ArcOfEllipse2dPy(new Geom2dArcOfEllipse);
}

// constructor method
int ArcOfEllipse2dPy::PyInit(PyObject* args, PyObject* /*kwds*/)
{
    PyObject* o;
    double u1, u2;
    PyObject *sense=Py_True;
    if (PyArg_ParseTuple(args, "O!dd|O!", &(Part::Ellipse2dPy::Type), &o, &u1, &u2, &PyBool_Type, &sense)) {
        try {
            Handle(Geom2d_Ellipse) ellipse = Handle(Geom2d_Ellipse)::DownCast
                (static_cast<Ellipse2dPy*>(o)->getGeom2dEllipsePtr()->handle());
            GCE2d_MakeArcOfEllipse arc(ellipse->Elips2d(), u1, u2, PyObject_IsTrue(sense) ? Standard_True : Standard_False);
            if (!arc.IsDone()) {
                PyErr_SetString(PartExceptionOCCError, gce_ErrorStatusText(arc.Status()));
                return -1;
            }

            getGeom2dArcOfEllipsePtr()->setHandle(arc.Value());
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
        "ArcOfEllipse2d constructor expects an ellipse curve and a parameter range");
    return -1;
}

Py::Float ArcOfEllipse2dPy::getMajorRadius(void) const
{
    return Py::Float(getGeom2dArcOfEllipsePtr()->getMajorRadius());
}

void  ArcOfEllipse2dPy::setMajorRadius(Py::Float arg)
{
    getGeom2dArcOfEllipsePtr()->setMajorRadius((double)arg);
}

Py::Float ArcOfEllipse2dPy::getMinorRadius(void) const
{
    return Py::Float(getGeom2dArcOfEllipsePtr()->getMinorRadius());
}

void  ArcOfEllipse2dPy::setMinorRadius(Py::Float arg)
{
    getGeom2dArcOfEllipsePtr()->setMinorRadius((double)arg);
}

Py::Object ArcOfEllipse2dPy::getEllipse(void) const
{
    Handle(Geom2d_TrimmedCurve) curve = Handle(Geom2d_TrimmedCurve)::DownCast(getGeom2dArcOfConicPtr()->handle());
    Handle(Geom2d_Ellipse) ellipse = Handle(Geom2d_Ellipse)::DownCast(curve->BasisCurve());
    return Py::asObject(new Ellipse2dPy(new Geom2dEllipse(ellipse)));
}

PyObject *ArcOfEllipse2dPy::getCustomAttributes(const char* ) const
{
    return 0;
}

int ArcOfEllipse2dPy::setCustomAttributes(const char* , PyObject *)
{
    return 0; 
}
