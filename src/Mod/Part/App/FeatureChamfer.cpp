/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <BRepFilletAPI_MakeChamfer.hxx>
# include <TopExp.hxx>
# include <TopExp_Explorer.hxx>
# include <TopoDS.hxx>
# include <TopoDS_Edge.hxx>
# include <TopTools_ListOfShape.hxx>
# include <TopTools_IndexedMapOfShape.hxx>
# include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>


#include "FeatureChamfer.h"


using namespace Part;


PROPERTY_SOURCE(Part::Chamfer, Part::FilletBase)

Chamfer::Chamfer()
{
}

App::DocumentObjectExecReturn *Chamfer::execute(void)
{
    App::DocumentObject* link = Base.getValue();
    if (!link)
        return new App::DocumentObjectExecReturn("No object linked");
    if (!link->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId()))
        return new App::DocumentObjectExecReturn("Linked object is not a Part object");
    Part::Feature *base = static_cast<Part::Feature*>(Base.getValue());

    try {
        BRepFilletAPI_MakeChamfer mkChamfer(base->Shape.getValue());
        TopTools_IndexedMapOfShape mapOfEdges;
        TopTools_IndexedDataMapOfShapeListOfShape mapEdgeFace;
        TopExp::MapShapesAndAncestors(base->Shape.getValue(), TopAbs_EDGE, TopAbs_FACE, mapEdgeFace);
        TopExp::MapShapes(base->Shape.getValue(), TopAbs_EDGE, mapOfEdges);

        std::vector<FilletElement> values = Edges.getValues();
        for (std::vector<FilletElement>::iterator it = values.begin(); it != values.end(); ++it) {
            int id = it->edgeid;
            double radius1 = it->radius1;
            double radius2 = it->radius2;
            const TopoDS_Edge& edge = TopoDS::Edge(mapOfEdges.FindKey(id));
            const TopoDS_Face& face = TopoDS::Face(mapEdgeFace.FindFromKey(edge).First());
            mkChamfer.Add(radius1, radius2, edge, face);
        }

        TopoDS_Shape shape = mkChamfer.Shape();
        if (shape.IsNull())
            return new App::DocumentObjectExecReturn("Resulting shape is null");
        ShapeHistory history = buildHistory(mkChamfer, TopAbs_FACE, shape, base->Shape.getValue());
        this->Shape.setValue(shape);

        // make sure the 'PropertyShapeHistory' is not safed in undo/redo (#0001889)
        PropertyShapeHistory prop;
        prop.setValue(history);
        prop.setContainer(this);
        prop.touch();

        return App::DocumentObject::StdReturn;
    }
    catch (Standard_Failure& e) {
        return new App::DocumentObjectExecReturn(e.GetMessageString());
    }
}

