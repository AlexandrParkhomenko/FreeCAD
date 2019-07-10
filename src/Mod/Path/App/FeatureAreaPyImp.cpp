/****************************************************************************
 *   Copyright (c) 2017 Zheng, Lei (realthunder) <realthunder.dev@gmail.com>*
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ****************************************************************************/


#include <CXX/Objects.hxx>
#include "Mod/Part/App/TopoShapePy.h"
#include "FeatureArea.h"

// inclusion of the generated files (generated out of FeatureAreaPy.xml)
#include "FeatureAreaPy.h"
#include "FeatureAreaPy.cpp"

#include "AreaPy.h"

using namespace Path;


// returns a string which represent the object e.g. when printed in python
std::string FeatureAreaPy::representation(void) const
{
    return std::string("<Path::FeatureArea>");
}


PyObject* FeatureAreaPy::getArea(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    return new AreaPy(new Area(getFeatureAreaPtr()->getArea()));
}

PyObject* FeatureAreaPy::setParams(PyObject *args, PyObject *keywds)
{
    static char *kwlist[] = {PARAM_FIELD_STRINGS(NAME,AREA_PARAMS_CONF),NULL};

    //Declare variables defined in the NAME field of the CONF parameter list
    PARAM_PY_DECLARE(PARAM_FNAME,AREA_PARAMS_CONF);

    FeatureArea *feature = getFeatureAreaPtr();

#define AREA_SET(_param) \
    PARAM_FNAME(_param) = \
        PARAM_TYPED(PARAM_PY_CAST_,_param)(feature->PARAM_FNAME(_param).getValue());
    //populate the CONF variables with values in properties
    PARAM_FOREACH(AREA_SET,AREA_PARAMS_CONF)

    //Parse arguments to overwrite CONF variables 
    if (!PyArg_ParseTupleAndKeywords(args, keywds, 
                "|" PARAM_PY_KWDS(AREA_PARAMS_CONF), kwlist, 
                PARAM_REF(PARAM_FNAME,AREA_PARAMS_CONF)))
        return 0;

#define AREA_GET(_param) \
    feature->PARAM_FNAME(_param).setValue(\
        PARAM_TYPED(PARAM_CAST_PY_,_param)(PARAM_FNAME(_param)));
    //populate properties with the CONF variables
    PARAM_FOREACH(AREA_GET,AREA_PARAMS_CONF)

    Py_INCREF(Py_None);
    return Py_None;
}

Py::Object FeatureAreaPy::getWorkPlane(void) const {
    return Part::shape2pyshape(getFeatureAreaPtr()->getArea().getPlane());
}

void FeatureAreaPy::setWorkPlane(Py::Object obj) {
    PyObject* p = obj.ptr();
    if (!PyObject_TypeCheck(p, &(Part::TopoShapePy::Type))) {
        std::string error = std::string("type must be 'TopoShape', not ");
        error += p->ob_type->tp_name;
        throw Py::TypeError(error);
    }
    getFeatureAreaPtr()->setWorkPlane(
            static_cast<Part::TopoShapePy*>(p)->getTopoShapePtr()->getShape());
}

PyObject *FeatureAreaPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}


int FeatureAreaPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

