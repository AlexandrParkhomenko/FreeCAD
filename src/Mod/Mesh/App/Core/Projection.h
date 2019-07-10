/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESH_PROJECTION_H
#define MESH_PROJECTION_H

#include "stdexport.h"
#include <vector>
#include "Base/BoundBox.h"
#include "Base/Vector3D.h"

using Base::Vector3f;

#ifdef FC_USE_OCC
class TopoDS_Edge;
class TopoDS_Shape;
#endif

namespace MeshCore
{

class MeshFacetGrid;
class MeshKernel;
class MeshGeomFacet;

class Standard_EXPORT MeshProjection
{
public:
    MeshProjection(const MeshKernel&);
    ~MeshProjection();

    bool projectLineOnMesh(const MeshFacetGrid& grid, const Base::Vector3f& p1, unsigned long f1,
        const Base::Vector3f& p2, unsigned long f2, const Base::Vector3f& view,
        std::vector<Base::Vector3f>& polyline);
protected:
    bool bboxInsideRectangle (const Base::BoundBox3f& bbox, const Base::Vector3f& p1, const Base::Vector3f& p2, const Base::Vector3f& view) const;
    bool isPointInsideDistance (const Base::Vector3f& p1, const Base::Vector3f& p2, const Base::Vector3f& pt) const;
    bool connectLines(std::list< std::pair<Base::Vector3f, Base::Vector3f> >& cutLines, const Base::Vector3f& startPoint,
        const Base::Vector3f& endPoint, std::vector<Base::Vector3f>& polyline) const;

private:
    const MeshKernel& kernel;
};

#ifdef FC_USE_OCC
/// Helper class
struct SplitEdge
{
  unsigned long uE0, uE1; /**< start and endpoint of an edge */
  Base::Vector3f cPt; /**< Point on edge (\a uE0, \a uE1) */
};

/**
 * The MeshProjection class projects a shape onto a mesh.
 * @author Werner Mayer
 */
class Standard_EXPORT MeshProjection
{
public:
  /// Construction
  MeshProjection( const MeshKernel& rMesh);
  /// Destruction
  ~MeshProjection();

  /**
   * Searches all edges that intersect with the projected curve \a aShape. Therefore \a aShape must
   * contain shapes of type TopoDS_Edge, other shape types are ignored. A possible solution is
   * taken if the distance between the curve point and the projected point is <= \a fMaxDist.
   */
  void projectToMesh ( const TopoDS_Shape &aShape, float fMaxDist, std::vector<SplitEdge>& rSplitEdges ) const;
  /**
   * Cuts the mesh at the curve defined by \a aShape. This method call @ref projectToMesh() to get the
   * split the facet at the found points. @see projectToMesh() for more details.
   */
  void splitMeshByShape ( const TopoDS_Shape &aShape, float fMaxDist ) const;

protected:
  void projectEdgeToEdge( const TopoDS_Edge &aCurve, float fMaxDist, const MeshFacetGrid& rGrid, 
                          std::vector<SplitEdge>& rSplitEdges ) const;

private:
  const MeshKernel& _rcMesh;
};
#endif

} // namespace MeshCore

#endif  // MESH_PROJECTION_H 
