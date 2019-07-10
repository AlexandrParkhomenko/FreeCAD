/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef FEATURE_MESH_IMPORT_H
#define FEATURE_MESH_IMPORT_H

#include "MeshFeature.h"

#include "App/PropertyStandard.h"
#include "App/PropertyFile.h"

namespace Mesh
{

/**
 * The Import class reads the any supported mesh format
 * into the FreeCAD workspace.
 * @author Werner Mayer
 */
class Import : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::Import);

public:
  Import();

  App::PropertyFile FileName;

  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  App::DocumentObjectExecReturn *execute(void);
  short mustExecute(void) const;
  //@}
};

}

#endif // FEATURE_MESH_IMPORT_H 
