/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESH_KDTREE_H
#define MESH_KDTREE_H

#include "stdexport.h"
#include "Elements.h"

namespace MeshCore
{

class Standard_EXPORT MeshKDTree
{
public:
    MeshKDTree(const std::vector<Base::Vector3f>& points);
    MeshKDTree(const MeshPointArray& points);
    ~MeshKDTree();

    bool IsEmpty() const;
    void Clear();
    void Optimize();

    unsigned long FindNearest(const Base::Vector3f& p, Base::Vector3f& n, float&) const;
    unsigned long FindNearest(const Base::Vector3f& p, float max_dist,
                              Base::Vector3f& n, float&) const;
    unsigned long FindExact(const Base::Vector3f& p) const;
    void FindInRange(const Base::Vector3f&, float, std::vector<unsigned long>&) const;

private:
    class Private;
    Private* d;

    MeshKDTree(const MeshKDTree&);
    void operator= (const MeshKDTree&);
};

} // namespace MeshCore


#endif  // MESH_KDTREE_H 
