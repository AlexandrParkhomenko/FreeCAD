/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FEATUREPARTSECTION_H
#define PART_FEATUREPARTSECTION_H

#include "App/PropertyLinks.h"

#include "FeaturePartBoolean.h"

namespace Part
{

class Section : public Boolean
{
    PROPERTY_HEADER(Part::Section);

public:
    Section();

    App::PropertyBool Approximation;
    
    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    short mustExecute() const;
protected:
    BRepAlgoAPI_BooleanOperation* makeOperation(const TopoDS_Shape&, const TopoDS_Shape&) const;
    //@}
};

}

#endif // PART_FEATUREPARTSECTION_H
