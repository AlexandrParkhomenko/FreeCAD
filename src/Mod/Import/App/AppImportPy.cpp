/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include "FCConfig.h"
# include <climits>
# include <Standard_Version.hxx>
# include <NCollection_Vector.hxx>
# include <TDocStd_Document.hxx>
# include <XCAFApp_Application.hxx>
# include <TDocStd_Document.hxx>
# include <XCAFApp_Application.hxx>
# include <XCAFDoc_DocumentTool.hxx>
# include <XCAFDoc_ShapeTool.hxx>
# include <STEPCAFControl_Reader.hxx>
# include <STEPCAFControl_Writer.hxx>
# include <STEPControl_Writer.hxx>
# include <IGESCAFControl_Reader.hxx>
# include <IGESCAFControl_Writer.hxx>
# include <IGESControl_Controller.hxx>
# include <IGESData_GlobalSection.hxx>
# include <IGESData_IGESModel.hxx>
# include <IGESToBRep_Actor.hxx>
# include <Interface_Static.hxx>
# include <Transfer_TransientProcess.hxx>
# include <XSControl_WorkSession.hxx>
# include <XSControl_TransferReader.hxx>
# include <APIHeaderSection_MakeHeader.hxx>
# include <OSD_Exception.hxx>

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

#include "ImportOCAF.h"
#include "ExportOCAF.h"
//#include "ImportOCAFAssembly.h"
#include "Base/PyObjectBase.h"
#include "Base/Console.h"
#include "App/Application.h"
#include "App/Document.h"
#include "App/DocumentObjectPy.h"
#include "Mod/Part/App/PartFeature.h"
#include "Mod/Part/App/ProgressIndicator.h"
#include "Mod/Part/App/ImportIges.h"
#include "Mod/Part/App/ImportStep.h"
#include "Mod/Part/App/TopoShape.h"
#include "Mod/Part/App/TopoShapePy.h"
#include "Mod/Part/App/PartFeature.h"
#include "Mod/Part/App/PartFeaturePy.h"

namespace Import {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("Import")
    {
        add_varargs_method("open",&Module::importer,
            "open(string) -- Open the file and create a new document."
        );
        add_varargs_method("insert",&Module::importer,
            "insert(string,string) -- Insert the file into the given document."
        );
        add_varargs_method("export",&Module::exporter,
            "export(list,string) -- Export a list of objects into a single file."
        );
       initialize("This module is the Import module."); // register with Python       
    }

    virtual ~Module() {}

private:
    Py::Object importer(const Py::Tuple& args)
    {
        char* Name;
        char* DocName=0;
        if (!PyArg_ParseTuple(args.ptr(), "et|s","utf-8",&Name,&DocName))
            throw Py::Exception();

        std::string Utf8Name = std::string(Name);
        PyMem_Free(Name);
        std::string name8bit = Utf8Name;

        try {
            //Base::Console().Log("Insert in Part with %s",Name);
            Base::FileInfo file(Utf8Name.c_str());

            App::Document *pcDoc = 0;
            if (DocName) {
                pcDoc = App::GetApplication().getDocument(DocName);
            }
            if (!pcDoc) {
                pcDoc = App::GetApplication().newDocument("Unnamed");
            }

            Handle(XCAFApp_Application) hApp = XCAFApp_Application::GetApplication();
            Handle(TDocStd_Document) hDoc;
            hApp->NewDocument(TCollection_ExtendedString("MDTV-CAF"), hDoc);

            if (file.hasExtension(".stp") || file.hasExtension(".step")) {
                try {
                    STEPCAFControl_Reader aReader;
                    aReader.SetColorMode(true);
                    aReader.SetNameMode(true);
                    aReader.SetLayerMode(true);
                    if (aReader.ReadFile((Standard_CString)(name8bit.c_str())) != IFSelect_RetDone) {
                        throw Py::Exception(PyExc_IOError, "cannot read STEP file");
                    }

                    aReader.Transfer(hDoc);
                }
                catch (OSD_Exception& e) {
                    Base::Console().Error("%s\n", e.GetMessageString());
                    Base::Console().Message("Try to load STEP file without colors...\n");

                    Part::ImportStepParts(pcDoc,Utf8Name.c_str());
                    pcDoc->recompute();
                }
            }
            else if (file.hasExtension(".igs") || file.hasExtension(".iges")) {
                Base::Reference<ParameterGrp> hGrp = App::GetApplication().GetUserParameter()
                    .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part")->GetGroup("IGES");

                try {
                    IGESControl_Controller::Init();
                    IGESCAFControl_Reader aReader;
                    // http://www.opencascade.org/org/forum/thread_20603/?forum=3
                    aReader.SetReadVisible(hGrp->GetBool("SkipBlankEntities", true)
                        ? Standard_True : Standard_False);
                    aReader.SetColorMode(true);
                    aReader.SetNameMode(true);
                    aReader.SetLayerMode(true);
                    if (aReader.ReadFile((Standard_CString)(name8bit.c_str())) != IFSelect_RetDone) {
                        throw Py::Exception(PyExc_IOError, "cannot read IGES file");
                    }

                    aReader.Transfer(hDoc);
                    // http://opencascade.blogspot.de/2009/03/unnoticeable-memory-leaks-part-2.html
                    Handle(IGESToBRep_Actor)::DownCast(aReader.WS()->TransferReader()->Actor())
                            ->SetModel(new IGESData_IGESModel);
                }
                catch (OSD_Exception& e) {
                    Base::Console().Error("%s\n", e.GetMessageString());
                    Base::Console().Message("Try to load IGES file without colors...\n");

                    Part::ImportIgesParts(pcDoc,Utf8Name.c_str());
                    pcDoc->recompute();
                }
            }
            else {
                throw Py::Exception(Base::BaseExceptionFreeCADError, "no supported file format");
            }

#if 1
            Import::ImportOCAFCmd ocaf(hDoc, pcDoc, file.fileNamePure());
            ocaf.loadShapes();
#else
            Import::ImportXCAF xcaf(hDoc, pcDoc, file.fileNamePure());
            xcaf.loadShapes();
#endif
            pcDoc->recompute();
            hApp->Close(hDoc);

            std::map<Part::Feature*, std::vector<App::Color> > colorMap = ocaf.getPartColorsMap();
            if (!colorMap.empty()) {
                Py::List list;
                for (auto it : colorMap) {
                    Py::Tuple tuple(2);
                    tuple.setItem(0, Py::asObject(it.first->getPyObject()));

                    App::PropertyColorList colors;
                    colors.setValues(it.second);
                    tuple.setItem(1, Py::asObject(colors.getPyObject()));

                    list.append(tuple);
                }

                return list;
            }
        }
        catch (Standard_Failure& e) {
            throw Py::Exception(Base::BaseExceptionFreeCADError, e.GetMessageString());
        }
        catch (const Base::Exception& e) {
            throw Py::RuntimeError(e.what());
        }

        return Py::None();
    }
    Py::Object exporter(const Py::Tuple& args)
    {
        PyObject* object;
        char* Name;
        if (!PyArg_ParseTuple(args.ptr(), "Oet",&object,"utf-8",&Name))
            throw Py::Exception();

        std::string Utf8Name = std::string(Name);
        PyMem_Free(Name);
        std::string name8bit = Utf8Name;

        try {
            Py::Sequence list(object);
            Handle(XCAFApp_Application) hApp = XCAFApp_Application::GetApplication();
            Handle(TDocStd_Document) hDoc;
            hApp->NewDocument(TCollection_ExtendedString("MDTV-CAF"), hDoc);

            //bool keepExplicitPlacement = list.size() > 1;
            bool keepExplicitPlacement = Standard_True;
            Import::ExportOCAFCmd ocaf(hDoc, keepExplicitPlacement);

            std::map<Part::Feature*, std::vector<App::Color> > partColors;
            std::vector<Part::Feature*> partObjects;

            for (Py::Sequence::iterator it = list.begin(); it != list.end(); ++it) {
                PyObject* item = (*it).ptr();
                if (PyObject_TypeCheck(item, &(App::DocumentObjectPy::Type))) {
                    App::DocumentObject* obj = static_cast<App::DocumentObjectPy*>(item)->getDocumentObjectPtr();
                    if (obj->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId())) {
                        Part::Feature* part = static_cast<Part::Feature*>(obj);
                        partObjects.push_back(part);
                    }
                    else {
                        Base::Console().Message("'%s' is not a shape, export will be ignored.\n", obj->Label.getValue());
                    }
                }
                else if (PyTuple_Check(item) && PyTuple_Size(item) == 2) {
                    Py::Tuple tuple(*it);
                    Py::Object item0 = tuple.getItem(0);
                    Py::Object item1 = tuple.getItem(1);
                    if (PyObject_TypeCheck(item0.ptr(), &(App::DocumentObjectPy::Type))) {
                        App::DocumentObject* obj = static_cast<App::DocumentObjectPy*>(item0.ptr())->getDocumentObjectPtr();
                        if (obj->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId())) {
                            Part::Feature* part = static_cast<Part::Feature*>(obj);
                            App::PropertyColorList colors;
                            colors.setPyObject(item1.ptr());

                            partObjects.push_back(part);
                            partColors[part] = colors.getValues();
                        }
                        else {
                            Base::Console().Message("'%s' is not a shape, export will be ignored.\n", obj->Label.getValue());
                        }
                    }
                }
            }

            ocaf.setPartColorsMap(partColors);

            // That stuff is exporting a list of selected objects into FreeCAD Tree
            std::vector <TDF_Label> hierarchical_label;
            std::vector <TopLoc_Location> hierarchical_loc;
            std::vector <App::DocumentObject*> hierarchical_part;

            for (auto it : partObjects) {
                ocaf.exportObject(it, hierarchical_label, hierarchical_loc, hierarchical_part);
            }

            // Free Shapes must have absolute placement and not explicit
            std::vector <TDF_Label> FreeLabels;
            std::vector <int> part_id;
            ocaf.getFreeLabels(hierarchical_label, FreeLabels, part_id);
            // Got issue with the colors as they are coming from the View Provider they can't be determined into
            // the App Code.
            std::vector< std::vector<App::Color> > Colors;
            ocaf.getPartColors(hierarchical_part, FreeLabels, part_id, Colors);
            ocaf.reallocateFreeShape(hierarchical_part, FreeLabels, part_id, Colors);

            // Update is not performed automatically anymore: https://tracker.dev.opencascade.org/view.php?id=28055
            XCAFDoc_DocumentTool::ShapeTool(hDoc->Main())->UpdateAssemblies();

            Base::FileInfo file(Utf8Name.c_str());
            if (file.hasExtension(".stp") || file.hasExtension(".step")) {
                //Interface_Static::SetCVal("write.step.schema", "AP214IS");
                STEPCAFControl_Writer writer;
                Interface_Static::SetIVal("write.step.assembly",1);
                // writer.SetColorMode(Standard_False);
                writer.Transfer(hDoc, STEPControl_AsIs);

                // edit STEP header
                APIHeaderSection_MakeHeader makeHeader(writer.ChangeWriter().Model());
                Base::Reference<ParameterGrp> hGrp = App::GetApplication().GetUserParameter()
                    .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part")->GetGroup("STEP");

                makeHeader.SetName(new TCollection_HAsciiString((Standard_CString)Utf8Name.c_str()));
                makeHeader.SetAuthorValue (1, new TCollection_HAsciiString(hGrp->GetASCII("Author", "Author").c_str()));
                makeHeader.SetOrganizationValue (1, new TCollection_HAsciiString(hGrp->GetASCII("Company").c_str()));
                makeHeader.SetOriginatingSystem(new TCollection_HAsciiString(App::GetApplication().getExecutableName()));
                makeHeader.SetDescriptionValue(1, new TCollection_HAsciiString("FreeCAD Model"));
                IFSelect_ReturnStatus ret = writer.Write(name8bit.c_str());
                if (ret == IFSelect_RetError || ret == IFSelect_RetFail || ret == IFSelect_RetStop) {
                    PyErr_Format(PyExc_IOError, "Cannot open file '%s'", Utf8Name.c_str());
                    throw Py::Exception();
                }
            }
            else if (file.hasExtension(".igs") || file.hasExtension(".iges")) {
                IGESControl_Controller::Init();
                IGESCAFControl_Writer writer;
                IGESData_GlobalSection header = writer.Model()->GlobalSection();
                header.SetAuthorName(new TCollection_HAsciiString(Interface_Static::CVal("write.iges.header.author")));
                header.SetCompanyName(new TCollection_HAsciiString(Interface_Static::CVal("write.iges.header.company")));
                header.SetSendName(new TCollection_HAsciiString(Interface_Static::CVal("write.iges.header.product")));
                writer.Model()->SetGlobalSection(header);
                writer.Transfer(hDoc);
                Standard_Boolean ret = writer.Write(name8bit.c_str());
                if (!ret) {
                    PyErr_Format(PyExc_IOError, "Cannot open file '%s'", Utf8Name.c_str());
                    throw Py::Exception();
                }
            }

            hApp->Close(hDoc);
        }
        catch (Standard_Failure& e) {
            throw Py::Exception(Base::BaseExceptionFreeCADError, e.GetMessageString());
        }
        catch (const Base::Exception& e) {
            throw Py::RuntimeError(e.what());
        }

        return Py::None();
    }

};

PyObject* initModule()
{
    return (new Module)->module().ptr();
}

} // namespace Import
