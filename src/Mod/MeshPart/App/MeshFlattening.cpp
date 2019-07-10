/***************************************************************************
 *   Copyright (c) 2017 Lorenz Lechner                                     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include "MeshFlattening.h"
#include "MeshFlatteningLscmRelax.h"
#include <Poly_Triangulation.hxx>
#include <BRep_Tool.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TopLoc_Location.hxx>
#include <Standard_Version.hxx>

#include <set>
#include <map>
#include <vector>
#include <exception>


std::vector<ColMat<double, 3>> getBoundaries(ColMat<double, 3> vertices, ColMat<long, 3> tris)
{
    // get a hashtable for all edges
    // e: v1, v2, num
    std::map<std::set<long>, std::vector<long>> hash_map;
    std::vector<std::set<long>> hash_list;
    std::map<long, std::vector<long>> neighbour_map;
    std::vector<long> edge_vector_0;
    std::vector<std::vector<long>> edge_vector;
    

    for (long i=0; i<tris.rows(); i++)
    {
        for (long j=0; j<3; j++)
        {
            long k = j + 1;
            if (k == 3)
                k = 0;
            long v1 = tris(i, j);
            long v2 = tris(i, k);
            std::set<long> hash {v1, v2};
            hash_list.push_back(hash);
            if (v1 < v2)
                hash_map[hash] = std::vector<long>{v1, v2, 0};
            else
                hash_map[hash] = std::vector<long>{v2, v1, 0};
        }
    }
    for (auto & hash: hash_list)
        hash_map[hash][2] += 1;

    for (auto &hash: hash_map)
    {
        if (hash.second[2] == 1)
        {
            long v0 = hash.second[0];
            long v1 = hash.second[1];

            neighbour_map[v0].push_back(v1);
            neighbour_map[v1].push_back(v0);
        }
    }


    while (neighbour_map.size() != 0)
    {
        long start_index = neighbour_map.begin()->first;
        long close_index = start_index;
        long next_index = neighbour_map[start_index][1];
        long temporary_next;
        edge_vector_0.clear();
        edge_vector_0.push_back(close_index);
        edge_vector_0.push_back(start_index);
        neighbour_map.erase(start_index);
        edge_vector_0.push_back(next_index);
        while (next_index != close_index)
        {
            temporary_next = neighbour_map[next_index][0];
            if (temporary_next != start_index)
            {
                start_index = next_index;
                next_index = temporary_next;
            }
            else
            {
                start_index = next_index;
                next_index = neighbour_map[start_index][1];
            }
            neighbour_map.erase(start_index);
            edge_vector_0.push_back(next_index);
            
        }
        edge_vector.push_back(edge_vector_0);
    }
    std::vector<ColMat<double, 3>> edges;
    for (auto &edge: edge_vector)
    {
        ColMat<double, 3> edge_vertices;
        edge_vertices.resize(edge.size(), 3);
        int i = 0;
        for (auto index: edge)
        {
            edge_vertices.row(i) = vertices.row(index);
            i++;
        }
        edges.push_back(edge_vertices);
    }
    return edges;
}

FaceUnwrapper::FaceUnwrapper(const TopoDS_Face& face)
{
    long i = 0;
//  transform to nurbs:
    TopLoc_Location location;
    
//  triangulate:
    const Handle(Poly_Triangulation) &triangulation = BRep_Tool::Triangulation(face, location);

    if (triangulation.IsNull())
        throw std::runtime_error("null triangulation in face construction");

//  compute uv coordinates
    if (triangulation->HasUVNodes())
    {
        const TColgp_Array1OfPnt2d &_uv_nodes = triangulation->UVNodes();
        this->uv_nodes.resize(triangulation->NbNodes(), 2);
        i = 0;
        for (Standard_Integer index = _uv_nodes.Lower(); index <= _uv_nodes.Upper(); ++index)
        {
            const gp_Pnt2d& _uv_node = _uv_nodes.Value(index);
            this->uv_nodes.row(i) << _uv_node.X(), _uv_node.Y();
            i++;
        }
    }
// 
    const TColgp_Array1OfPnt &_nodes = triangulation->Nodes();
    this->xyz_nodes.resize(triangulation->NbNodes(), 3);
    i = 0;
    for (Standard_Integer index = _nodes.Lower(); index <= _nodes.Upper(); ++index)
    {
        gp_Pnt _node = _nodes.Value(index);
        this->xyz_nodes.row(i) << _node.X(), _node.Y(), _node.Z();
        i++;
    }
    
    const Poly_Array1OfTriangle &_tris = triangulation->Triangles();
    this->tris.resize(triangulation->NbTriangles(), 3);
    i = 0;
    for (Standard_Integer index = _tris.Lower(); index <= _tris.Upper(); ++index)
    {
        int n1, n2, n3;
        Poly_Triangle _tri = _tris.Value(index);
        _tri.Get(n1, n2, n3);
        this->tris.row(i) << n1-1, n2-1, n3-1;
        i++;
    }
}

void FaceUnwrapper::findFlatNodes(int steps, double val)
{
    std::vector<long> fixed_pins;  //TODO: INPUT
    lscmrelax::LscmRelax mesh_flattener(this->xyz_nodes.transpose(), this->tris.transpose(), fixed_pins);
    mesh_flattener.lscm();
    for (int j=0; j<steps; j++)
        mesh_flattener.relax(val);
    this->ze_nodes = mesh_flattener.flat_vertices.transpose();
}

ColMat<double, 3> FaceUnwrapper::interpolateFlatFace(const TopoDS_Face& face)
{
    if (this->uv_nodes.size() == 0)
        throw(std::runtime_error("no uv-coordinates found, interpolating with nurbs is only possible if the Flattener was constructed with a nurbs."));
    
    // extract xyz poles, knots, weights, degree
    const Handle(Geom_Surface) &_surface = BRep_Tool::Surface(face);
    const Handle(Geom_BSplineSurface) &_bspline = Handle(Geom_BSplineSurface)::DownCast(_surface);
    const TColStd_Array1OfReal &_uknots = _bspline->UKnotSequence();
    const TColStd_Array1OfReal &_vknots = _bspline->VKnotSequence();

    Eigen::VectorXd weights;
    weights.resize(_bspline->NbUPoles() * _bspline->NbVPoles());
    long i = 0;
    for (long u=1; u <= _bspline->NbUPoles(); u++)
    {
        for (long v=1; v <= _bspline->NbVPoles(); v++)
        {
            weights[i] = _bspline->Weight(u, v);
            i++;
        }
    }

    Eigen::VectorXd u_knots;
    Eigen::VectorXd v_knots;
    u_knots.resize(_uknots.Length());
    v_knots.resize(_vknots.Length());
    for (long u=1; u <= _uknots.Length(); u++)
    {
        u_knots[u - 1] = _uknots.Value(u);
    }
    for (long v=1; v <= _vknots.Length(); v++)
    {
        v_knots[v - 1] = _vknots.Value(v);
    }
    

    nu = nurbs::NurbsBase2D(u_knots, v_knots, weights, _bspline->UDegree(), _bspline->VDegree());
    A = nu.getInfluenceMatrix(this->uv_nodes);
    
    Eigen::LeastSquaresConjugateGradient<spMat > solver;
    solver.compute(A);
    ColMat<double, 2> ze_poles;
    ColMat<double, 3> flat_poles;
    ze_poles.resize(weights.rows(), 2);
    flat_poles.resize(weights.rows(), 3);
    flat_poles.setZero();
    ze_poles = solver.solve(ze_nodes);
    flat_poles.col(0) << ze_poles.col(0);
    flat_poles.col(1) << ze_poles.col(1);
    return flat_poles;    
}


FaceUnwrapper::FaceUnwrapper(ColMat< double, int(3) > xyz_nodes, ColMat< long int, int(3) > tris)
{
    this->tris = tris;
    this->xyz_nodes = xyz_nodes;
    
}

std::vector<ColMat<double, 3>> FaceUnwrapper::getFlatBoundaryNodes()
{
    if (this->ze_nodes.size() == 0)
        throw(std::runtime_error("flat vertices not xet computed"));

    ColMat<double, 3> flat_vertices;
    flat_vertices.resize(this->ze_nodes.rows(), 3);
    flat_vertices.setZero();
    flat_vertices.col(0) << this->ze_nodes.col(0);
    flat_vertices.col(1) << this->ze_nodes.col(1);
    return getBoundaries(flat_vertices, this->tris);
}
