/***************************************************************************
 *   Copyright (c) 2005 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <iomanip>
# include <ios>
# include <map>
# include <set>

#include "Info.h"
#include "Algorithm.h"
#include "Iterator.h"

#include "Base/Exception.h"

using namespace MeshCore;

MeshInfo::MeshInfo (const MeshKernel &rclM)
: _rclMesh(rclM)
{
}

std::ostream& MeshInfo::GeneralInformation (std::ostream &rclStream) const
{
  unsigned long ulCtPt, ulCtEd, ulCtFc;
  ulCtPt = _rclMesh.CountPoints();
  ulCtFc = _rclMesh.CountFacets();
  ulCtEd = _rclMesh.CountEdges();

  rclStream << "Mesh: ["
            << ulCtFc << " Faces, ";
          if (ulCtEd!=ULONG_MAX)
  rclStream << ulCtEd << " Edges, ";
          else
  rclStream << "Cannot determine number of edges, ";
  rclStream << ulCtPt << " Points"
            << "]" << std::endl;

  return rclStream;
}

std::ostream& MeshInfo::DetailedPointInfo (std::ostream& rclStream) const
{
  // print points
  unsigned long i;
  rclStream << _rclMesh.CountPoints() << " Points:" << std::endl;
  MeshPointIterator pPIter(_rclMesh), pPEnd(_rclMesh);
  pPIter.Begin();
  pPEnd.End();
  i = 0;

  rclStream.precision(3);
  rclStream.setf(std::ios::fixed | std::ios::showpoint | std::ios::showpos);
  while (pPIter < pPEnd)
  {
    rclStream << "P " << std::setw(4) << (i++)       << ": ("
                      << std::setw(8) << (*pPIter).x << ", "
                      << std::setw(8) << (*pPIter).y << ", "
                      << std::setw(8) << (*pPIter).z << ")" << std::endl;
    ++pPIter;
  }

  return rclStream;
}

std::ostream& MeshInfo::DetailedEdgeInfo (std::ostream& rclStream) const
{
  // print edges
  // get edges from facets
  std::map<std::pair<unsigned long, unsigned long>, int > lEdges;

  const MeshFacetArray& rFacets = _rclMesh.GetFacets();
  MeshFacetArray::_TConstIterator pFIter;
  pFIter = rFacets.begin();
  while (pFIter < rFacets.end())
  {
    const MeshFacet& rFacet = *pFIter;
    for ( int j=0; j<3; j++ )
    {
      unsigned long ulPt0 = std::min<unsigned long>(rFacet._aulPoints[j],  rFacet._aulPoints[(j+1)%3]);
      unsigned long ulPt1 = std::max<unsigned long>(rFacet._aulPoints[j],  rFacet._aulPoints[(j+1)%3]);
      std::pair<unsigned long, unsigned long> cEdge(ulPt0, ulPt1);
      lEdges[ cEdge ]++;
    }

    pFIter++;
  }

  // print edges
  rclStream << lEdges.size() << " Edges:" << std::endl;
  std::map<std::pair<unsigned long, unsigned long>, int >::const_iterator  pEIter;
  pEIter = lEdges.begin();

  rclStream.precision(3);
  rclStream.setf(std::ios::fixed | std::ios::showpoint | std::ios::showpos);
  unsigned long i=0;
  const MeshPointArray& rPoints = _rclMesh.GetPoints();
  while (pEIter != lEdges.end())
  {
    int ct = pEIter->second;
    const Base::Vector3f& rP0 = rPoints[ pEIter->first.first ];
    const Base::Vector3f& rP1 = rPoints[ pEIter->first.second ];

    rclStream << "E "    << std::setw(4) << (i++) << ": "
              << "  P (" << std::setw(8) << rP0.x << ", "
                         << std::setw(8) << rP0.y << ", "
                         << std::setw(8) << rP0.z << "); "
              << "  P (" << std::setw(8) << rP1.x << ", "
                         << std::setw(8) << rP1.y << ", "
                         << std::setw(8) << rP1.z << "),  B: " << (ct == 2 ? "n" : "y") << std::endl;
    ++pEIter;
  }

  return rclStream;
}

std::ostream& MeshInfo::DetailedFacetInfo (std::ostream& rclStream) const
{
  // print facets
  unsigned long i, j;
  rclStream << _rclMesh.CountFacets() << " Faces:" << std::endl;
  MeshFacetIterator pFIter(_rclMesh), pFEnd(_rclMesh);
  pFIter.Begin();
  pFEnd.End();
  i = 0;

  rclStream.precision(3);
  rclStream.setf(std::ios::fixed | std::ios::showpoint | std::ios::showpos);
  while (pFIter < pFEnd)
  {
    rclStream << "F "    << std::setw(4) << (i++) << ":" << std::endl;
    rclStream << "  N (" << std::setw(8) << (*pFIter).GetNormal().x << ", "
                         << std::setw(8) << (*pFIter).GetNormal().y << ", "
                         << std::setw(8) << (*pFIter).GetNormal().z << ")" << std::endl;
    for (j = 0; j < 3; j++)
    {
      rclStream << "  P (" << std::setw(8) << (*pFIter)._aclPoints[j].x << ", "
                           << std::setw(8) << (*pFIter)._aclPoints[j].y << ", "
                           << std::setw(8) << (*pFIter)._aclPoints[j].z << ")" << std::endl;
    }
    ++pFIter;
  }

  return rclStream;
}

std::ostream& MeshInfo::DetailedInformation (std::ostream& rclStream) const
{
  DetailedPointInfo( rclStream );
  DetailedEdgeInfo ( rclStream );
  DetailedFacetInfo( rclStream );

  return rclStream;
}

std::ostream& MeshInfo::InternalPointInfo (std::ostream& rclStream) const
{
  // print points
  unsigned long i;
  rclStream << _rclMesh.CountPoints() << " Points:" << std::endl;
  MeshPointIterator pPIter(_rclMesh), pPEnd(_rclMesh);
  pPIter.Begin();
  pPEnd.End();
  i = 0;

  rclStream.precision(3);
  rclStream.setf(std::ios::fixed | std::ios::showpoint | std::ios::showpos);
  while (pPIter < pPEnd)
  {
    rclStream << "P " << std::setw(4) << (i++)       << ": ("
                      << std::setw(8) << (*pPIter).x << ", "
                      << std::setw(8) << (*pPIter).y << ", "
                      << std::setw(8) << (*pPIter).z << ")";
    if (pPIter->IsValid() == true)
      rclStream << std::endl;
    else
      rclStream << " invalid" << std::endl;
    ++pPIter;
  }

  return rclStream;
}

std::ostream& MeshInfo::InternalFacetInfo (std::ostream& rclStream) const
{
  // print facets
  unsigned long i;
  rclStream << _rclMesh.CountFacets() << " Faces:" << std::endl;

  const MeshFacetArray& rFacets = _rclMesh.GetFacets();
  MeshFacetArray::_TConstIterator pFIter;
  pFIter = rFacets.begin();
  i = 0;
  while (pFIter < rFacets.end())
  {
    rclStream << "F " << std::setw(4) << (i++) << ": P ("
                      << std::setw(4) << pFIter->_aulPoints[0] << ", "
                      << std::setw(4) << pFIter->_aulPoints[1] << ", "
                      << std::setw(4) << pFIter->_aulPoints[2] << ")  "
             << "N (" << std::setw(4) << pFIter->_aulNeighbours[0] << ", "
                      << std::setw(4) << pFIter->_aulNeighbours[1] << ", "
                      << std::setw(4) << pFIter->_aulNeighbours[2] << ") ";

    if (pFIter->IsValid() == true)
      rclStream << std::endl;
    else
      rclStream << " invalid" << std::endl;

    pFIter++;
  }

  return rclStream;
}

std::ostream& MeshInfo::InternalInformation (std::ostream& rclStream) const
{
  InternalPointInfo( rclStream );
  InternalFacetInfo( rclStream );

  return rclStream;
}

std::ostream& MeshInfo::TopologyInformation (std::ostream& rclStream) const
{
    unsigned long index = 0;
    const MeshFacetArray& rFAry = _rclMesh.GetFacets();
    for (MeshFacetArray::_TConstIterator it = rFAry.begin(); it != rFAry.end(); ++it, ++index) {
        rclStream << "F " << std::setw(4) << index << ": P (" 
                  << it->_aulPoints[0] << ", "
                  << it->_aulPoints[1] << ", "
                  << it->_aulPoints[2] << "), N ("
                  << it->_aulNeighbours[0] << ", "
                  << it->_aulNeighbours[1] << ", "
                  << it->_aulNeighbours[2] << ")" << std::endl;
    }
    
    return rclStream;
}
