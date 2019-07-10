/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_VIEWPROVIDERMESHTRANSFORM_H
#define MESHGUI_VIEWPROVIDERMESHTRANSFORM_H

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
  class View3DInventorViewer;
}


#include "ViewProvider.h"

namespace MeshGui {

/** Like Mesh viewprovider but with manipulator
 */
class ViewProviderMeshTransform : public ViewProviderMesh
{
  PROPERTY_HEADER(MeshGui::ViewProviderMeshTransform);

public:
  ViewProviderMeshTransform();
  virtual ~ViewProviderMeshTransform();


  /** 
   * Extracts the mesh data from the feature \a pcFeature and creates
   * an Inventor node \a SoNode with these data. 
   */
  virtual void attach(App::DocumentObject *);

  /// set the viewing mode
  virtual void setDisplayMode(const char* ModeName);
  /// get the default display mode
  virtual const char* getDefaultDisplayMode() const;
  /// returns a list of all possible modes
  virtual std::vector<std::string> getDisplayModes(void) const;
  /// Update the Mesh representation
  virtual void updateData(const App::Property*);

protected:

  SoTransformerManip *pcTransformerDragger;
};

} // namespace MeshGui


#endif // MESHGUI_VIEWPROVIDERMESHTRANSFORM_H

