/***************************************************************************
 *   Copyright (c) Juergen Riegel         <juergen.riegel@web.de>          *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include <vector>

#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Stream.h"
#include "Base/Writer.h"


#include "PointsFeature.h"

using namespace Points;


//===========================================================================
// Feature
//===========================================================================

PROPERTY_SOURCE(Points::Feature, App::GeoFeature)

Feature::Feature() 
{
    ADD_PROPERTY(Points, (PointKernel()));
}

Feature::~Feature()
{
}

short Feature::mustExecute() const
{
    return 0;
}

App::DocumentObjectExecReturn *Feature::execute(void)
{
    this->Points.touch();
    return App::DocumentObject::StdReturn;
}

void Feature::Restore(Base::XMLReader &reader)
{
    GeoFeature::Restore(reader);
}

void Feature::RestoreDocFile(Base::Reader &reader)
{
    // This gets only invoked if a points file has been added from Restore()
    Points.RestoreDocFile(reader);
}

void Feature::onChanged(const App::Property* prop)
{
    // if the placement has changed apply the change to the point data as well
    if (prop == &this->Placement) {
        PointKernel& pts = const_cast<PointKernel&>(this->Points.getValue());
        pts.setTransform(this->Placement.getValue().toMatrix());
    }
    // if the point data has changed check and adjust the transformation as well
    else if (prop == &this->Points) {
        Base::Placement p;
        p.fromMatrix(this->Points.getValue().getTransform());
        if (p != this->Placement.getValue())
            this->Placement.setValue(p);
    }
    
    GeoFeature::onChanged(prop);
}

// ---------------------------------------------------------

namespace App {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Points::FeatureCustom, Points::Feature)
/// @endcond

// explicit template instantiation
template class Standard_EXPORT FeatureCustomT<Points::Feature>;
}

// ---------------------------------------------------------

namespace App {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Points::FeaturePython, Points::Feature)
template<> const char* Points::FeaturePython::getViewProviderName(void) const {
    return "PointsGui::ViewProviderPython";
}
/// @endcond

// explicit template instantiation
template class Standard_EXPORT FeaturePythonT<Points::Feature>;
}

