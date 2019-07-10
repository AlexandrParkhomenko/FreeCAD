/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "KDTree.h"
#include <kdtree++/kdtree.hpp>

using namespace MeshCore;

struct Point3d 
{
   typedef float value_type;

   Point3d(const Base::Vector3f& f, unsigned long i) : p(f), i(i)
   {
   }

   inline value_type operator[](const int N) const
   {
       return p[N];
   }

   inline bool operator==(const Point3d& other) const
   {
      return (this->p) == (other.p);
   }

   inline bool operator!=(const Point3d& other) const
   {
      return (this->p) != (other.p);
   }

   inline void operator=(const Point3d& other)
   {
       this->p = other.p;
       this->i = other.i;
   }

   Base::Vector3f p;
   unsigned long i;
};

typedef KDTree::KDTree<3, Point3d> MyKDTree;

class MeshKDTree::Private
{
public:
    MyKDTree kd_tree;
};

MeshKDTree::MeshKDTree(const std::vector<Base::Vector3f>& points) : d(new Private)
{
    unsigned long index=0;
    for (std::vector<Base::Vector3f>::const_iterator it = points.begin(); it != points.end(); ++it) {
        d->kd_tree.insert(Point3d(*it, index++));
    }
}

MeshKDTree::MeshKDTree(const MeshPointArray& points) : d(new Private)
{
    unsigned long index=0;
    for (MeshPointArray::_TConstIterator it = points.begin(); it != points.end(); ++it) {
        d->kd_tree.insert(Point3d(*it, index++));
    }
}

MeshKDTree::~MeshKDTree()
{
    delete d;
}

bool MeshKDTree::IsEmpty() const
{
    return d->kd_tree.empty();
}

void MeshKDTree::Clear()
{
    d->kd_tree.clear();
}

void MeshKDTree::Optimize()
{
    d->kd_tree.optimize();
}

unsigned long MeshKDTree::FindNearest(const Base::Vector3f& p, Base::Vector3f& n, float& dist) const
{
    std::pair<MyKDTree::const_iterator, MyKDTree::distance_type> it =
        d->kd_tree.find_nearest(Point3d(p,0));
    if (it.first == d->kd_tree.end())
        return ULONG_MAX;
    unsigned long index = it.first->i;
    n = it.first->p;
    dist = it.second;
    return index;
}

unsigned long MeshKDTree::FindNearest(const Base::Vector3f& p, float max_dist,
                                      Base::Vector3f& n, float& dist) const
{
    std::pair<MyKDTree::const_iterator, MyKDTree::distance_type> it =
        d->kd_tree.find_nearest(Point3d(p,0), max_dist);
    if (it.first == d->kd_tree.end())
        return ULONG_MAX;
    unsigned long index = it.first->i;
    n = it.first->p;
    dist = it.second;
    return index;
}

unsigned long MeshKDTree::FindExact(const Base::Vector3f& p) const
{
    MyKDTree::const_iterator it = 
        d->kd_tree.find_exact(Point3d(p,0));
    if (it == d->kd_tree.end())
        return ULONG_MAX;
    unsigned long index = it->i;
    return index;
}

void MeshKDTree::FindInRange(const Base::Vector3f& p, float range, std::vector<unsigned long>& indices) const
{
    std::vector<Point3d> v;
    d->kd_tree.find_within_range(Point3d(p,0), range, std::back_inserter(v));
    indices.reserve(v.size());
    for (std::vector<Point3d>::iterator it = v.begin(); it != v.end(); ++it)
        indices.push_back(it->i);
}
