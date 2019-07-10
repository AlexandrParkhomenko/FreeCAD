/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <werner.wm.mayer@gmx.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_VIEWPROVIDERMESHNODE_H
#define MESHGUI_VIEWPROVIDERMESHNODE_H

#include "stdexport.h"
#include "Gui/ViewProviderGeometryObject.h"
#include "Mod/Mesh/App/Core/Elements.h"

#include <vector>
#include <Inventor/fields/SoSFVec2f.h>

class SbViewVolume;
class SoBaseColor;

namespace Gui {
  class SoFCSelection;
  class AbstractMouseModel;
}
namespace MeshGui {

/**
 * The ViewProviderMeshNode class creates a node representing the mesh data structure.
 * @author Werner Mayer
 */
class MeshGuiExport ViewProviderMeshNode : public Gui::ViewProviderGeometryObject
{
  PROPERTY_HEADER(TriangulationGui::ViewProviderMeshNode);

public:
  ViewProviderMeshNode();
  virtual ~ViewProviderMeshNode();
  
  // Display properties
  App::PropertyFloatConstraint LineWidth;
  App::PropertyFloatConstraint PointSize;
  App::PropertyBool OpenEdges;

  void attach(App::DocumentObject *pcFeat);
  virtual void updateData(const App::Property*);
  virtual QIcon getIcon() const;
  virtual void setDisplayMode(const char* ModeName);
  virtual std::vector<std::string> getDisplayModes() const;

  /** @name Polygon picking */
	//@{
  // Draws the picked polygon
  bool handleEvent(const SoEvent * const ev,Gui::View3DInventorViewer &Viewer);
  /// Sets the edit mnode
  bool setEdit(int ModNum=0);
  /// Unsets the edit mode
  void unsetEdit(void);
  /// Returns the edit mode
  const char* getEditModeName(void);
	//@}

protected:
  /// get called by the container whenever a property has been changed
  void onChanged(const App::Property* prop);
  void showOpenEdges( bool );
  void setOpenEdgeColorFrom( const App::Color& col );

  SoDrawStyle    *pcLineStyle;
  SoDrawStyle    *pcPointStyle;
  SoSeparator    *pcOpenEdge;
  SoBaseColor    *pOpenColor;

private:
  bool m_bEdit;

  static App::PropertyFloatConstraint::Constraints floatRange;
};

} // namespace MeshGui


#endif // MESHGUI_VIEWPROVIDERMESHNODE_H

