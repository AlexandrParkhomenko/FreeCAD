/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <Geom_OffsetSurface.hxx>
# include <memory>

#include "Base/VectorPy.h"
#include "Base/Vector3D.h"

#include "OCCError.h"
#include "Geometry.h"
#include "Mod/Part/App/OffsetSurfacePy.h"
#include <Mod/Part/App/OffsetSurfacePy.cpp>

using namespace Part;

// returns a string which represents the object e.g. when printed in python
std::string OffsetSurfacePy::representation(void) const
{
    return "<OffsetSurface object>";
}

PyObject *OffsetSurfacePy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of OffsetSurfacePy and the Twin object 
    return new OffsetSurfacePy(new GeomOffsetSurface);
}

// constructor method
int OffsetSurfacePy::PyInit(PyObject* args, PyObject* /*kwd*/)
{
    PyObject* pGeom;
    double offset;
    if (!PyArg_ParseTuple(args, "O!d", 
                            &(GeometryPy::Type), &pGeom, 
                            &offset))
        return -1;

    GeometryPy* pcGeo = static_cast<GeometryPy*>(pGeom);
    Handle(Geom_Surface) surf = Handle(Geom_Surface)::DownCast
        (pcGeo->getGeometryPtr()->handle());
    if (surf.IsNull()) {
        PyErr_SetString(PyExc_TypeError, "geometry is not a surface");
        return -1;
    }

    try {
        Handle(Geom_OffsetSurface) surf2 = new Geom_OffsetSurface(surf, offset);
        getGeomOffsetSurfacePtr()->setHandle(surf2);
        return 0;
    }
    catch (Standard_Failure& e) {

        PyErr_SetString(PartExceptionOCCError, e.GetMessageString());
        return -1;
    }
}

Py::Float OffsetSurfacePy::getOffsetValue(void) const
{
    Handle(Geom_OffsetSurface) surf = Handle(Geom_OffsetSurface)::DownCast(getGeometryPtr()->handle());
    return Py::Float(surf->Offset());
}

void  OffsetSurfacePy::setOffsetValue(Py::Float arg)
{
    Handle(Geom_OffsetSurface) surf = Handle(Geom_OffsetSurface)::DownCast(getGeometryPtr()->handle());
    surf->SetOffsetValue((double)arg);
}

Py::Object OffsetSurfacePy::getBasisSurface(void) const
{
    Handle(Geom_OffsetSurface) surf = Handle(Geom_OffsetSurface)::DownCast
        (getGeometryPtr()->handle());
    if (surf.IsNull()) {
        throw Py::TypeError("geometry is not a surface");
    }

    std::unique_ptr<GeomSurface> geo(makeFromSurface(surf->BasisSurface()));
    return Py::asObject(geo->getPyObject());
}

void  OffsetSurfacePy::setBasisSurface(Py::Object arg)
{
    PyObject* p = arg.ptr();
    if (PyObject_TypeCheck(p, &(GeometryPy::Type))) {
        GeometryPy* pcGeo = static_cast<GeometryPy*>(p);
        Handle(Geom_Surface) surf = Handle(Geom_Surface)::DownCast
            (pcGeo->getGeometryPtr()->handle());
        if (surf.IsNull()) {
            throw Py::TypeError("geometry is not a surface");
        }

        try {
            Handle(Geom_OffsetSurface) surf2 = Handle(Geom_OffsetSurface)::DownCast
                (getGeometryPtr()->handle());
            surf2->SetBasisSurface(surf);
        }
        catch (Standard_Failure& e) {
            throw Py::RuntimeError(e.GetMessageString());
        }
    }
}

PyObject *OffsetSurfacePy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int OffsetSurfacePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}
