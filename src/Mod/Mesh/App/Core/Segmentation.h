/***************************************************************************
 *   Copyright (c) 2012 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHCORE_SEGMENTATION_H
#define MESHCORE_SEGMENTATION_H

#include "stdexport.h"
#include "MeshKernel.h"
#include "Curvature.h"
#include "Visitor.h"
#include <vector>

namespace MeshCore {

class PlaneFit;
class CylinderFit;
class SphereFit;
class MeshFacet;
typedef std::vector<unsigned long> MeshSegment;

class Standard_EXPORT MeshSurfaceSegment
{
public:
    MeshSurfaceSegment(unsigned long minFacets)
        : minFacets(minFacets) {}
    virtual ~MeshSurfaceSegment() {}
    virtual bool TestFacet (const MeshFacet &rclFacet) const = 0;
    virtual const char* GetType() const = 0;
    virtual void Initialize(unsigned long);
    virtual bool TestInitialFacet(unsigned long) const;
    virtual void AddFacet(const MeshFacet& rclFacet);
    void AddSegment(const std::vector<unsigned long>&);
    const std::vector<MeshSegment>& GetSegments() const { return segments; }
    MeshSegment FindSegment(unsigned long) const;

protected:
    std::vector<MeshSegment> segments;
    unsigned long minFacets;
};

// --------------------------------------------------------

class Standard_EXPORT MeshDistanceSurfaceSegment : public MeshSurfaceSegment
{
public:
    MeshDistanceSurfaceSegment(const MeshKernel& mesh, unsigned long minFacets, float tol)
        : MeshSurfaceSegment(minFacets), kernel(mesh), tolerance(tol) {}

protected:
    const MeshKernel& kernel;
    float tolerance;
};

class Standard_EXPORT MeshDistancePlanarSegment : public MeshDistanceSurfaceSegment
{
public:
    MeshDistancePlanarSegment(const MeshKernel& mesh, unsigned long minFacets, float tol);
    virtual ~MeshDistancePlanarSegment();
    bool TestFacet (const MeshFacet& rclFacet) const;
    const char* GetType() const { return "Plane"; }
    void Initialize(unsigned long);
    void AddFacet(const MeshFacet& rclFacet);

protected:
    Base::Vector3f basepoint;
    Base::Vector3f normal;
    PlaneFit* fitter;
};

class Standard_EXPORT AbstractSurfaceFit
{
public:
    AbstractSurfaceFit(){}
    virtual ~AbstractSurfaceFit(){}
    virtual const char* GetType() const = 0;
    virtual void Initialize(const MeshGeomFacet&) = 0;
    virtual bool TestTriangle(const MeshGeomFacet&) const = 0;
    virtual void AddTriangle(const MeshGeomFacet&) = 0;
    virtual bool Done() const = 0;
    virtual float Fit() = 0;
    virtual float GetDistanceToSurface(const Base::Vector3f&) const = 0;
};

class Standard_EXPORT PlaneSurfaceFit : public AbstractSurfaceFit
{
public:
    PlaneSurfaceFit();
    PlaneSurfaceFit(const Base::Vector3f& b, const Base::Vector3f& n);
    ~PlaneSurfaceFit();
    const char* GetType() const { return "Plane"; }
    void Initialize(const MeshGeomFacet&);
    bool TestTriangle(const MeshGeomFacet&) const;
    void AddTriangle(const MeshGeomFacet&);
    bool Done() const;
    float Fit();
    float GetDistanceToSurface(const Base::Vector3f&) const;

private:
    Base::Vector3f basepoint;
    Base::Vector3f normal;
    PlaneFit* fitter;
};

class Standard_EXPORT CylinderSurfaceFit : public AbstractSurfaceFit
{
public:
    CylinderSurfaceFit();
    CylinderSurfaceFit(const Base::Vector3f& b, const Base::Vector3f& a, float r);
    ~CylinderSurfaceFit();
    const char* GetType() const { return "Cylinder"; }
    void Initialize(const MeshGeomFacet&);
    bool TestTriangle(const MeshGeomFacet&) const;
    void AddTriangle(const MeshGeomFacet&);
    bool Done() const;
    float Fit();
    float GetDistanceToSurface(const Base::Vector3f&) const;

private:
    Base::Vector3f basepoint;
    Base::Vector3f axis;
    float radius;
    CylinderFit* fitter;
};

class Standard_EXPORT SphereSurfaceFit : public AbstractSurfaceFit
{
public:
    SphereSurfaceFit();
    SphereSurfaceFit(const Base::Vector3f& c, float r);
    ~SphereSurfaceFit();
    const char* GetType() const { return "Sphere"; }
    void Initialize(const MeshGeomFacet&);
    bool TestTriangle(const MeshGeomFacet&) const;
    void AddTriangle(const MeshGeomFacet&);
    bool Done() const;
    float Fit();
    float GetDistanceToSurface(const Base::Vector3f&) const;

private:
    Base::Vector3f center;
    float radius;
    SphereFit* fitter;
};

class Standard_EXPORT MeshDistanceGenericSurfaceFitSegment : public MeshDistanceSurfaceSegment
{
public:
    MeshDistanceGenericSurfaceFitSegment(AbstractSurfaceFit*, const MeshKernel& mesh,
                                         unsigned long minFacets, float tol);
    virtual ~MeshDistanceGenericSurfaceFitSegment();
    bool TestFacet (const MeshFacet& rclFacet) const;
    const char* GetType() const { return fitter->GetType(); }
    void Initialize(unsigned long);
    bool TestInitialFacet(unsigned long) const;
    void AddFacet(const MeshFacet& rclFacet);

protected:
    AbstractSurfaceFit* fitter;
};

// --------------------------------------------------------

class Standard_EXPORT MeshCurvatureSurfaceSegment : public MeshSurfaceSegment
{
public:
    MeshCurvatureSurfaceSegment(const std::vector<CurvatureInfo>& ci, unsigned long minFacets)
        : MeshSurfaceSegment(minFacets), info(ci) {}

protected:
    const std::vector<CurvatureInfo>& info;
};

class Standard_EXPORT MeshCurvaturePlanarSegment : public MeshCurvatureSurfaceSegment
{
public:
    MeshCurvaturePlanarSegment(const std::vector<CurvatureInfo>& ci, unsigned long minFacets, float tol)
        : MeshCurvatureSurfaceSegment(ci, minFacets), tolerance(tol) {}
    virtual bool TestFacet (const MeshFacet &rclFacet) const;
    virtual const char* GetType() const { return "Plane"; }

private:
    float tolerance;
};

class Standard_EXPORT MeshCurvatureCylindricalSegment : public MeshCurvatureSurfaceSegment
{
public:
    MeshCurvatureCylindricalSegment(const std::vector<CurvatureInfo>& ci, unsigned long minFacets,
                                    float tolMin, float tolMax, float curv)
        : MeshCurvatureSurfaceSegment(ci, minFacets), toleranceMin(tolMin), toleranceMax(tolMax) { curvature = curv;}
    virtual bool TestFacet (const MeshFacet &rclFacet) const;
    virtual const char* GetType() const { return "Cylinder"; }

private:
    float curvature;
    float toleranceMin;
    float toleranceMax;
};

class Standard_EXPORT MeshCurvatureSphericalSegment : public MeshCurvatureSurfaceSegment
{
public:
    MeshCurvatureSphericalSegment(const std::vector<CurvatureInfo>& ci, unsigned long minFacets, float tol, float curv)
        : MeshCurvatureSurfaceSegment(ci, minFacets), tolerance(tol) { curvature = curv;}
    virtual bool TestFacet (const MeshFacet &rclFacet) const;
    virtual const char* GetType() const { return "Sphere"; }

private:
    float curvature;
    float tolerance;
};

class Standard_EXPORT MeshCurvatureFreeformSegment : public MeshCurvatureSurfaceSegment
{
public:
    MeshCurvatureFreeformSegment(const std::vector<CurvatureInfo>& ci, unsigned long minFacets,
                                 float tolMin, float tolMax, float c1, float c2)
        : MeshCurvatureSurfaceSegment(ci, minFacets), c1(c1), c2(c2),
          toleranceMin(tolMin), toleranceMax(tolMax) {}
    virtual bool TestFacet (const MeshFacet &rclFacet) const;
    virtual const char* GetType() const { return "Freeform"; }

private:
    float c1, c2;
    float toleranceMin;
    float toleranceMax;
};

class Standard_EXPORT MeshSurfaceVisitor : public MeshFacetVisitor
{
public:
    MeshSurfaceVisitor (MeshSurfaceSegment& segm, std::vector<unsigned long> &indices);
    virtual ~MeshSurfaceVisitor ();
    bool AllowVisit (const MeshFacet& face, const MeshFacet&, 
                     unsigned long, unsigned long, unsigned short neighbourIndex);
    bool Visit (const MeshFacet & face, const MeshFacet &,
                unsigned long ulFInd, unsigned long);

protected:
    std::vector<unsigned long>  &indices;
    MeshSurfaceSegment& segm;
};

class Standard_EXPORT MeshSegmentAlgorithm
{
public:
    MeshSegmentAlgorithm(const MeshKernel& kernel) : myKernel(kernel) {}
    void FindSegments(std::vector<MeshSurfaceSegment*>&);

private:
    const MeshKernel& myKernel;
};

} // MeshCore

#endif // MESHCORE_SEGMENTATION_H
