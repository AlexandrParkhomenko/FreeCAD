/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_MESHEDITOR_H
#define MESHGUI_MESHEDITOR_H

#include "stdexport.h"
#include <QObject>
#include "Mod/Mesh/Gui/ViewProvider.h"
#include <boost/signals2.hpp>

class SoCoordinate3;
class SoFaceSet;
class SoEventCallback;
class SoPickedPoint;
class SoGroup;
class SoSeparator;
class SoRayPickAction;
class SbLine;
class SbVec3f;

namespace Gui { class View3DInventor; class View3DInventorViewer;}
namespace Mesh { class MeshObject; }
namespace Mesh { class Feature; }
namespace MeshGui {
class SoFCMeshPickNode;

/** The ViewProviderFace class is used to display a single face.
 * @author Werner Mayer
 */
class MeshGuiExport ViewProviderFace : public Gui::ViewProviderDocumentObject
{
    PROPERTY_HEADER(MeshGui::ViewProviderFace);

public:
    ViewProviderFace();
    virtual ~ViewProviderFace();

    // Build up the initial Inventor node
    void attach(App::DocumentObject* obj);
    void setDisplayMode(const char* ModeName);
    const char* getDefaultDisplayMode() const;
    std::vector<std::string> getDisplayModes(void) const;
    SoPickedPoint* getPickedPoint(const SbVec2s& pos, const Gui::View3DInventorViewer* viewer) const;

    ViewProviderMesh* mesh;
    std::vector<int> index;
    int current_index;

    SoCoordinate3   * pcCoords;
    SoFaceSet       * pcFaces;
    SoFCMeshPickNode* pcMeshPick;
};

/**
 * Display data of a mesh kernel.
 * \author Werner Mayer
 */
class MeshGuiExport MeshFaceAddition : public QObject
{
    Q_OBJECT

public:
    MeshFaceAddition(Gui::View3DInventor* parent);
    ~MeshFaceAddition();

    void startEditing(ViewProviderMesh*);

public Q_SLOTS:
    void finishEditing();

private Q_SLOTS:
    void addFace();
    void clearPoints();
    void flipNormal();

private:
    bool addMarkerPoint();
    void showMarker(SoPickedPoint*);
    static void addFacetCallback(void * ud, SoEventCallback * n);

private:
    ViewProviderFace* faceView;
};

class MeshGuiExport MeshHoleFiller
{
public:
    MeshHoleFiller()
    {
    }
    virtual ~MeshHoleFiller()
    {
    }
    virtual bool fillHoles(Mesh::MeshObject&, const std::list<std::vector<unsigned long> >&,
                           unsigned long, unsigned long)
    {
        return false;
    }
};

/**
 * Display data of a mesh kernel.
 * \author Werner Mayer
 */
class MeshGuiExport MeshFillHole : public QObject
{
    Q_OBJECT

public:
    MeshFillHole(MeshHoleFiller& hf, Gui::View3DInventor* parent);
    virtual ~MeshFillHole();

    void startEditing(ViewProviderMesh*);

public Q_SLOTS:
    void finishEditing();

private Q_SLOTS:
    void closeBridge();

private:
    typedef std::vector<unsigned long> TBoundary;
    typedef boost::signals2::connection Connection;

    static void fileHoleCallback(void * ud, SoEventCallback * n);
    void createPolygons();
    SoNode* getPickedPolygon(const SoRayPickAction& action) const;
    float findClosestPoint(const SbLine& ray, const TBoundary& polygon,
                           unsigned long&, SbVec3f&) const;
    void slotChangedObject(const App::DocumentObject& Obj, const App::Property& Prop);

private:
    SoSeparator* myBoundariesRoot;
    SoGroup* myBoundariesGroup;
    SoSeparator* myBoundaryRoot;
    SoSeparator* myBridgeRoot;
    SoCoordinate3* myVertex;
    std::map<SoNode*, TBoundary> myPolygons;
    Mesh::Feature* myMesh;
    int myNumPoints;
    unsigned long myVertex1;
    unsigned long myVertex2;
    TBoundary myPolygon;
    MeshHoleFiller& myHoleFiller;
    Connection myConnection;
};

} // namespace MeshGui


#endif // MESHGUI_MESHEDITOR_H

