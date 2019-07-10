/***************************************************************************
 *   Copyright (c) 2005 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#include "stdexport.h"

#ifndef MESH_DEFINITIONS_H
#define MESH_DEFINITIONS_H

// default values
#define MESH_MIN_PT_DIST           1.0e-6f
#define MESH_MIN_EDGE_LEN          1.0e-3f
#define MESH_MIN_EDGE_ANGLE        2.0
#define MESH_REMOVE_MIN_LEN        true
#define MESH_REMOVE_G3_EDGES       true

/*
 * general constant definitions
 */
#define FLOAT_EPS   1.0e-4f 

#ifndef  FLOAT_MAX
# define FLOAT_MAX 1e30f
#endif

#ifndef  DOUBLE_MAX
# define DOUBLE_MAX 1.7976931348623157E+308    /* max decimal value of a "double"*/
#endif

#ifndef  DOUBLE_MIN
# define DOUBLE_MIN 2.2250738585072014E-308    /* min decimal value of a "double"*/
#endif

namespace MeshCore {

template <class Prec>
class Math
{
public:
    Standard_EXPORT static const Prec PI;
};

typedef Math<float> Mathf;
typedef Math<double> Mathd;

/**
 * Global defined tolerances used to compare points
 * for equality.
 */
class Standard_EXPORT MeshDefinitions
{
public:
  MeshDefinitions (void);
  virtual ~MeshDefinitions (void)
  {}

  static float  _fMinPointDistance;
  static float  _fMinPointDistanceP2;
  static float  _fMinPointDistanceD1;

  static float  _fMinEdgeLength;
  static bool  _bRemoveMinLength;

  static float _fMinEdgeAngle;

  static void  SetMinPointDistance (float fMin);
};

} // namespace MeshCore

#endif // MESH_DEFINITIONS_H 
