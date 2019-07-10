/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "Base/Interpreter.h"
#include "Base/Console.h"

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

#include "Gui/Application.h"
#include "Gui/BitmapFactory.h"
#include "Gui/WidgetFactory.h"

#include "Mod/Mesh/App/MeshProperties.h"

#include "images.h"
#include "DlgEvaluateMeshImp.h"
#include "PropertyEditorMesh.h"
#include "DlgSettingsMeshView.h"
#include "DlgSettingsImportExportImp.h"
#include "SoFCMeshObject.h"
#include "SoFCIndexedFaceSet.h"
#include "SoPolygon.h"
#include "ViewProvider.h"
#include "ViewProviderMeshFaceSet.h"
#include "ViewProviderCurvature.h"
#include "ViewProviderTransform.h"
#include "ViewProviderTransformDemolding.h"
#include "ViewProviderDefects.h"
#include "ViewProviderPython.h"
#include "Workbench.h"


// use a different name to CreateCommand()
void CreateMeshCommands(void);

void loadMeshResource()
{
    // add resources and reloads the translators
    Q_INIT_RESOURCE(Mesh);
}

namespace MeshGui {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("MeshGui")
    {
        initialize("This module is the MeshGui module."); // register with Python
    }

    virtual ~Module() {}

private:
};

PyObject* initModule()
{
    return (new Module)->module().ptr();
}

} // namespace MeshGui

/* Python entry */
PyMOD_INIT_FUNC(MeshGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(0);
    }

    // load dependent module
    try {
        Base::Interpreter().loadModule("Mesh");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(0);
    }
    PyObject* mod = MeshGui::initModule();
    Base::Console().Log("Loading GUI of Mesh module... done\n");

    // Register icons
    Gui::BitmapFactory().addXPM("mesh_fillhole", mesh_fillhole);

    // instantiating the commands
    CreateMeshCommands();
    (void)new MeshGui::CleanupHandler;
    
    // try to instantiate flat-mesh commands
    try{
        Base::Interpreter().runString("import MeshFlatteningCommand");
    } catch (Base::PyException &err){
        err.ReportException();
    }

    // register preferences pages
    (void)new Gui::PrefPageProducer<MeshGui::DlgSettingsMeshView> ("Display");
    (void)new Gui::PrefPageProducer<MeshGui::DlgSettingsImportExport>     ( QT_TRANSLATE_NOOP("QObject", "Import-Export") );

    MeshGui::SoFCMeshObjectElement              ::initClass();
    MeshGui::SoSFMeshObject                     ::initClass();
    MeshGui::SoFCMeshObjectNode                 ::initClass();
    MeshGui::SoFCMeshObjectShape                ::initClass();
    MeshGui::SoFCMeshSegmentShape               ::initClass();
    MeshGui::SoFCMeshObjectBoundary             ::initClass();
    MeshGui::SoFCMaterialEngine                 ::initClass();
    MeshGui::SoFCIndexedFaceSet                 ::initClass();
    MeshGui::SoFCMeshPickNode                   ::initClass();
    MeshGui::SoFCMeshGridNode                   ::initClass();
    MeshGui::SoPolygon                          ::initClass();
    MeshGui::PropertyMeshKernelItem             ::init();
    MeshGui::ViewProviderMesh                   ::init();
    MeshGui::ViewProviderMeshObject             ::init();
    MeshGui::ViewProviderIndexedFaceSet         ::init();
    MeshGui::ViewProviderMeshFaceSet            ::init();
    MeshGui::ViewProviderPython                 ::init();
    MeshGui::ViewProviderExport                 ::init();
    MeshGui::ViewProviderMeshCurvature          ::init();
    MeshGui::ViewProviderMeshTransform          ::init();
    MeshGui::ViewProviderMeshTransformDemolding ::init();
    MeshGui::ViewProviderMeshDefects            ::init();
    MeshGui::ViewProviderMeshOrientation        ::init();
    MeshGui::ViewProviderMeshNonManifolds       ::init();
    MeshGui::ViewProviderMeshNonManifoldPoints  ::init();
    MeshGui::ViewProviderMeshDuplicatedFaces    ::init();
    MeshGui::ViewProviderMeshDuplicatedPoints   ::init();
    MeshGui::ViewProviderMeshDegenerations      ::init();
    MeshGui::ViewProviderMeshIndices            ::init();
    MeshGui::ViewProviderMeshSelfIntersections  ::init();
    MeshGui::ViewProviderMeshFolds              ::init();
    MeshGui::Workbench                          ::init();
    Gui::ViewProviderBuilder::add(
        Mesh::PropertyMeshKernel::getClassTypeId(),
        MeshGui::ViewProviderMeshFaceSet::getClassTypeId());

    // add resources and reloads the translators
    loadMeshResource();

    PyMOD_Return(mod);
}
