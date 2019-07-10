/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <BRepAlgoAPI_Fuse.hxx>
# include <BRepCheck_Analyzer.hxx>
# include <Standard_Failure.hxx>
# include <TopoDS_Iterator.hxx>
# include <TopTools_IndexedMapOfShape.hxx>
# include <TopExp.hxx>


#include "FeaturePartFuse.h"
#include "modelRefine.h"
#include "App/Application.h"
#include "Base/Parameter.h"
#include "Base/Exception.h"

using namespace Part;

PROPERTY_SOURCE(Part::Fuse, Part::Boolean)


Fuse::Fuse(void)
{
}

BRepAlgoAPI_BooleanOperation* Fuse::makeOperation(const TopoDS_Shape& base, const TopoDS_Shape& tool) const
{
    // Let's call algorithm computing a fuse operation:
    return new BRepAlgoAPI_Fuse(base, tool);
}

// ----------------------------------------------------

PROPERTY_SOURCE(Part::MultiFuse, Part::Feature)


MultiFuse::MultiFuse(void)
{
    ADD_PROPERTY(Shapes,(0));
    Shapes.setSize(0);
    ADD_PROPERTY_TYPE(History,(ShapeHistory()), "Boolean", (App::PropertyType)
        (App::Prop_Output|App::Prop_Transient|App::Prop_Hidden), "Shape history");
    History.setSize(0);

    ADD_PROPERTY_TYPE(Refine,(0),"Boolean",(App::PropertyType)(App::Prop_None),"Refine shape (clean up redundant edges) after this boolean operation");

    //init Refine property
    Base::Reference<ParameterGrp> hGrp = App::GetApplication().GetUserParameter()
        .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part/Boolean");
    this->Refine.setValue(hGrp->GetBool("RefineModel", false));

}

short MultiFuse::mustExecute() const
{
    if (Shapes.isTouched())
        return 1;
    return 0;
}

App::DocumentObjectExecReturn *MultiFuse::execute(void)
{
    std::vector<TopoDS_Shape> s;
    std::vector<App::DocumentObject*> obj = Shapes.getValues();

    std::vector<App::DocumentObject*>::iterator it;
    for (it = obj.begin(); it != obj.end(); ++it) {
        if ((*it)->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId())) {
            s.push_back(static_cast<Part::Feature*>(*it)->Shape.getValue());
        }
    }

    bool argumentsAreInCompound = false;
    TopoDS_Shape compoundOfArguments;

    //if only one source shape, and it is a compound - fuse children of the compound
    if (s.size() == 1){
        compoundOfArguments = s[0];
        if (compoundOfArguments.ShapeType() == TopAbs_COMPOUND){
            s.clear();
            TopoDS_Iterator it(compoundOfArguments);
            for (; it.More(); it.Next()) {
                const TopoDS_Shape& aChild = it.Value();
                s.push_back(aChild);
            }
            argumentsAreInCompound = true;
        }
    }

    if (s.size() >= 2) {
        try {
            std::vector<ShapeHistory> history;
#if OCC_VERSION_HEX <= 0x060800
            TopoDS_Shape resShape = s.front();
            if (resShape.IsNull())
                throw NullShapeException("Input shape is null");
            for (std::vector<TopoDS_Shape>::iterator it = s.begin()+1; it != s.end(); ++it) {
                if (it->IsNull())
                    throw NullShapeException("Input shape is null");

                // Let's call algorithm computing a fuse operation:
                BRepAlgoAPI_Fuse mkFuse(resShape, *it);
                // Let's check if the fusion has been successful
                if (!mkFuse.IsDone()) 
                    throw BooleanException("Fusion failed");
                resShape = mkFuse.Shape();

                ShapeHistory hist1 = buildHistory(mkFuse, TopAbs_FACE, resShape, mkFuse.Shape1());
                ShapeHistory hist2 = buildHistory(mkFuse, TopAbs_FACE, resShape, mkFuse.Shape2());
                if (history.empty()) {
                    history.push_back(hist1);
                    history.push_back(hist2);
                }
                else {
                    for (std::vector<ShapeHistory>::iterator jt = history.begin(); jt != history.end(); ++jt)
                        *jt = joinHistory(*jt, hist1);
                    history.push_back(hist2);
                }
            }
#else
            BRepAlgoAPI_Fuse mkFuse;
            TopTools_ListOfShape shapeArguments,shapeTools;
            const TopoDS_Shape& shape = s.front();
            if (shape.IsNull())
                throw Base::RuntimeError("Input shape is null");
            shapeArguments.Append(shape);

            for (std::vector<TopoDS_Shape>::iterator it = s.begin()+1; it != s.end(); ++it) {
                if (it->IsNull())
                    throw Base::RuntimeError("Input shape is null");
                shapeTools.Append(*it);
            }

            mkFuse.SetArguments(shapeArguments);
            mkFuse.SetTools(shapeTools);
            mkFuse.Build();
            if (!mkFuse.IsDone())
                throw Base::RuntimeError("MultiFusion failed");

            TopoDS_Shape resShape = mkFuse.Shape();
            for (std::vector<TopoDS_Shape>::iterator it = s.begin(); it != s.end(); ++it) {
                history.push_back(buildHistory(mkFuse, TopAbs_FACE, resShape, *it));
            }
#endif
            if (resShape.IsNull())
                throw Base::RuntimeError("Resulting shape is null");

            Base::Reference<ParameterGrp> hGrp = App::GetApplication().GetUserParameter()
                .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part/Boolean");
            if (hGrp->GetBool("CheckModel", false)) {
                BRepCheck_Analyzer aChecker(resShape);
                if (! aChecker.IsValid() ) {
                    return new App::DocumentObjectExecReturn("Resulting shape is invalid");
                }
            }
            if (this->Refine.getValue()) {
                try {
                    TopoDS_Shape oldShape = resShape;
                    BRepBuilderAPI_RefineModel mkRefine(oldShape);
                    resShape = mkRefine.Shape();
                    ShapeHistory hist = buildHistory(mkRefine, TopAbs_FACE, resShape, oldShape);
                    for (std::vector<ShapeHistory>::iterator jt = history.begin(); jt != history.end(); ++jt)
                        *jt = joinHistory(*jt, hist);
                }
                catch (Standard_Failure&) {
                    // do nothing
                }
            }

            this->Shape.setValue(resShape);


            if (argumentsAreInCompound){
                //combine histories of every child of source compound into one
                ShapeHistory overallHist;
                TopTools_IndexedMapOfShape facesOfCompound;
                TopAbs_ShapeEnum type = TopAbs_FACE;
                TopExp::MapShapes(compoundOfArguments, type, facesOfCompound);
                for (std::size_t iChild = 0; iChild < history.size(); iChild++){ //loop over children of source compound
                    //for each face of a child, find the inex of the face in compound, and assign the corresponding right-hand-size of the history
                    TopTools_IndexedMapOfShape facesOfChild;
                    TopExp::MapShapes(s[iChild], type, facesOfChild);
                    for(std::pair<const int,ShapeHistory::List> &histitem: history[iChild].shapeMap){ //loop over elements of history - that is - over faces of the child of source compound
                        int iFaceInChild = histitem.first;
                        ShapeHistory::List &iFacesInResult = histitem.second;
                        TopoDS_Shape srcFace = facesOfChild(iFaceInChild + 1); //+1 to convert our 0-based to OCC 1-bsed conventions
                        int iFaceInCompound = facesOfCompound.FindIndex(srcFace)-1;
                        overallHist.shapeMap[iFaceInCompound] = iFacesInResult; //this may overwrite existing info if the same face is used in several children of compound. This shouldn't be a problem, because the histories should match anyway...
                    }
                }
                history.clear();
                history.push_back(overallHist);
            }
            this->History.setValues(history);
        }
        catch (Standard_Failure& e) {
            return new App::DocumentObjectExecReturn(e.GetMessageString());
        }
    }
    else {
        throw Base::CADKernelError("Not enough shape objects linked");
    }

    return App::DocumentObject::StdReturn;
}
