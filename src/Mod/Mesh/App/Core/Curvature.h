/***************************************************************************
 *   Copyright (c) 2012 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHCORE_CURVATURE_H
#define MESHCORE_CURVATURE_H

#include "stdexport.h"
#include <vector>
#include "Base/Vector3D.h"

namespace MeshCore {

class MeshKernel;
class MeshRefPointToFacets;

/** Curvature information. */
struct Standard_EXPORT CurvatureInfo
{
    float fMaxCurvature, fMinCurvature;
    Base::Vector3f cMaxCurvDir, cMinCurvDir;
};

class Standard_EXPORT FacetCurvature
{
public:
    FacetCurvature(const MeshKernel& kernel, const MeshRefPointToFacets& search, float, unsigned long);
    CurvatureInfo Compute(unsigned long index) const;

private:
    const MeshKernel& myKernel;
    const MeshRefPointToFacets& mySearch;
    unsigned long myMinPoints;
    float myRadius;
};

class Standard_EXPORT MeshCurvature
{
public:
    MeshCurvature(const MeshKernel& kernel);
    MeshCurvature(const MeshKernel& kernel, const std::vector<unsigned long>& segm);
    float GetRadius() const { return myRadius; }
    void SetRadius(float r) { myRadius = r; }
    void ComputePerFace(bool parallel);
    void ComputePerVertex();
    const std::vector<CurvatureInfo>& GetCurvature() const { return myCurvature; }

private:
    const MeshKernel& myKernel;
    unsigned long myMinPoints;
    float myRadius;
    std::vector<unsigned long> mySegment;
    std::vector<CurvatureInfo> myCurvature;
};

} // MeshCore

#endif // MESHCORE_CURVATURE_H
