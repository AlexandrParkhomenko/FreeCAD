/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef FEATURE_MESH_SOLID_H
#define FEATURE_MESH_SOLID_H

#include "MeshFeature.h"

#include "App/PropertyStandard.h"
#include "App/PropertyLinks.h"

namespace Mesh
{

/**
 * @author Werner Mayer
 */
class Sphere : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::Sphere);

public:
  Sphere();

  App::PropertyFloatConstraint Radius;
  App::PropertyIntegerConstraint Sampling;

  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  App::DocumentObjectExecReturn *execute(void);
  short mustExecute() const;
  //@}
};

// -------------------------------------------------------------

class Ellipsoid : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::Ellipsoid);

public:
  Ellipsoid();

  App::PropertyFloatConstraint Radius1;
  App::PropertyFloatConstraint Radius2;
  App::PropertyIntegerConstraint Sampling;

  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  App::DocumentObjectExecReturn *execute(void);
  short mustExecute() const;
  //@}
};

// -------------------------------------------------------------

class Cylinder : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::Cylinder);

public:
  Cylinder();

  App::PropertyFloatConstraint Radius;
  App::PropertyFloatConstraint Length;
  App::PropertyFloatConstraint EdgeLength;
  App::PropertyBool Closed;
  App::PropertyIntegerConstraint Sampling;

  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  App::DocumentObjectExecReturn *execute(void);
  short mustExecute() const;
  //@}
};

// -------------------------------------------------------------

class Cone : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::Cone);

public:
  Cone();

  App::PropertyFloatConstraint Radius1;
  App::PropertyFloatConstraint Radius2;
  App::PropertyFloatConstraint Length;
  App::PropertyFloatConstraint EdgeLength;
  App::PropertyBool Closed;
  App::PropertyIntegerConstraint Sampling;

  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  App::DocumentObjectExecReturn *execute(void);
  short mustExecute() const;
  //@}
};

// -------------------------------------------------------------

class Torus : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::Torus);

public:
  Torus();

  App::PropertyFloatConstraint Radius1;
  App::PropertyFloatConstraint Radius2;
  App::PropertyIntegerConstraint Sampling;

  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  App::DocumentObjectExecReturn *execute(void);
  short mustExecute() const;
  //@}
};

// -------------------------------------------------------------

class Cube : public Mesh::Feature
{
  PROPERTY_HEADER(Mesh::Cube);

public:
  Cube();

  App::PropertyFloatConstraint Length;
  App::PropertyFloatConstraint Width;
  App::PropertyFloatConstraint Height;

  /** @name methods override Feature */
  //@{
  /// recalculate the Feature
  App::DocumentObjectExecReturn *execute(void);
  short mustExecute() const;
  //@}
};

}

#endif // FEATURE_MESH_SOLID_H 
