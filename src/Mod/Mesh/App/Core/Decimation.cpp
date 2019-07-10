/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "Decimation.h"
#include "MeshKernel.h"
#include "Algorithm.h"
#include "Iterator.h"
#include "TopoAlgorithm.h"
#include "Base/Tools.h"
#include "Simplify.h"


using namespace MeshCore;

MeshSimplify::MeshSimplify(MeshKernel& mesh)
  : myKernel(mesh)
{
}

MeshSimplify::~MeshSimplify()
{
}

void MeshSimplify::simplify(float tolerance, float reduction)
{
    Simplify alg;

    const MeshPointArray& points = myKernel.GetPoints();
    for (std::size_t i = 0; i < points.size(); i++) {
        Simplify::Vertex v;
        v.p = points[i];
        alg.vertices.push_back(v);
    }

    const MeshFacetArray& facets = myKernel.GetFacets();
    for (std::size_t i = 0; i < facets.size(); i++) {
        Simplify::Triangle t;
        for (int j = 0; j < 3; j++)
            t.v[j] = facets[i]._aulPoints[j];
        alg.triangles.push_back(t);
    }

    int target_count = static_cast<int>(static_cast<float>(facets.size()) * (1.0f-reduction));

    // Simplification starts
    alg.simplify_mesh(target_count, tolerance);

    // Simplification done
    MeshPointArray new_points;
    new_points.reserve(alg.vertices.size());
    for (std::size_t i = 0; i < alg.vertices.size(); i++) {
        new_points.push_back(alg.vertices[i].p);
    }

    std::size_t numFacets = 0;
    for (std::size_t i = 0; i < alg.triangles.size(); i++) {
        if (!alg.triangles[i].deleted)
            numFacets++;
    }
    MeshFacetArray new_facets;
    new_facets.reserve(numFacets);
    for (std::size_t i = 0; i < alg.triangles.size(); i++) {
        if (!alg.triangles[i].deleted) {
            MeshFacet face;
            face._aulPoints[0] = alg.triangles[i].v[0];
            face._aulPoints[1] = alg.triangles[i].v[1];
            face._aulPoints[2] = alg.triangles[i].v[2];
            new_facets.push_back(face);
        }
    }

    myKernel.Adopt(new_points, new_facets, true);
}
