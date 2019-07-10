/***************************************************************************
 *   Copyright (c) 2017 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef MESHPARTGUI_CURVEONMESH_H
#define MESHPARTGUI_CURVEONMESH_H

#include <QObject>
#include <Geom_BSplineCurve.hxx>
#include <GeomAbs_Shape.hxx>
#include "Gui/ViewProviderDocumentObject.h"
#include <memory>

class SbVec3f;
class SoCoordinate3;
class SoDrawStyle;
class TopoDS_Edge;

namespace Gui {
class View3DInventor;
class ViewProvider;
}

namespace MeshPartGui
{

class ViewProviderCurveOnMesh : public Gui::ViewProviderDocumentObject
{
    PROPERTY_HEADER(MeshPartGui::ViewProviderCurveOnMesh);

public:
    ViewProviderCurveOnMesh();
    virtual ~ViewProviderCurveOnMesh();
    void addVertex(const SbVec3f&);
    void clearVertex();
    void setPoints(const std::vector<SbVec3f>&);
    void clearPoints();
    void setDisplayMode(const char* ModeName);

private:
    SoCoordinate3 * pcCoords;
    SoCoordinate3 * pcNodes;
    SoDrawStyle   * pcPointStyle;
    SoDrawStyle   * pcLinesStyle;
};

class CurveOnMeshHandler : public QObject
{
    Q_OBJECT

public:
    CurveOnMeshHandler(QObject* parent = 0);
    ~CurveOnMeshHandler();
    void setParameters(int maxDegree, GeomAbs_Shape cont, double tol3d, double angle);
    void enableCallback(Gui::View3DInventor* viewer);
    void disableCallback();

private:
    Handle(Geom_BSplineCurve) approximateSpline(const std::vector<SbVec3f>& points);
    void approximateEdge(const TopoDS_Edge&, double tolerance);
    void displaySpline(const Handle(Geom_BSplineCurve)&);
    std::vector<SbVec3f> getPoints() const;
    std::vector<SbVec3f> getVertexes() const;
    void closeWire();
    bool tryCloseWire(const SbVec3f&) const;

private Q_SLOTS:
    void onContextMenu();
    void onCreate();
    void onClear();
    void onCancel();
    void onCloseWire();

private:
    class Private;
    std::unique_ptr<Private> d_ptr;
};

}

#endif // MESHPARTGUI_CURVEONMESH_H
