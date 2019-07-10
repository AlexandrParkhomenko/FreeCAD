/***************************************************************************
 *   Copyright (c) 2012 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef MESHTRIM_H
#define MESHTRIM_H

#include "stdexport.h"
#include "Mod/Mesh/App/Core/Elements.h"
#include "Mod/Mesh/App/Core/MeshKernel.h"
#include "Base/Tools2D.h"
#include "Base/ViewProj.h"

namespace MeshCore {

/**
 * Checks the facets in 2D and then trim them in 3D
 */
class Standard_EXPORT MeshTrimming
{
public:
    enum TMode {INNER, OUTER};

public:
    MeshTrimming(MeshKernel& mesh, const Base::ViewProjMethod* pclProj, const Base::Polygon2d& rclPoly);
    ~MeshTrimming();

public:
    /**
     * Checks all facets for intersection with the polygon and writes all touched facets into the vector
     */
    void CheckFacets(const MeshFacetGrid& rclGrid, std::vector<unsigned long>& raulFacets) const;

    /**
     * The facets from raulFacets will be trimmed or deleted and aclNewFacets gives the new generated facets
     */
    void TrimFacets(const std::vector<unsigned long>& raulFacets, std::vector<MeshGeomFacet>& aclNewFacets);

    /**
     * Setter: Trimm INNER or OUTER
     */
    void SetInnerOrOuter(TMode tMode);
 
private:
    /**
     * Checks if the polygon cuts the facet
     */
    bool HasIntersection(const MeshGeomFacet& rclFacet) const;

    /**
     * Checks if a facet lies totally within a polygon
     */
    bool PolygonContainsCompleteFacet(bool bInner, unsigned long ulIndex) const;

    /**
     * Creates new facets from edge points of the facet
     */
    bool CreateFacets(unsigned long ulFacetPos, int iSide, const std::vector<Base::Vector3f>& raclPoints,
        std::vector<MeshGeomFacet>& aclNewFacets);

    /**
     * Creates new facets from edge points of the facet and a point inside the facet
     */
    bool CreateFacets(unsigned long ulFacetPos, int iSide, const std::vector<Base::Vector3f>& raclPoints,
        Base::Vector3f& clP3, std::vector<MeshGeomFacet>& aclNewFacets);

    /**
     * Checks if a polygon point lies within a facet
     */
    bool IsPolygonPointInFacet(unsigned long ulIndex, Base::Vector3f& clPoint);
    
    /**
     * Calculates the two intersection points between polygonline and facet in 2D 
     * and project the points back into 3D (not very exactly)
     */
    bool GetIntersectionPointsOfPolygonAndFacet(unsigned long ulIndex, int& iSide,
        std::vector<Base::Vector3f>& raclPoints) const;

    void AdjustFacet(MeshFacet& facet, int iInd);

private:
    MeshKernel& myMesh;
    bool myInner;
    std::vector<MeshGeomFacet> myTriangles;
    const Base::ViewProjMethod* myProj;
    const Base::Polygon2d& myPoly;
};

} //namespace MeshCore

#endif //MESHTRIM_H
