/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef FEATURE_MESH_SEGMENTBYMESH_H
#define FEATURE_MESH_SEGMENTBYMESH_H

#include "App/PropertyStandard.h"

#include "MeshFeature.h"

#include "App/PropertyLinks.h"
#include "App/PropertyGeo.h"


namespace Mesh
{

/**
 * The SegmentByMesh class creates a mesh segment from two meshes whereat 
 * the facets of the first mesh that lie inside the second mesh build up the segment.  
 * @author Werner Mayer
 */
class SegmentByMesh : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::SegmentByMesh);

public:
  SegmentByMesh();

  App::PropertyLink Source;
  App::PropertyLink Tool;
  App::PropertyVector Base;
  App::PropertyVector Normal;


  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  App::DocumentObjectExecReturn *execute(void);
  short mustExecute() const;
  //@}
};

}

#endif // FEATURE_MESH_SEGMENTBYMESH_H 
