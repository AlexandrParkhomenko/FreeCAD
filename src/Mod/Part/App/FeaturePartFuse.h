/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FEATUREPARTFUSE_H
#define PART_FEATUREPARTFUSE_H

#include "App/PropertyLinks.h"

#include "FeaturePartBoolean.h"

namespace Part
{

class Fuse : public Boolean
{
    PROPERTY_HEADER(Part::Fuse);

public:
    Fuse();

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
protected:
    BRepAlgoAPI_BooleanOperation* makeOperation(const TopoDS_Shape&, const TopoDS_Shape&) const;
    //@}
};

class MultiFuse : public Part::Feature
{
    PROPERTY_HEADER(Part::MultiFuse);

public:
    MultiFuse();

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
        return "PartGui::ViewProviderMultiFuse";
    }

};

}

#endif // PART_FEATUREPARTFUSE_H
