/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <fcntl.h>
# include <BRep_Builder.hxx>
# include <Interface_Static.hxx>
# include <TopTools_HSequenceOfShape.hxx>
# include <IGESControl_Controller.hxx>
# include <IGESControl_Reader.hxx>
# include <TopoDS.hxx>
# include <TopoDS_Shape.hxx>
# include <TopoDS_Shell.hxx>
# include <TopoDS_Solid.hxx>
# include <TopoDS_Compound.hxx>
# include <TopExp_Explorer.hxx>
# include <Message_MsgFile.hxx>
# include <TColStd_HSequenceOfTransient.hxx>
# include <TColStd_HSequenceOfTransient.hxx>
# include <IGESBasic_Group.hxx>
# include <IGESSolid_ManifoldSolid.hxx>
# include <IGESBasic_SingularSubfigure.hxx>

#include <XSControl_WorkSession.hxx>
#include <XSControl_TransferReader.hxx>
#include <XSControl_WorkSession.hxx>
#include <XSControl_TransferReader.hxx>
#include <Transfer_TransientProcess.hxx>

#include <Interface_EntityIterator.hxx>
#include <Quantity_Color.hxx>
#include <TCollection_ExtendedString.hxx>

#include "Base/Console.h"
#include "Base/Sequencer.h"
#include "App/Application.h"
#include "App/Document.h"

#include "ImportIges.h"
#include "PartFeature.h"
#include "ProgressIndicator.h"

using namespace Part;

int Part::ImportIgesParts(App::Document *pcDoc, const char* FileName)
{
    try {
        Base::FileInfo fi(FileName);
        // read iges file
        IGESControl_Controller::Init();

        // load data exchange message files
        Message_MsgFile::LoadFromEnv("CSF_XSMessage","IGES");

        // load shape healing message files
        Message_MsgFile::LoadFromEnv("CSF_SHMessageStd","SHAPEStd");

        IGESControl_Reader aReader;
        if (aReader.ReadFile((Standard_CString)FileName) != IFSelect_RetDone)
            throw Base::FileException("Error in reading IGES");

        // Ignore construction elements
        // http://www.opencascade.org/org/forum/thread_20603/?forum=3
        aReader.SetReadVisible(Standard_True);

        // check file conformity and output stats
        aReader.PrintCheckLoad(Standard_True,IFSelect_GeneralInfo);

#if 1
        std::string aName = fi.fileNamePure();

        // make model
        aReader.ClearShapes();
        //Standard_Integer nbRootsForTransfer = aReader.NbRootsForTransfer();
        aReader.TransferRoots();

        // put all other free-flying shapes into a single compound
        Standard_Boolean emptyComp = Standard_True;
        BRep_Builder builder;
        TopoDS_Compound comp;
        builder.MakeCompound(comp);

        Standard_Integer nbShapes = aReader.NbShapes();
        for (Standard_Integer i=1; i<=nbShapes; i++) {
            TopoDS_Shape aShape = aReader.Shape(i);
            if (!aShape.IsNull()) {
                if (aShape.ShapeType() == TopAbs_SOLID ||
                    aShape.ShapeType() == TopAbs_COMPOUND ||
                    aShape.ShapeType() == TopAbs_SHELL) {
                        App::DocumentObject* obj = pcDoc->addObject("Part::Feature", aName.c_str());
                        static_cast<Part::Feature*>(obj)->Shape.setValue(aShape);
                }
                else {
                    builder.Add(comp, aShape);
                    emptyComp = Standard_False;
                }
            }
        }
        if (!emptyComp) {
            std::string name = fi.fileNamePure();
            Part::Feature *pcFeature = static_cast<Part::Feature*>(pcDoc->addObject
                ("Part::Feature", name.c_str()));
            pcFeature->Shape.setValue(comp);
        }
#endif
    }
    catch (Standard_Failure& e) {
        throw Base::CADKernelError(e.GetMessageString());
    }

    return 0;
}
