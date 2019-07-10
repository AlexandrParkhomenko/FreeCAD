/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef FEATURE_MESH_TRANSFORM_H
#define FEATURE_MESH_TRANSFORM_H

#include "MeshFeature.h"

#include "App/PropertyLinks.h"
#include "App/PropertyGeo.h"


namespace Mesh
{

/**
 * The Import class reads the any supported mesh format
 * into the FreeCAD workspace.
 * @author Werner Mayer
 */
class Transform : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::Transform);

public:
  Transform();

  App::PropertyLink   Source;
  App::PropertyMatrix Position;


  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  virtual App::DocumentObjectExecReturn *execute(void);
  /// returns the type name of the ViewProvider
  virtual const char* getViewProviderName(void) const { 
    return "MeshGui::ViewProviderMeshTransform"; 
  }
  //@}
};

}

#endif // FEATURE_MESH_TRANSFORM_H 
