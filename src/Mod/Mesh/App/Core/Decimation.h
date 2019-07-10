/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESH_DECIMATION_H
#define MESH_DECIMATION_H

#include "stdexport.h"

namespace MeshCore
{
class MeshKernel;

class Standard_EXPORT MeshSimplify
{
public:
    MeshSimplify(MeshKernel&);
    ~MeshSimplify();
    void simplify(float tolerance, float reduction);

private:
    MeshKernel& myKernel;
};

} // namespace MeshCore


#endif  // MESH_DECIMATION_H
