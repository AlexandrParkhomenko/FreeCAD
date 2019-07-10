/***************************************************************************
 *   Copyright (c) 2008 Juergen Riegel <juergen.riegel@web.de>             *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "Mod/Points/App/Points.h"
#include "Base/Builder3D.h"
#include "Base/VectorPy.h"
#include "Base/GeometryPyCXX.h"
#include <boost/math/special_functions/fpclassify.hpp>

// inclusion of the generated files (generated out of PointsPy.xml)
#include "PointsPy.h"
#include "PointsPy.cpp"

using namespace Points;

// returns a string which represents the object e.g. when printed in python
std::string PointsPy::representation(void) const
{
    return std::string("<PointKernel object>");
}

PyObject *PointsPy::PyMake(struct _typeobject *, PyObject *, PyObject *)  // Python wrapper
{
    // create a new instance of PointsPy and the Twin object 
    return new PointsPy(new PointKernel);
}

// constructor method
int PointsPy::PyInit(PyObject* args, PyObject* /*kwd*/)
{
    PyObject *pcObj=0;
    if (!PyArg_ParseTuple(args, "|O", &pcObj))     // convert args: Python->C 
        return -1;                             // NULL triggers exception

    // if no mesh is given
    if (!pcObj) return 0;
    if (PyObject_TypeCheck(pcObj, &(PointsPy::Type))) {
        *getPointKernelPtr() = *(static_cast<PointsPy*>(pcObj)->getPointKernelPtr());
    }
    else if (PyList_Check(pcObj)) {
        if (!addPoints(args))
            return -1;
    }
    else if (PyTuple_Check(pcObj)) {
        if (!addPoints(args))
            return -1;
    }
    else if (PyUnicode_Check(pcObj)) {
        getPointKernelPtr()->load(PyUnicode_AsUTF8(pcObj));
    }

    else {
        PyErr_SetString(PyExc_TypeError, "optional argument must be list, tuple or string");
        return -1;
    }

    return 0;
}

PyObject* PointsPy::copy(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    PointKernel* kernel = new PointKernel();
    // assign data
    *kernel = *getPointKernelPtr();
    return new PointsPy(kernel);
}

PyObject* PointsPy::read(PyObject * args)
{
    const char* Name;
    if (!PyArg_ParseTuple(args, "s",&Name))
        return NULL;                         

    PY_TRY {
        getPointKernelPtr()->load(Name);
    } PY_CATCH;
    
    Py_Return; 
}

PyObject* PointsPy::write(PyObject * args)
{
    const char* Name;
    if (!PyArg_ParseTuple(args, "s",&Name))
        return NULL;                         

    PY_TRY {
        getPointKernelPtr()->save(Name);
    } PY_CATCH;
    
    Py_Return; 
}

PyObject* PointsPy::writeInventor(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    std::stringstream result;
    Base::InventorBuilder builder(result);
    builder.beginPoints();
    PointKernel* kernel = getPointKernelPtr();
    for (Points::PointKernel::const_iterator it = kernel->begin(); it != kernel->end(); ++it)
        builder.addPoint((float)it->x,(float)it->y,(float)it->z);
    builder.endPoints();
    builder.addPointSet();
    builder.close();

    return Py::new_reference_to(Py::String(result.str()));
}

PyObject* PointsPy::addPoints(PyObject * args)
{
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "O", &obj))
        return 0;

    try {
        Py::Sequence list(obj);
        union PyType_Object pyType = {&(Base::VectorPy::Type)};
        Py::Type vType(pyType.o);

        for (Py::Sequence::iterator it = list.begin(); it != list.end(); ++it) {
            if ((*it).isType(vType)) {
                Py::Vector p(*it);
                getPointKernelPtr()->push_back(p.toVector());
            }
            else {
                Base::Vector3d pnt;
                Py::Tuple tuple(*it);
                pnt.x = (double)Py::Float(tuple[0]);
                pnt.y = (double)Py::Float(tuple[1]);
                pnt.z = (double)Py::Float(tuple[2]);
                getPointKernelPtr()->push_back(pnt);
            }
        }
    }
    catch (const Py::Exception&) {
        PyErr_SetString(Base::BaseExceptionFreeCADError, "either expect\n"
            "-- [Vector,...] \n"
            "-- [(x,y,z),...]");
        return 0;
    }

    Py_Return;
}

PyObject* PointsPy::fromSegment(PyObject * args)
{
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "O", &obj))
        return 0;

    try {
        const PointKernel* points = getPointKernelPtr();
        Py::Sequence list(obj);
        std::unique_ptr<PointKernel> pts(new PointKernel());
        pts->reserve(list.size());
        int numPoints = static_cast<int>(points->size());
        for (Py::Sequence::iterator it = list.begin(); it != list.end(); ++it) {
            long index = static_cast<long>(Py::Long(*it));
            if (index >= 0 && index < numPoints)
                pts->push_back(points->getPoint(index));
        }

        return new PointsPy(pts.release());
    }
    catch (const Py::Exception&) {
        PyErr_SetString(Base::BaseExceptionFreeCADError, "expect a list of int");
        return 0;
    }
}

PyObject* PointsPy::fromValid(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return 0;

    try {
        const PointKernel* points = getPointKernelPtr();
        std::unique_ptr<PointKernel> pts(new PointKernel());
        pts->reserve(points->size());
        for (PointKernel::const_iterator it = points->begin(); it != points->end(); ++it) {
            if (!boost::math::isnan(it->x) && !boost::math::isnan(it->y) && !boost::math::isnan(it->z))
                pts->push_back(*it);
        }

        return new PointsPy(pts.release());
    }
    catch (const Py::Exception&) {
        PyErr_SetString(Base::BaseExceptionFreeCADError, "expect a list of int");
        return 0;
    }
}

Py::Long PointsPy::getCountPoints(void) const
{
    return Py::Long((long)getPointKernelPtr()->size());
}

Py::List PointsPy::getPoints(void) const
{
    Py::List PointList;
    const PointKernel* points = getPointKernelPtr();
    for (PointKernel::const_point_iterator it = points->begin(); it != points->end(); ++it) {
        PointList.append(Py::Object(new Base::VectorPy(*it)));
    }
    return PointList;
}

PyObject *PointsPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int PointsPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}


