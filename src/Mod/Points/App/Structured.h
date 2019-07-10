/***************************************************************************
 *   Copyright (c) 2015 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef POINTS_VIEW_FEATURE_H
#define POINTS_VIEW_FEATURE_H

#include "PointsFeature.h"


namespace Points
{

/*! For the Structured class it is expected that the Point property has Width*Height vertices
  and that with respect to their x,y coordinates they are ordered in a grid structure.
  If a point is marked invalid then one of its coordinates is set to NaN.
 */
class Standard_EXPORT Structured : public Feature
{
    PROPERTY_HEADER(Points::Structured);

public:
    /// Constructor
    Structured(void);
    virtual ~Structured(void);

    App::PropertyInteger Width; /**< The width of the structured cloud. */
    App::PropertyInteger Height; /**< The height of the structured cloud. */

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    virtual App::DocumentObjectExecReturn *execute(void);
    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "PointsGui::ViewProviderStructured";
    }
    //@}
};

typedef App::FeatureCustomT<Structured> StructuredCustom;

} //namespace Points


#endif
