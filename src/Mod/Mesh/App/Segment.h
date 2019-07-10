/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESH_SEGMENT_H
#define MESH_SEGMENT_H

#include "stdexport.h"
#include <vector>
#include <string>
#include "Facet.h"
#include "Core/Iterator.h"

namespace Mesh
{

class MeshObject;

class Standard_EXPORT Segment
{
public:
    Segment(MeshObject*, bool mod);
    Segment(MeshObject*, const std::vector<unsigned long>& inds, bool mod);
    void addIndices(const std::vector<unsigned long>& inds);
    void removeIndices(const std::vector<unsigned long>& inds);
    const std::vector<unsigned long>& getIndices() const;
    bool isEmpty() const { return _indices.empty(); }

    Segment(const Segment&);
    const Segment& operator = (const Segment&);
    bool operator == (const Segment&) const;

    void setName(const std::string& n) { _name = n; }
    const std::string& getName() const { return _name; }

    void save(bool on) { _save = on; }
    bool isSaved() const { return _save; }

    // friends
    friend class MeshObject;

private:
    MeshObject* _mesh;
    std::vector<unsigned long> _indices;
    std::string _name;
    bool _save;
    bool _modifykernel;

public:
    class Standard_EXPORT const_facet_iterator
    {
    public:
        const_facet_iterator(const Segment*, std::vector<unsigned long>::const_iterator);
        const_facet_iterator(const const_facet_iterator& fi);
        ~const_facet_iterator();

        const_facet_iterator& operator=(const const_facet_iterator& fi);
        const Facet& operator*() const;
        const Facet* operator->() const;
        bool operator==(const const_facet_iterator& fi) const;
        bool operator!=(const const_facet_iterator& fi) const;
        const_facet_iterator& operator++();
        const_facet_iterator& operator--();
    private:
        void dereference();
        const Segment* _segment;
        Facet _facet;
        MeshCore::MeshFacetIterator _f_it;
        std::vector<unsigned long>::const_iterator _it;
    };

    const_facet_iterator facets_begin() const
    { return const_facet_iterator(this, _indices.begin()); }
    const_facet_iterator facets_end() const
    { return const_facet_iterator(this, _indices.end()); }
};

} // namespace Mesh


#endif // MESH_SEGMENT_H
