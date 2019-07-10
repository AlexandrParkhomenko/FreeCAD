/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Sequencer.h"
#include "Base/Matrix.h"
using Base::Matrix4D;
#include "FeatureMeshTransform.h"

#include "App/PropertyLinks.h"
#include "App/PropertyGeo.h"

using namespace Mesh;
using namespace MeshCore;

PROPERTY_SOURCE(Mesh::Transform, Mesh::Feature)


Transform::Transform(void)
{
  ADD_PROPERTY(Source  ,(0));
  ADD_PROPERTY(Position,(Matrix4D()));
}

App::DocumentObjectExecReturn *Transform::execute(void)
{
/*
  Feature *pcFirst  = dynamic_cast<Feature*>(Source.getValue());
  if(!pcFirst || pcFirst->isError())
    return new App::DocumentObjectExecReturn("Unknown Error");

  Matrix4D Matrix =Position.getValue();

 
  MeshCore::MeshKernel *pcKernel = new MeshCore::MeshKernel(pcFirst->Mesh.getValue()); // Result Meshkernel
  pcKernel->Transform(Matrix);
  Mesh.setValue(pcKernel);
*/
  return App::DocumentObject::StdReturn;
}

