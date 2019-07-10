/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_FEATUREFILLET_H
#define PART_FEATUREFILLET_H

#include "App/PropertyStandard.h"
#include "PartFeature.h"

namespace Part
{

class Fillet : public Part::FilletBase
{
    PROPERTY_HEADER(Part::Fillet);

public:
    Fillet();

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    /// returns the type name of the view provider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderFillet";
    }
    //@}
};

} //namespace Part


#endif // PART_FEATUREFILLET_H
