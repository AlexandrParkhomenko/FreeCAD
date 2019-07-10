/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FEATURES_H
#define PART_FEATURES_H

#include "App/PropertyStandard.h"
#include "App/PropertyUnits.h"
#include "Mod/Part/App/PartFeature.h"

namespace Part
{

class RuledSurface : public Part::Feature
{
    PROPERTY_HEADER(Part::RuledSurface);

public:
    RuledSurface();

    App::PropertyEnumeration Orientation;
    App::PropertyLinkSub Curve1;
    App::PropertyLinkSub Curve2;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderRuledSurface";
    }
    //@}

protected:
    void onChanged (const App::Property* prop);

private:
    App::DocumentObjectExecReturn* getShape(const App::PropertyLinkSub& link, TopoDS_Shape&) const;

private:
    static const char* OrientationEnums[];
};

class Loft : public Part::Feature
{
    PROPERTY_HEADER(Part::Loft);

public:
    Loft();

    App::PropertyLinkList Sections;
    App::PropertyBool Solid;
    App::PropertyBool Ruled;
    App::PropertyBool Closed;
    App::PropertyIntegerConstraint MaxDegree;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderLoft";
    }
    //@}

protected:
    void onChanged (const App::Property* prop);

private:
    static App::PropertyIntegerConstraint::Constraints Degrees;
};

class Sweep : public Part::Feature
{
    PROPERTY_HEADER(Part::Sweep);

public:
    Sweep();

    App::PropertyLinkList Sections;
    App::PropertyLinkSub Spine;
    App::PropertyBool Solid;
    App::PropertyBool Frenet;
    App::PropertyEnumeration Transition;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderSweep";
    }
    //@}

protected:
    void onChanged (const App::Property* prop);

private:
    static const char* TransitionEnums[];
};

class Thickness : public Part::Feature
{
    PROPERTY_HEADER(Part::Thickness);

public:
    Thickness();

    App::PropertyLinkSub Faces;
    App::PropertyQuantity Value;
    App::PropertyEnumeration Mode;
    App::PropertyEnumeration Join;
    App::PropertyBool Intersection;
    App::PropertyBool SelfIntersection;

    /** @name methods override feature */
    //@{
    /// recalculate the feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderThickness";
    }
    //@}

protected:
    void handleChangedPropertyType(Base::XMLReader &reader, const char *TypeName, App::Property *prop);

private:
    static const char* ModeEnums[];
    static const char* JoinEnums[];
};

} //namespace Part


#endif // PART_FEATURES_H
