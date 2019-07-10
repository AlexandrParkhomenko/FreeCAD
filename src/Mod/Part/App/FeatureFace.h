/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FACE_H
#define PART_FACE_H

#include "stdexport.h"
#include "Mod/Part/App/PartFeature.h"

namespace Part
{

class Standard_EXPORT Face : public Part::Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Part::Face);

public:
    Face();

    App::PropertyLinkList   Sources;
    App::PropertyString FaceMakerClass;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void) override;
    short mustExecute() const override;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const override {
        return "PartGui::ViewProviderFace";
    }
    void setupObject() override;
    //@}
};

} //namespace Part


#endif // PART_FACE_H
