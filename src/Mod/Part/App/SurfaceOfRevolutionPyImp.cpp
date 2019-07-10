/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <Geom_SurfaceOfRevolution.hxx>

#include "Geometry.h"
#include "SurfaceOfRevolutionPy.h"
#include "SurfaceOfRevolutionPy.cpp"

#include "Base/GeometryPyCXX.h"
#include "Base/VectorPy.h"
#include "OCCError.h"

using namespace Part;

// returns a string which represents the object e.g. when printed in python
std::string SurfaceOfRevolutionPy::representation(void) const
{
    return std::string("<SurfaceOfRevolution object>");
}

PyObject *SurfaceOfRevolutionPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of SurfaceOfRevolutionPy and the Twin object 
    return new SurfaceOfRevolutionPy(new GeomSurfaceOfRevolution);
}

// constructor method
int SurfaceOfRevolutionPy::PyInit(PyObject* args, PyObject* /*kwd*/)
{
    PyObject* pGeom;
    PyObject* pPnt;
    PyObject* pDir;
    if (!PyArg_ParseTuple(args, "O!O!O!", 
                            &(GeometryPy::Type), &pGeom, 
                            &(Base::VectorPy::Type),&pPnt,
                            &(Base::VectorPy::Type),&pDir))
        return -1;

    GeometryPy* pcGeo = static_cast<GeometryPy*>(pGeom);
    Handle(Geom_Curve) curve = Handle(Geom_Curve)::DownCast
        (pcGeo->getGeometryPtr()->handle());
    if (curve.IsNull()) {
        PyErr_SetString(PyExc_TypeError, "geometry is not a curve");
        return -1;
    }

    try {
        Base::Vector3d pnt = static_cast<Base::VectorPy*>(pPnt)->value();
        Base::Vector3d dir = static_cast<Base::VectorPy*>(pDir)->value();
        Handle(Geom_SurfaceOfRevolution) curve2 = new Geom_SurfaceOfRevolution(curve,
            gp_Ax1(gp_Pnt(pnt.x,pnt.y,pnt.z),
                   gp_Dir(dir.x,dir.y,dir.z)));
        getGeomSurfaceOfRevolutionPtr()->setHandle(curve2);
        return 0;
    }
    catch (Standard_Failure& e) {

        PyErr_SetString(PartExceptionOCCError, e.GetMessageString());
        return -1;
    }
}

Py::Object SurfaceOfRevolutionPy::getLocation(void) const
{
    Handle(Geom_SurfaceOfRevolution) curve = Handle(Geom_SurfaceOfRevolution)::DownCast
        (getGeometryPtr()->handle());
    const gp_Pnt& pnt = curve->Location();
    return Py::Vector(Base::Vector3d(pnt.X(),pnt.Y(),pnt.Z()));
}

void  SurfaceOfRevolutionPy::setLocation(Py::Object arg)
{
    PyObject* p = arg.ptr();
    if (PyObject_TypeCheck(p, &(Base::VectorPy::Type))) {
        Base::Vector3d pnt = static_cast<Base::VectorPy*>(p)->value();
        Handle(Geom_SurfaceOfRevolution) curve = Handle(Geom_SurfaceOfRevolution)::DownCast
            (getGeometryPtr()->handle());
        curve->SetLocation(gp_Pnt(pnt.x,pnt.y,pnt.z));
    }
    else if (PyObject_TypeCheck(p, &PyTuple_Type)) {
        Base::Vector3d pnt = Base::getVectorFromTuple<double>(p);
        Handle(Geom_SurfaceOfRevolution) curve = Handle(Geom_SurfaceOfRevolution)::DownCast
            (getGeometryPtr()->handle());
        curve->SetLocation(gp_Pnt(pnt.x,pnt.y,pnt.z));
    }
    else {
        std::string error = std::string("type must be 'Vector', not ");
        error += p->ob_type->tp_name;
        throw Py::TypeError(error);
    }
}

Py::Object SurfaceOfRevolutionPy::getDirection(void) const
{
    Handle(Geom_SurfaceOfRevolution) curve = Handle(Geom_SurfaceOfRevolution)::DownCast
        (getGeometryPtr()->handle());
    const gp_Dir& dir = curve->Direction();
    return Py::Vector(Base::Vector3d(dir.X(),dir.Y(),dir.Z()));
}

void  SurfaceOfRevolutionPy::setDirection(Py::Object arg)
{
    PyObject* p = arg.ptr();
    if (PyObject_TypeCheck(p, &(Base::VectorPy::Type))) {
        Base::Vector3d dir = static_cast<Base::VectorPy*>(p)->value();
        Handle(Geom_SurfaceOfRevolution) curve = Handle(Geom_SurfaceOfRevolution)::DownCast
            (getGeometryPtr()->handle());
        curve->SetDirection(gp_Dir(dir.x,dir.y,dir.z));
    }
    else if (PyObject_TypeCheck(p, &PyTuple_Type)) {
        Base::Vector3d dir = Base::getVectorFromTuple<double>(p);
        Handle(Geom_SurfaceOfRevolution) curve = Handle(Geom_SurfaceOfRevolution)::DownCast
            (getGeometryPtr()->handle());
        curve->SetDirection(gp_Dir(dir.x,dir.y,dir.z));
    }
    else {
        std::string error = std::string("type must be 'Vector', not ");
        error += p->ob_type->tp_name;
        throw Py::TypeError(error);
    }
}

Py::Object SurfaceOfRevolutionPy::getBasisCurve(void) const
{
    throw Py::Exception(PyExc_NotImplementedError, "Not yet implemented");
}

void  SurfaceOfRevolutionPy::setBasisCurve(Py::Object arg)
{
    PyObject* p = arg.ptr();
    if (PyObject_TypeCheck(p, &(GeometryPy::Type))) {
        GeometryPy* pcGeo = static_cast<GeometryPy*>(p);
        Handle(Geom_Curve) curve = Handle(Geom_Curve)::DownCast
            (pcGeo->getGeometryPtr()->handle());
        if (curve.IsNull()) {
            throw Py::TypeError("geometry is not a curve");
        }

        try {
            Handle(Geom_SurfaceOfRevolution) curve2 = Handle(Geom_SurfaceOfRevolution)::DownCast
                (getGeometryPtr()->handle());
            curve2->SetBasisCurve(curve);
        }
        catch (Standard_Failure& e) {
            throw Py::RuntimeError(e.GetMessageString());
        }
    }
}

PyObject *SurfaceOfRevolutionPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int SurfaceOfRevolutionPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}


