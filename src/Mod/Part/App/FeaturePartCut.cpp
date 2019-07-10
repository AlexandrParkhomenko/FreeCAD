/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

 
# include <BRepAlgoAPI_Cut.hxx>


#include "FeaturePartCut.h"

#include "Base/Exception.h"

using namespace Part;

PROPERTY_SOURCE(Part::Cut, Part::Boolean)


Cut::Cut(void)
{
}

BRepAlgoAPI_BooleanOperation* Cut::makeOperation(const TopoDS_Shape& base, const TopoDS_Shape& tool) const
{
    // Let's call algorithm computing a cut operation:
    return new BRepAlgoAPI_Cut(base, tool);
}
