/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "ViewProviderSphereParametric.h"

using namespace PartGui;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderSphereParametric, PartGui::ViewProviderPart)

ViewProviderSphereParametric::ViewProviderSphereParametric()
{
  sPixmap = "Tree_Part_Sphere_Parametric.svg";
}

ViewProviderSphereParametric::~ViewProviderSphereParametric()
{

}

std::vector<std::string> ViewProviderSphereParametric::getDisplayModes(void) const
{
  std::vector<std::string> StrList;

  // add your own modes
  StrList.push_back("Flat Lines");
  StrList.push_back("Shaded");
  StrList.push_back("Wireframe");
  StrList.push_back("Points");

  return StrList;
}

// ----------------------------------------------------------------------------

PROPERTY_SOURCE(PartGui::ViewProviderEllipsoid, PartGui::ViewProviderPart)

ViewProviderEllipsoid::ViewProviderEllipsoid()
{
    sPixmap = "Tree_Part_Ellipsoid_Parametric.svg";
}

ViewProviderEllipsoid::~ViewProviderEllipsoid()
{
}

std::vector<std::string> ViewProviderEllipsoid::getDisplayModes(void) const
{
  std::vector<std::string> StrList;

  // add your own modes
  StrList.push_back("Flat Lines");
  StrList.push_back("Shaded");
  StrList.push_back("Wireframe");
  StrList.push_back("Points");

  return StrList;
}
