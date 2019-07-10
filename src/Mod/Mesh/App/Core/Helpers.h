/***************************************************************************
 *   Copyright (c) 2005 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESH_HELPERS_H
#define MESH_HELPERS_H

#include "stdexport.h"
#include "Elements.h"

#include "Base/Vector3D.h"

namespace MeshCore {


/**
 * Helper class for points.
 */
struct Standard_EXPORT MeshHelpPoint
{
  inline void Set (unsigned long ulCorner, unsigned long ulFacet, const Base::Vector3f &rclPt);

  inline bool operator < (const MeshHelpPoint &rclObj) const;
  inline bool operator == (const MeshHelpPoint &rclObj) const;

  unsigned long Index (void) const
  { return _ulInd >> 2; }

  unsigned long Corner (void) const
  { return _ulInd & 3; }

  MeshPoint _clPt;
  unsigned long     _ulInd;
};

/**
 * Helper class for list of points.
 */
struct MeshPointBuilder: public std::vector<MeshHelpPoint>
{
  inline void Add (unsigned long ulCorner, unsigned long ulFacet, const Base::Vector3f &rclPt);
};

/**
 * Helper class for edges.
 */
struct Standard_EXPORT MeshHelpBuilderEdge
{
  unsigned long Side (void) const
  { return _ulFIndex & 3; }

  unsigned long Index (void) const
  { return _ulFIndex >> 2; }

  inline void Set (unsigned long ulInd1, unsigned long ulInd2,
                                         unsigned long ulSide, unsigned long ulFInd);

  inline bool operator < (const MeshHelpBuilderEdge &rclObj) const;

  inline bool operator == (const MeshHelpBuilderEdge &rclObj) const;
  

  inline bool operator != (const MeshHelpBuilderEdge &rclObj) const;

  unsigned long  _ulFIndex;    // facet index
  unsigned long  _aulInd[2];   // point index
};

/**
 * Helper class to build up list of edges.
 */
struct MeshEdgeBuilder: public std::vector<MeshHelpBuilderEdge>
{
  typedef std::vector<MeshHelpBuilderEdge>::iterator  _TIterator;
  inline void Add (unsigned long ulInd1, unsigned long ulInd2, unsigned long ulSide, unsigned long ulFInd);
};

inline void MeshHelpPoint::Set (unsigned long ulCorner, unsigned long ulFacet, const Base::Vector3f &rclPt)
{
  _ulInd = (ulFacet << 2) | ulCorner;
  _clPt  = rclPt;
};

inline bool MeshHelpPoint::operator < (const MeshHelpPoint &rclObj) const
{
//   if (fabs(_clPt.x - rclObj._clPt.x) < MeshDefinitions::_fMinPointDistanceD1)
//   {
//     if (fabs(_clPt.y - rclObj._clPt.y) < MeshDefinitions::_fMinPointDistanceD1)
//     {
//       if (fabs(_clPt.z - rclObj._clPt.z) < MeshDefinitions::_fMinPointDistanceD1)
//         return false;
//       else
//         return _clPt.z < rclObj._clPt.z;
//     }
//     else
//       return _clPt.y < rclObj._clPt.y;
//   }
//   else
//     return _clPt.x < rclObj._clPt.x;

  if (_clPt.x == rclObj._clPt.x)
  {
    if (_clPt.y == rclObj._clPt.y)
      return _clPt.z < rclObj._clPt.z;
    else
      return _clPt.y < rclObj._clPt.y;
  }
  else
    return _clPt.x < rclObj._clPt.x;
}

inline bool MeshHelpPoint::operator == (const MeshHelpPoint &rclObj) const
{
  return Base::DistanceP2(_clPt, rclObj._clPt) < MeshDefinitions::_fMinPointDistanceP2;
/*
  if (fabs(_clPt.x - rclObj._clPt.x) < (MeshDefinitions::_fMinPointDistanceD1 + 1.0e-2f))
  {
    if (fabs(_clPt.y - rclObj._clPt.y) < (MeshDefinitions::_fMinPointDistanceD1 + 1.0e-2f))
    {
      if (fabs(_clPt.z - rclObj._clPt.z) < (MeshDefinitions::_fMinPointDistanceD1 + 1.0e-2f))
        return true;
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
*/
}

inline void MeshPointBuilder::Add (unsigned long ulCorner, unsigned long ulFacet, const Base::Vector3f &rclPt)
{
  MeshHelpPoint  clObj;
  clObj.Set(ulCorner, ulFacet, rclPt);
  push_back(clObj);
}

inline void MeshHelpBuilderEdge::Set ( unsigned long ulInd1, unsigned long ulInd2,
                                       unsigned long ulSide, unsigned long ulFInd)
{
  if (ulInd1 < ulInd2)
  {
    _aulInd[0] = ulInd1;
    _aulInd[1] = ulInd2; 
  }
  else
  {
    _aulInd[0] = ulInd2;
    _aulInd[1] = ulInd1; 
  }
  _ulFIndex = (ulFInd << 2) | ulSide;
}

inline bool MeshHelpBuilderEdge::operator < (const MeshHelpBuilderEdge &rclObj) const
{
  if (_aulInd[0] == rclObj._aulInd[0])
    return _aulInd[1] < rclObj._aulInd[1];
  else
    return _aulInd[0] < rclObj._aulInd[0];
}

inline bool MeshHelpBuilderEdge::operator == (const MeshHelpBuilderEdge &rclObj) const
{
  return (_aulInd[0] == rclObj._aulInd[0]) && (_aulInd[1] == rclObj._aulInd[1]);
}

inline bool MeshHelpBuilderEdge::operator != (const MeshHelpBuilderEdge &rclObj) const
{
  return (_aulInd[0] != rclObj._aulInd[0]) || (_aulInd[1] != rclObj._aulInd[1]);
}


inline void MeshEdgeBuilder::Add (unsigned long ulInd1, unsigned long ulInd2, 
                                  unsigned long ulSide, unsigned long ulFInd)
{
  MeshHelpBuilderEdge  clObj;
  clObj.Set(ulInd1, ulInd2, ulSide, ulFInd);
  push_back(clObj);
}

} // namespace MeshCore

#endif // MESH_HELPERS_H 
