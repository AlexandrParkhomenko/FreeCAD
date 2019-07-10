/***************************************************************************
 *   Copyright (c) 2005 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include <cmath>

#include "Definitions.h"
#include "Base/Tools.h"

namespace MeshCore {

template<> const float  Math<float> ::PI = (float)(4.0*atan(1.0));
template<> const double Math<double>::PI =         4.0*atan(1.0);

float  MeshDefinitions::_fMinPointDistance    =  float(MESH_MIN_PT_DIST);
float  MeshDefinitions::_fMinPointDistanceP2  =  _fMinPointDistance * _fMinPointDistance;
float  MeshDefinitions::_fMinPointDistanceD1  =  _fMinPointDistance;
float  MeshDefinitions::_fMinEdgeLength       =  MESH_MIN_EDGE_LEN;
bool   MeshDefinitions::_bRemoveMinLength     =  MESH_REMOVE_MIN_LEN;
float  MeshDefinitions::_fMinEdgeAngle        =  Base::toRadians<float>(MESH_MIN_EDGE_ANGLE);

MeshDefinitions::MeshDefinitions (void)
{
}

void MeshDefinitions::SetMinPointDistance (float fMin)
{
  _fMinPointDistance   = fMin;
  _fMinPointDistanceP2 = fMin * fMin;
  _fMinPointDistanceD1 = float(sqrt((fMin * fMin) / 3.0f));
}

}
