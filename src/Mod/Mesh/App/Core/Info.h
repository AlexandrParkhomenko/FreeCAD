/***************************************************************************
 *   Copyright (c) 2005 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESH_INFO_H
#define MESH_INFO_H

#include "stdexport.h"
#include "MeshKernel.h"

namespace MeshCore {

class MeshKernel;

/**
 * Determines information about the mesh data structure.
 */
class Standard_EXPORT MeshInfo
{
public:
  MeshInfo (const MeshKernel &rclM);
  virtual ~MeshInfo (void) {}
  /**
   * Writes general information about the mesh structure into the stream.
   */
  std::ostream& GeneralInformation (std::ostream& rclStream) const;
  /**
   * Writes detailed information about the mesh structure into the stream.
   */
  std::ostream& DetailedInformation (std::ostream& rclStream) const;
  /**
   * Writes internal information about the mesh structure into the stream.
   */
  std::ostream& InternalInformation (std::ostream& rclStream) const;
  /**
   * Writes topological information about the mesh structure into the stream.
   */
  std::ostream& TopologyInformation (std::ostream& rclStream) const;

protected:
  /**
   * Writes detailed point information.
   */
  std::ostream& DetailedPointInfo (std::ostream& rclStream) const;
  /**
   * Writes detailed edge information.
   */
  std::ostream& DetailedEdgeInfo (std::ostream& rclStream) const;
  /**
   * Writes detailed facet information.
   */
  std::ostream& DetailedFacetInfo (std::ostream& rclStream) const;
  /**
   * Writes internal point information.
   */
  std::ostream& InternalPointInfo (std::ostream& rclStream) const;
  /**
   * Writes internal facet information.
   */
  std::ostream& InternalFacetInfo (std::ostream& rclStream) const;


protected:
  const MeshKernel &_rclMesh;   // const reference to mesh data structure

private:
  MeshInfo(void);         // not accessible default constructor
};


} // namespace MeshCore

#endif
