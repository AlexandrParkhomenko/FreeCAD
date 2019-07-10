/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_FEATURECOMPOUND_H
#define PART_FEATURECOMPOUND_H

#include "App/PropertyLinks.h"
#include "PartFeature.h"

namespace Part
{

class Compound : public Part::Feature
{
    PROPERTY_HEADER(Part::Compound);

public:
    Compound();
    virtual ~Compound();

    App::PropertyLinkList Links;

    /** @name methods override feature */
    //@{
    short mustExecute() const;
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    /// returns the type name of the view provider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderCompound";
    }
    //@}
};

} //namespace Part


#endif // PART_FEATURECOMPOUND_H

