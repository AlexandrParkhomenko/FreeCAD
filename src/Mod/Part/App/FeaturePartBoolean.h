/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_FEATUREPARTBOOLEAN_H
#define PART_FEATUREPARTBOOLEAN_H

#include "App/PropertyLinks.h"
#include "PartFeature.h"

class BRepAlgoAPI_BooleanOperation;

namespace Part
{

class Boolean : public Part::Feature
{
    PROPERTY_HEADER(Part::Boolean);

public:
    Boolean();

    App::PropertyLink Base;
    App::PropertyLink Tool;
    PropertyShapeHistory History;
    App::PropertyBool Refine;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    //@}

    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderBoolean";
    }

protected:
    virtual BRepAlgoAPI_BooleanOperation* makeOperation(const TopoDS_Shape&, const TopoDS_Shape&) const = 0;
};

}

#endif // PART_FEATUREPARTBOOLEAN_H
