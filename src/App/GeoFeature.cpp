/***************************************************************************
 *   Copyright (c) Juergen Riegel          (juergen.riegel@web.de) 2002    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "GeoFeature.h"
#include "GeoFeatureGroupExtension.h"
#include "App/GeoFeaturePy.h"

using namespace App;


PROPERTY_SOURCE(App::GeoFeature, App::DocumentObject)


//===========================================================================
// Feature
//===========================================================================

GeoFeature::GeoFeature(void)
{
    ADD_PROPERTY_TYPE(Placement,(Base::Placement()),nullptr,Prop_NoRecompute,nullptr);
}

GeoFeature::~GeoFeature(void)
{
}

void GeoFeature::transformPlacement(const Base::Placement &transform)
{
    Base::Placement plm = this->Placement.getValue();
    plm = transform * plm;
    this->Placement.setValue(plm);
}

Base::Placement GeoFeature::globalPlacement() const
{
    auto* group = GeoFeatureGroupExtension::getGroupOfObject(this);
    if (group) {
        auto ext = group->getExtensionByType<GeoFeatureGroupExtension>();
        return ext->globalGroupPlacement() * Placement.getValue();
    }
    return Placement.getValue();    
}

const PropertyComplexGeoData* GeoFeature::getPropertyOfGeometry() const
{
    return nullptr;
}

PyObject* GeoFeature::getPyObject(void)
{
    if (PythonObject.is(Py::_None())) {
        // ref counter is set to 1
        PythonObject = Py::Object(new GeoFeaturePy(this),true);
    }
    return Py::new_reference_to(PythonObject);
}
