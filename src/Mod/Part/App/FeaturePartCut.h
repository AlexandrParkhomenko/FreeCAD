/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_FEATUREPARTCUT_H
#define PART_FEATUREPARTCUT_H

#include "App/PropertyLinks.h"

#include "FeaturePartBoolean.h"

namespace Part
{

class Cut : public Boolean
{
    PROPERTY_HEADER(Part::Cut);

public:
    Cut();

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
protected:
    BRepAlgoAPI_BooleanOperation* makeOperation(const TopoDS_Shape&, const TopoDS_Shape&) const;
    //@}
};

}

#endif // PART_FEATUREPARTCUT_H
