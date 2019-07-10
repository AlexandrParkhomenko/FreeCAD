/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <BRep_Builder.hxx>
# include <TopoDS_Compound.hxx>
# include <TopExp.hxx>
# include <TopTools_IndexedMapOfShape.hxx>
# include <Standard_Failure.hxx>


#include "FeatureCompound.h"


using namespace Part;


PROPERTY_SOURCE(Part::Compound, Part::Feature)

Compound::Compound()
{
    ADD_PROPERTY(Links,(0));
    Links.setSize(0);
}

Compound::~Compound()
{
}

short Compound::mustExecute() const
{
    if (Links.isTouched())
        return 1;
    return 0;
}

App::DocumentObjectExecReturn *Compound::execute(void)
{
    try {
        std::vector<ShapeHistory> history;
        int countFaces = 0;

        BRep_Builder builder;
        TopoDS_Compound comp;
        builder.MakeCompound(comp);

        const std::vector<DocumentObject*>& links = Links.getValues();
        for (std::vector<DocumentObject*>::const_iterator it = links.begin(); it != links.end(); ++it) {
            if (*it && (*it)->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId())) {
                Part::Feature* fea = static_cast<Part::Feature*>(*it);
                const TopoDS_Shape& sh = fea->Shape.getValue();
                if (!sh.IsNull()) {
                    builder.Add(comp, sh);
                    TopTools_IndexedMapOfShape faceMap;
                    TopExp::MapShapes(sh, TopAbs_FACE, faceMap);
                    ShapeHistory hist;
                    hist.type = TopAbs_FACE;
                    for (int i=1; i<=faceMap.Extent(); i++) {
                        hist.shapeMap[i-1].push_back(countFaces++);
                    }
                    history.push_back(hist);
                }
            }
        }

        this->Shape.setValue(comp);

        // make sure the 'PropertyShapeHistory' is not safed in undo/redo (#0001889)
        PropertyShapeHistory prop;
        prop.setValues(history);
        prop.setContainer(this);
        prop.touch();

        return App::DocumentObject::StdReturn;
    }
    catch (Standard_Failure& e) {
        return new App::DocumentObjectExecReturn(e.GetMessageString());
    }
}

