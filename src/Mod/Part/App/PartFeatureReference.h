/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2010     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_FeatureReference_H
#define PART_FeatureReference_H

#include "stdexport.h"
#include "TopoShape.h"
#include "PropertyTopoShape.h"
#include "App/GeoFeature.h"
#include "App/FeaturePython.h"
#include "App/PropertyLinks.h"

namespace Part
{

class PartFeaturePy;

/** Base class of all shape feature classes in FreeCAD
 */
class Standard_EXPORT FeatureReference : public App::GeoFeature
{
    PROPERTY_HEADER(Part::FeatureReference);

public:
    /// Constructor
    FeatureReference(void);
    virtual ~FeatureReference();

	App::PropertyLink Reference;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    virtual App::DocumentObjectExecReturn *execute(void);
    virtual short mustExecute(void) const;
    //@}

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderPartReference";
    }
protected:
    TopLoc_Location getLocation() const;

};


} //namespace Part


#endif // PART_FeatureReference_H
