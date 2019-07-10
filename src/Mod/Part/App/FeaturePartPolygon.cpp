/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <BRep_Builder.hxx>
# include <BRepBuilderAPI_MakePolygon.hxx>
# include <gp_Pnt.hxx>
# include <TopoDS_Wire.hxx>

#include "FeaturePartPolygon.h"
#include "Base/Exception.h"

PROPERTY_SOURCE(Part::Polygon, Part::Feature)


Part::Polygon::Polygon()
{
    ADD_PROPERTY(Nodes,(Base::Vector3d()));
    ADD_PROPERTY(Close,(false));
}

Part::Polygon::~Polygon()
{
}

short Part::Polygon::mustExecute() const
{
    if (Nodes.isTouched() || Close.isTouched())
        return 1;
    return 0;
}

App::DocumentObjectExecReturn *Part::Polygon::execute(void)
{
    BRepBuilderAPI_MakePolygon poly;
    const std::vector<Base::Vector3d> nodes = Nodes.getValues();

    for (std::vector<Base::Vector3d>::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        gp_Pnt pnt(it->x, it->y, it->z);
        poly.Add(pnt);
    }

    if (Close.getValue())
        poly.Close();

    if (!poly.IsDone())
        throw Base::CADKernelError("Cannot create polygon because less than two vertices are given");
    TopoDS_Wire wire = poly.Wire();
    this->Shape.setValue(wire);

    return App::DocumentObject::StdReturn;
}
