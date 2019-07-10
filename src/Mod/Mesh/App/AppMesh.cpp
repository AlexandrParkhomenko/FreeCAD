/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include "FCConfig.h"

#include "Base/Console.h"
#include "Base/Interpreter.h"

#include "Mesh.h"
#include "MeshPy.h"
#include "MeshPointPy.h"
#include "FacetPy.h"
#include "MeshFeaturePy.h"
#include "FeatureMeshImport.h"
#include "FeatureMeshExport.h"
#include "FeatureMeshTransform.h"
#include "FeatureMeshTransformDemolding.h"
#include "FeatureMeshCurvature.h"
#include "FeatureMeshSegmentByMesh.h"
#include "FeatureMeshSetOperations.h"
#include "FeatureMeshDefects.h"
#include "FeatureMeshSolid.h"

namespace Mesh {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(Mesh)
{
    PyObject* meshModule = Mesh::initModule();
    Base::Console().Log("Loading Mesh module... done\n");

    // NOTE: To finish the initialization of our own type objects we must
    // call PyType_Ready, otherwise we run into a segmentation fault, later on.
    // This function is responsible for adding inherited slots from a type's base class.

    // add mesh elements
    Base::Interpreter().addType(&Mesh::MeshPointPy  ::Type,meshModule,"MeshPoint");
    Base::Interpreter().addType(&Mesh::FacetPy      ::Type,meshModule,"Facet");
    Base::Interpreter().addType(&Mesh::MeshPy       ::Type,meshModule,"Mesh");
    Base::Interpreter().addType(&Mesh::MeshFeaturePy::Type,meshModule,"Feature");

    // init Type system
    Mesh::PropertyNormalList    ::init();
    Mesh::PropertyCurvatureList ::init();
    Mesh::PropertyMeshKernel    ::init();

    Mesh::MeshObject            ::init();

    Mesh::Feature               ::init();
    Mesh::FeatureCustom         ::init();
    Mesh::FeaturePython         ::init();
    Mesh::Import                ::init();
    Mesh::Export                ::init();
    Mesh::Transform             ::init();
    Mesh::TransformDemolding    ::init();
    Mesh::Curvature             ::init();
    Mesh::SegmentByMesh         ::init();
    Mesh::SetOperations         ::init();
    Mesh::FixDefects            ::init();
    Mesh::HarmonizeNormals      ::init();
    Mesh::FlipNormals           ::init();
    Mesh::FixNonManifolds       ::init();
    Mesh::FixDuplicatedFaces    ::init();
    Mesh::FixDuplicatedPoints   ::init();
    Mesh::FixDegenerations      ::init();
    Mesh::FixDeformations       ::init();
    Mesh::FixIndices            ::init();
    Mesh::FillHoles             ::init();
    Mesh::RemoveComponents      ::init();

    Mesh::Sphere                ::init();
    Mesh::Ellipsoid             ::init();
    Mesh::Cylinder              ::init();
    Mesh::Cone                  ::init();
    Mesh::Torus                 ::init();
    Mesh::Cube                  ::init();

    PyMOD_Return(meshModule);
}
