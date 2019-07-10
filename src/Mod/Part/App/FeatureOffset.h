/***************************************************************************
 *   Copyright (c) 2016 Victor Titov (DeepSOIC)      <vv.titov@gmail.com>  *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PART_FEATUREOFFSET_H
#define PART_FEATUREOFFSET_H

#include "stdexport.h"
#include "App/PropertyStandard.h"
#include "App/PropertyUnits.h"
#include "Mod/Part/App/PartFeature.h"

namespace Part
{

class Standard_EXPORT Offset : public Part::Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Part::Offset);

public:
    Offset();
    ~Offset();

    App::PropertyLink  Source;
    App::PropertyFloat Value;
    App::PropertyEnumeration Mode;
    App::PropertyEnumeration Join;
    App::PropertyBool Intersection;
    App::PropertyBool SelfIntersection;
    App::PropertyBool Fill;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    virtual App::DocumentObjectExecReturn *execute(void) override;
    virtual short mustExecute() const override;
    virtual const char* getViewProviderName(void) const override {
        return "PartGui::ViewProviderOffset";
    }
    //@}

private:
    static const char* ModeEnums[];
    static const char* JoinEnums[];
};

class Standard_EXPORT Offset2D : public Offset
{
    PROPERTY_HEADER_WITH_OVERRIDE(Part::Offset2D);
public:
    Offset2D();
    ~Offset2D();

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    virtual App::DocumentObjectExecReturn *execute(void) override;
    virtual short mustExecute() const override;
    virtual const char* getViewProviderName(void) const override {
        return "PartGui::ViewProviderOffset2D";
    }
    //@}
};

}
#endif // PART_FEATUREOFFSET_H
