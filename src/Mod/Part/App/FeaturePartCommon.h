/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_FEATUREPARTCOMMON_H
#define PART_FEATUREPARTCOMMON_H

#include "App/PropertyLinks.h"
#include "FeaturePartBoolean.h"

namespace Part
{

class Common : public Boolean
{
    PROPERTY_HEADER(Part::Common);

public:
    Common();

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
protected:
    BRepAlgoAPI_BooleanOperation* makeOperation(const TopoDS_Shape&, const TopoDS_Shape&) const;
    //@}
};

class MultiCommon : public Part::Feature
{
    PROPERTY_HEADER(Part::MultiCommon);

public:
    MultiCommon();

    App::PropertyLinkList Shapes;
    PropertyShapeHistory History;
    App::PropertyBool Refine;

    /** @name methods override feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    //@}
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderMultiCommon";
    }

};

}

#endif // PART_FEATUREPARTCOMMON_H
