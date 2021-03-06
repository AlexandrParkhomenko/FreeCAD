/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_VIEWPROVIDERMESHFACESET_H
#define MESHGUI_VIEWPROVIDERMESHFACESET_H

#include "stdexport.h"
#include "Mod/Mesh/Gui/ViewProvider.h"

namespace MeshGui {
class SoFCIndexedFaceSet;

/**
 * The ViewProviderMeshFaceSet class creates nodes for representing the mesh
 * data structure. Depending on the size of the mesh it uses two ways to
 * render it:
 * - For huge meshes it renders directly the data structure. Rendering directly
 *   the data structure has the advantage to save memory by not creating the
 *   according OpenInventor nodes which would more or less duplicate the
 *   memory for a mesh. Especially for huge with several hundred thousands or
 *   even millions of triangles, the amount of saved memory is considerable.
 * - For all other meshes it uses the appropriate OpenInventor nodes. Although
 *   this needs more memory its usage is much more flexible. It offers several
 *   nice features like a smooth-shaded appearance of a mesh whereas the
 *   OpenInventor nodes are already capable to do everything automatically,
 *   or the usage with textures.
 *
 * For more details @see SoFCMeshNode and SoFCMeshFaceSet.
 * @author Werner Mayer
 */
class MeshGuiExport ViewProviderMeshFaceSet : public ViewProviderMesh
{
    PROPERTY_HEADER(MeshGui::ViewProviderMeshFaceSet);

public:
    ViewProviderMeshFaceSet();
    virtual ~ViewProviderMeshFaceSet();

    void attach(App::DocumentObject *pcFeat);
    virtual void updateData(const App::Property*);

protected:
    void showOpenEdges(bool);
    SoShape* getShapeNode() const;
    SoNode* getCoordNode() const;

private:
    bool directRendering;
    unsigned long triangleCount;
    SoCoordinate3       * pcMeshCoord;
    SoFCIndexedFaceSet  * pcMeshFaces;
    SoFCMeshObjectNode  * pcMeshNode;
    SoFCMeshObjectShape * pcMeshShape;
};

} // namespace MeshGui


#endif // MESHGUI_VIEWPROVIDERMESHFACESET_H

