/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESH_FACET_H
#define MESH_FACET_H

#include "stdexport.h"
#include "Base/Matrix.h"
#include "Base/Vector3D.h"
#include "Base/Handle.h"

#include "Core/Elements.h"

namespace Mesh
{
// forward declaration
class MeshObject;

/** The Facet helper class
 * The MeshFacet class provides an interface for the MeshFacetPy class for
 * convenient access to the Mesh data structure. This class should not be used
 * for programming algorithms in C++. Use Mesh Core classes instead!
 */
class Standard_EXPORT Facet : public MeshCore::MeshGeomFacet
{
public:
    Facet(const MeshCore::MeshFacet& face = MeshCore::MeshFacet(), MeshObject* obj = 0, unsigned long index = ULONG_MAX);
    Facet(const Facet& f);
    ~Facet();

    bool isBound(void) const {return Index != ULONG_MAX;}
    void operator = (const Facet& f);

    unsigned long Index;
    unsigned long PIndex[3];
    unsigned long NIndex[3];
    Base::Reference<MeshObject> Mesh;
};

} // namespace Mesh


#endif // MESH_FACET_H
