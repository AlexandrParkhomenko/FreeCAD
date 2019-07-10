/***************************************************************************
 *   Copyright (c) Juergen Riegel         <juergen.riegel@web.de>          *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESH_MESHPOINT_H
#define MESH_MESHPOINT_H

#include "stdexport.h"
#include "Base/Matrix.h"
#include "Base/Vector3D.h"

#include "Mesh.h"

using Base::Vector3d;

namespace Mesh
{
// forward declaration
class MeshObject;

/** The MeshPoint helper class
 * The MeshPoint class provides an interface for the MeshPointPy classes for
 * convenient access to the Mesh data structure. This class should not be used for
 * programming algorithms in C++. Use Mesh Core classes instead!
 */
class Standard_EXPORT MeshPoint : public Vector3d
{

public:
    /// simple constructor
    MeshPoint(const Vector3d& vec = Vector3d(),MeshObject* obj = 0, unsigned int index = UINT_MAX)
        :Vector3d(vec),Index(index),Mesh(obj)
    {}

    bool isBound(void) const {return Index != UINT_MAX;}

    unsigned int Index;
    Base::Reference<MeshObject> Mesh;
};

} // namespace Mesh


#endif // MESH_MESH_H
