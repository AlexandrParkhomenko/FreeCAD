/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <sstream>

#include "Facet.h"
#include "Mesh.h"

using namespace Mesh;

Facet::Facet(const MeshCore::MeshFacet& face, MeshObject* obj, unsigned long index)
  : Index(index), Mesh(obj)
{
    for (int i=0; i<3; i++) {
        PIndex[i] = face._aulPoints[i];
        NIndex[i] = face._aulNeighbours[i];
    }
    if (Mesh.isValid() && index != ULONG_MAX) {
        for (int i=0; i<3; i++) {
            Base::Vector3d vert = Mesh->getPoint(PIndex[i]);
            _aclPoints[i].Set((float)vert.x, (float)vert.y, (float)vert.z);
        }
    }
}

Facet::Facet(const Facet& f)
  : MeshCore::MeshGeomFacet(f), Index(f.Index), Mesh(f.Mesh)
{
    for (int i=0; i<3; i++) {
        PIndex[i] = f.PIndex[i];
        NIndex[i] = f.NIndex[i];
    }
}

Facet::~Facet()
{
}

void Facet::operator = (const Facet& f)
{
    MeshCore::MeshGeomFacet::operator = (f);
    Mesh  = f.Mesh;
    Index = f.Index;
    for (int i=0; i<3; i++) {
        PIndex[i] = f.PIndex[i];
        NIndex[i] = f.NIndex[i];
    }
}
