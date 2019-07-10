/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FEATURECHAMFER_H
#define PART_FEATURECHAMFER_H

#include "App/PropertyStandard.h"
#include "PartFeature.h"

namespace Part
{

class Chamfer : public Part::FilletBase
{
    PROPERTY_HEADER(Part::Chamfer);

public:
    Chamfer();

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    /// returns the type name of the view provider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderChamfer";
    }
    //@}
};

} //namespace Part


#endif // PART_FEATURECHAMFER_H

