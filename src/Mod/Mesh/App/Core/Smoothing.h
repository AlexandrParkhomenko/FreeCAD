/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESH_SMOOTHING_H
#define MESH_SMOOTHING_H

#include "stdexport.h"
#include <vector>

namespace MeshCore
{
class MeshKernel;
class MeshRefPointToPoints;
class MeshRefPointToFacets;

/** Base class for smoothing algorithms. */
class Standard_EXPORT AbstractSmoothing
{
public:
    enum Component { 
        Tangential,         ///< Smooth tangential direction
        Normal,             ///< Smooth normal direction
        TangentialNormal    ///< Smooth tangential and normal direction
    };

    enum Continuity { 
        C0, 
        C1, 
        C2 
    };

    AbstractSmoothing(MeshKernel&);
    virtual ~AbstractSmoothing();
    void initialize(Component comp, Continuity cont);

    /** Smooth the triangle mesh. */
    virtual void Smooth(unsigned int) = 0;
    virtual void SmoothPoints(unsigned int, const std::vector<unsigned long>&) = 0;

protected:
    MeshKernel& kernel;

    float tolerance;
    Component   component;
    Continuity  continuity;
};

class Standard_EXPORT PlaneFitSmoothing : public AbstractSmoothing
{
public:
    PlaneFitSmoothing(MeshKernel&);
    virtual ~PlaneFitSmoothing();
    void Smooth(unsigned int);
    void SmoothPoints(unsigned int, const std::vector<unsigned long>&);
};

class Standard_EXPORT LaplaceSmoothing : public AbstractSmoothing
{
public:
    LaplaceSmoothing(MeshKernel&);
    virtual ~LaplaceSmoothing();
    void Smooth(unsigned int);
    void SmoothPoints(unsigned int, const std::vector<unsigned long>&);
    void SetLambda(double l) { lambda = l;}

protected:
    void Umbrella(const MeshRefPointToPoints&,
                  const MeshRefPointToFacets&, double);
    void Umbrella(const MeshRefPointToPoints&,
                  const MeshRefPointToFacets&, double,
                  const std::vector<unsigned long>&);

protected:
    double lambda;
};

class Standard_EXPORT TaubinSmoothing : public LaplaceSmoothing
{
public:
    TaubinSmoothing(MeshKernel&);
    virtual ~TaubinSmoothing();
    void Smooth(unsigned int);
    void SmoothPoints(unsigned int, const std::vector<unsigned long>&);
    void SetMicro(double m) { micro = m;}

protected:
    double micro;
};

} // namespace MeshCore


#endif  // MESH_SMOOTHING_H 
