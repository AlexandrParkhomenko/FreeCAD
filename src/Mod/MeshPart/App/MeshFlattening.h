/***************************************************************************
 *   Copyright (c) 2017 Lorenz Lechner                                     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESHFLATTENING
#define MESHFLATTENING

// idea:
// - unwrap any meshed shells and output a 2d face (meshing is done externally)
// - unwrap faces which are nurbs and return nurbs (no cuts, meshing internally)
// 	- TODO: map any curves from origin to flattened faces

#include "MeshFlatteningNurbs.h"
#include <BRepTools.hxx>
#include <TopoDS_Face.hxx>
#include <vector>

#include <Eigen/Geometry>
#include <Eigen/IterativeLinearSolvers>
#include <Eigen/SparseCore>
#include <Eigen/QR>

#include <vector>


typedef Eigen::Vector3d Vector3;
typedef Eigen::Vector2d Vector2;

template <typename type, unsigned int size>
using ColMat = Eigen::Matrix<type, Eigen::Dynamic, size>;

template <typename type, unsigned int size>
using RowMat = Eigen::Matrix<type, size, Eigen::Dynamic>;


typedef Eigen::Triplet<double> trip;
typedef Eigen::SparseMatrix<double> spMat;


std::vector<ColMat<double, 3>> getBoundaries(ColMat<double, 3> vertices, ColMat<long, 3> tris);

class FaceUnwrapper{
	nurbs::NurbsBase2D nu;
public:
	FaceUnwrapper(){}
	FaceUnwrapper(const TopoDS_Face & face);
        FaceUnwrapper(ColMat<double, 3> xyz_nodes, ColMat<long, 3> tris);
	void findFlatNodes(int steps, double val);
	ColMat<double, 3> interpolateFlatFace(const TopoDS_Face& face);
        std::vector<ColMat<double, 3>> getFlatBoundaryNodes();

	bool use_nurbs = true;
	// the mesh
	ColMat<long, 3> tris;  // input
	ColMat<long, 1> fixed_nodes; // input
	ColMat<double, 3> xyz_nodes; // compute from uv_mesh (xyz = A * poles)
	ColMat<double, 2> uv_nodes;  // input
	ColMat<double, 2> ze_nodes;  // copute

	// nurbs
	ColMat<double, 2> ze_poles;   // compute
	spMat A; // mapping between nurbs(poles) and mesh(vertices) computed with nurbs-basis-functions and uv_mesh

};

#endif // MESHFLATTENING 
