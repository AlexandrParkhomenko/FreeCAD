/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#include "stdexport.h"
#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Reader.h"
#include "Base/Writer.h"
#include "App/FeaturePythonPyImp.h"

#include "Core/MeshIO.h"

#include "MeshFeature.h"
#include "MeshFeaturePy.h"

using namespace Mesh;


//===========================================================================
// Feature
//===========================================================================

PROPERTY_SOURCE(Mesh::Feature, App::GeoFeature)

Feature::Feature()
{
    ADD_PROPERTY_TYPE(Mesh,(MeshObject()),0,App::Prop_Output,"The mesh kernel");
}

Feature::~Feature()
{
}

App::DocumentObjectExecReturn *Feature::execute(void)
{
    this->Mesh.touch();
    return App::DocumentObject::StdReturn;
}

PyObject *Feature::getPyObject(void)
{
    if(PythonObject.is(Py::_None())){
        // ref counter is set to 1
        PythonObject = Py::Object(new MeshFeaturePy(this),true);
    }
    return Py::new_reference_to(PythonObject); 
}

void Feature::onChanged(const App::Property* prop)
{
    // if the placement has changed apply the change to the mesh data as well
    if (prop == &this->Placement) {
        MeshObject& mesh = const_cast<MeshObject&>(this->Mesh.getValue());
        mesh.setTransform(this->Placement.getValue().toMatrix());
    }
    // if the mesh data has changed check and adjust the transformation as well
    else if (prop == &this->Mesh) {
        Base::Placement p;
        p.fromMatrix(this->Mesh.getValue().getTransform());
        if (p != this->Placement.getValue())
            this->Placement.setValue(p);
    }

    // Note: If the Mesh property has changed the property and this object are marked as 'touched'
    // but no recomputation of this objects needs to be done because the Mesh property is regarded
    // as output of a previous recomputation The mustExecute() method returns 0 in that case. 
    // However, objects that reference this object the Mesh property can be an input parameter.
    // As this object and the property are touched such objects can check this and return a value 1 
    // (or -1) in their mustExecute() to be recomputed the next time the document recomputes itself.
    DocumentObject::onChanged(prop);
}

// ---------------------------------------------------------

namespace App {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Mesh::FeatureCustom, Mesh::Feature)
/// @endcond

// explicit template instantiation
template class Standard_EXPORT FeatureCustomT<Mesh::Feature>;
}

// ---------------------------------------------------------

namespace App {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Mesh::FeaturePython, Mesh::Feature)
template<> const char* Mesh::FeaturePython::getViewProviderName(void) const {
    return "MeshGui::ViewProviderPython";
}
template<> PyObject* Mesh::FeaturePython::getPyObject(void) {
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new FeaturePythonPyT<Mesh::MeshFeaturePy>(this),true);
    }
    return Py::new_reference_to(PythonObject);
}
/// @endcond

// explicit template instantiation
template class Standard_EXPORT FeaturePythonT<Mesh::Feature>;
}

