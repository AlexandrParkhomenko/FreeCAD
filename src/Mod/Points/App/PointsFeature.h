/***************************************************************************
 *   Copyright (c) Juergen Riegel         <juergen.riegel@web.de>          *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef POINTS_FEATURE_H
#define POINTS_FEATURE_H

#include "App/GeoFeature.h"
#include "App/FeatureCustom.h"
#include "App/FeaturePython.h"
#include "App/PropertyLinks.h"
#include "App/PropertyGeo.h"
#include "Points.h"
#include "PropertyPointKernel.h"


namespace Base{
class Writer;
}

namespace App{
class Color;
}

namespace Points
{
class Property;
class PointsFeaturePy;

/** Base class of all Points feature classes in FreeCAD.
 * This class holds an PointsKernel object.
 */
class Standard_EXPORT Feature : public App::GeoFeature
{
    PROPERTY_HEADER(Points::Feature);

public:
    /// Constructor
    Feature(void);
    virtual ~Feature(void);

    /** @name methods override Feature */
    //@{
    void Restore(Base::XMLReader &reader);
    void RestoreDocFile(Base::Reader &reader);
    short mustExecute() const;
    /// recalculate the Feature
    virtual App::DocumentObjectExecReturn *execute(void);
    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "PointsGui::ViewProviderScattered";
    }

    virtual const App::PropertyComplexGeoData* getPropertyOfGeometry() const {
        return &Points;
    }
protected:
    void onChanged(const App::Property* prop);
    //@}

public:
    PropertyPointKernel Points; /**< The point kernel property. */
};

typedef App::FeatureCustomT<Feature> FeatureCustom;
typedef App::FeaturePythonT<Feature> FeaturePython;

} //namespace Points


#endif 
