/***************************************************************************
 *   Copyright (c) 2005 Berthold Grupp                                     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "stdexport.h"
#include <set>
#include <vector>

#include "MeshKernel.h"
#include "Base/Vector3D.h"

namespace Base {
class SequencerLauncher;
}

namespace MeshCore
{
class MeshKernel;
class MeshPoint;
class MeshGeomFacet;

/**
 * Class for creating the mesh structure by adding facets. Building the structure needs 3 steps:
 * 1. initializing  
 * 2. adding the facets
 * 3. finishing
 * \code
 * // Sample Code for building a mesh structure
 * MeshBuilder builder(someMeshReference);
 * builder.Initialize(numberOfFacets);
 * ...
 * for (...)
 *   builder.AddFacet(...);
 * ...
 * builder.Finish();
 * \endcode
 * @author Berthold Grupp
 */
class Standard_EXPORT MeshBuilder
{
private:
    /** @name Helper class */
    //@{
    class Edge
    {
        public:
        unsigned long	pt1, pt2, facetIdx;

        Edge (unsigned long p1, unsigned long p2, unsigned long idx)
        {
            facetIdx = idx;
            if (p1 > p2)
            {
                pt1 = p2;
                pt2 = p1;
            }
            else
            {
                pt1 = p1;
                pt2 = p2;
            }
        }

        bool operator < (const Edge &e) const
        {
            return (pt1 == e.pt1) ? (pt2 < e.pt2) : (pt1 < e.pt1);
        }

        bool operator > (const Edge &e) const
        {
            return (pt1 == e.pt1) ? (pt2 > e.pt2) : (pt1 > e.pt1);
        }

        bool operator == (const Edge &e) const
        {
            return (pt1 == e.pt1) && (pt2 == e.pt2);
        }
    };
    //@}

    MeshKernel& _meshKernel;
    std::set<MeshPoint> _points;
    Base::SequencerLauncher* _seq;

    // keep an array of iterators pointing to the vertex inside the set to save memory
    typedef std::pair<std::set<MeshPoint>::iterator, bool> MeshPointIterator;
    std::vector<MeshPointIterator> _pointsIterator;
    unsigned long _ptIdx;

    void SetNeighbourhood  ();
    // As it's forbidden to insert a degenerated facet but insert its vertices anyway we must remove them 
    void RemoveUnreferencedPoints();

public:
    MeshBuilder(MeshKernel &rclM);
    ~MeshBuilder(void);

    /**
     * Set the tolerance for the comparison of points. Normally you don't need to set the tolerance.
     */
    void SetTolerance(float);

    /** Initializes the class. Must be done before adding facets 
     * @param ctFacets count of facets. 
     * @param deletion if true (default) the mesh-kernel will be cleared
     *     otherwise you can add new facets on an existing mesh-kernel
     * @remarks To be efficient you should add exactly \a ctFacets with
     * AddFacet(), otherwise you'll possibly run into wastage of memory
     * and performance problems.
     */
    void Initialize (unsigned long ctFacets, bool deletion = true);

    /** adding facets */
    /** Add new facet
     * @param facet \a the facet
     * @param takeFlag if true the flag from the MeshGeomFacet will be taken
     * @param takeProperty
     */
    void AddFacet (const MeshGeomFacet& facet, bool takeFlag = false, bool takeProperty = false);
    /** Add new facet
     */
    void AddFacet (const Base::Vector3f& pt1, const Base::Vector3f& pt2, const Base::Vector3f& pt3, const Base::Vector3f& normal, unsigned char flag = 0, unsigned long prop = 0);
    /** Add new facet
     * @param facetPoints Array of vectors (size 4) in order of vec1, vec2,
     *                    vec3, normal
     * @param flag
     * @param prop
     */
    void AddFacet (Base::Vector3f* facetPoints, unsigned char flag = 0, unsigned long prop = 0);

    /** Finishes building up the mesh structure. Must be done after adding facets.
     * @param freeMemory if false (default) only the memory of internal
     * structures gets freed, otherwise  additional unneeded memory in the
     * mesh structure is tried to be freed.
     * @remarks If you have called AddFacet() as many times as specified in
     * Initialize() then absolutely no memory is wasted and you can leave the
     * default value.
     */
    void Finish (bool freeMemory=false);

    friend class MeshKernel;

private:
    float _fSaveTolerance;
};

/**
 * Class for creating the mesh structure by adding facets. Building the structure needs 3 steps:
 * 1. initializing  
 * 2. adding the facets
 * 3. finishing
 * \code
 * // Sample Code for building a mesh structure
 * MeshFastBuilder builder(someMeshReference);
 * builder.Initialize(numberOfFacets);
 * ...
 * for (...)
 *   builder.AddFacet(...);
 * ...
 * builder.Finish();
 * \endcode
 * @author Werner Mayer
 */
class Standard_EXPORT MeshFastBuilder
{
private:
    MeshKernel& _meshKernel;

public:
    MeshFastBuilder(MeshKernel &rclM);
    ~MeshFastBuilder(void);

    /** Initializes the class. Must be done before adding facets 
     * @param ctFacets count of facets.
     */
    void Initialize (unsigned long ctFacets);
    /** Add new facet
     */
    void AddFacet (const Base::Vector3f* facetPoints);
    /** Add new facet
     */
    void AddFacet (const MeshGeomFacet& facetPoints);

    /** Finishes building up the mesh structure. Must be done after adding facets.
     */
    void Finish ();

private:
    struct Private;
    Private* p;
};

} // namespace MeshCore

#endif 
