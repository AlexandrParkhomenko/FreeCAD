/***************************************************************************
 *   Copyright (c) Juergen Riegel          (juergen.riegel@web.de) 2016    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "App/GeoFeature.h"

// inclusion of the generated files (generated out of GeoFeaturePy.xml)
#include "GeoFeaturePy.h"
#include "GeoFeaturePy.cpp"
#include "Base/PlacementPy.h"
#include <CXX/Objects.hxx>

using namespace App;

// returns a string which represents the object e.g. when printed in python
std::string GeoFeaturePy::representation(void) const
{
    return std::string("<GeoFeature object>");
}

PyObject* GeoFeaturePy::getPaths(PyObject * /*args*/)
{
    PyErr_SetString(PyExc_NotImplementedError, "Not yet implemented");
    return 0;
}

PyObject* GeoFeaturePy::getGlobalPlacement(PyObject * args) {
    
    if (!PyArg_ParseTuple(args, ""))
        return 0;
    
    try {
        Base::Placement p = static_cast<GeoFeature*>(getDocumentObjectPtr())->globalPlacement();
        return new Base::PlacementPy(new Base::Placement(p));
    }
    catch (const Base::Exception& e) {
        throw Py::RuntimeError(e.what());
    }
}

PyObject* GeoFeaturePy::getPropertyNameOfGeometry(PyObject * args)
{
    if (!PyArg_ParseTuple(args, ""))
        return 0;
    GeoFeature* object = this->getGeoFeaturePtr();
    const PropertyComplexGeoData* prop = object->getPropertyOfGeometry();
    const char* name = prop ? prop->getName() : 0;
    if (name) {
        return Py::new_reference_to(Py::String(std::string(name)));
    }
    return Py::new_reference_to(Py::None());
}

PyObject *GeoFeaturePy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int GeoFeaturePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}
