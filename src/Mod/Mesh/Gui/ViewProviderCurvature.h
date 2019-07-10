/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_VIEWPROVIDER_MESH_CURVATURE_H
#define MESHGUI_VIEWPROVIDER_MESH_CURVATURE_H

#include "stdexport.h"
#include "Base/Observer.h"
#include "App/DocumentObserver.h"
#include "ViewProvider.h"

class SoSeparator;
class SbVec3f;
class SoSwitch;
class SoCoordinate3;
class SoNormal;
class SoIndexedFaceSet;
class SoFaceSet;
class SoPath;
class SoLocateHighlight;
class SoTransformerManip;

namespace Gui {
  class SoFCColorBar;
  class View3DInventorViewer;
}

namespace Mesh {
  class PropertyCurvatureList;
}

namespace MeshGui {

/** The ViewProviderMeshCurvature class is associated to the mesh curvature feature. It allows to display the most known types of
 * curvatures, such as Gaussian curvature, mean curvature, minimum and maximum curvature.
 * Moreover a color bar is also added to the scene.
 *
 * @author Werner Mayer
 */
class MeshGuiExport ViewProviderMeshCurvature : public Gui::ViewProviderDocumentObject,
                                                public App::DocumentObserver,
                                                public Base::Observer<int> {
    typedef Gui::ViewProviderDocumentObject inherited;

    PROPERTY_HEADER(MeshGui::ViewProviderMeshCurvature);

public:
    ViewProviderMeshCurvature();
    virtual ~ViewProviderMeshCurvature();

    App::PropertyMaterial TextureMaterial;

    /// Extracts the mesh data from the feature \a pcFeature and creates an Inventor node \a SoNode with these data. 
    void attach(App::DocumentObject* pcFeature);
    virtual bool useNewSelectionModel(void) const {return false;}
    /// Sets the viewing mode
    void setDisplayMode(const char* ModeName);
    /// get the default display mode
    virtual const char* getDefaultDisplayMode() const;
    /// Returns a list of all possible modes
    std::vector<std::string> getDisplayModes(void) const;
    /// Updates the mesh feature representation
    void updateData(const App::Property*);
    /// Returns a pixmap for the associated feature type
    QIcon getIcon() const;
    /// Once the color bar settinhs has been changed this method gets called to update the feature's representation
    void OnChange(Base::Subject<int> &rCaller,int rcReason);
    /// Returns a color bar
    SoSeparator* getFrontRoot(void) const;
    /// Hide the object in the view
    virtual void hide(void);
    /// Show the object in the view
    virtual void show(void);

public:
    static void curvatureInfoCallback(void * ud, SoEventCallback * n);

protected:
    void onChanged(const App::Property* prop);
    void setVertexCurvatureMode(int mode);
    std::string curvatureInfo(bool detail, int index1, int index2, int index3) const;

private:
    void init(const Mesh::PropertyCurvatureList *prop);

    void slotChangedObject(const App::DocumentObject& Obj, const App::Property& Prop);

protected:
    SoMaterial       * pcColorMat;
    SoGroup          * pcLinkRoot;
    Gui::SoFCColorBar* pcColorBar;
    SoDrawStyle      * pcColorStyle;
    SoSeparator      * pcColorRoot;

private:
    static bool addflag;
};

} // namespace MeshGui


#endif // MESHGUI_VIEWPROVIDER_MESH_CURVATURE_H

