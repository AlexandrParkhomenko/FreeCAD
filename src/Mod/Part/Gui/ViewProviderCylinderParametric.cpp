/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "ViewProviderCylinderParametric.h"


using namespace PartGui;
using namespace std;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderCylinderParametric, PartGui::ViewProviderPart)


ViewProviderCylinderParametric::ViewProviderCylinderParametric()
{
  sPixmap = "Tree_Part_Cylinder_Parametric.svg";
}

ViewProviderCylinderParametric::~ViewProviderCylinderParametric()
{

}



// **********************************************************************************

std::vector<std::string> ViewProviderCylinderParametric::getDisplayModes(void) const
{
  // get the modes of the father
  std::vector<std::string> StrList;

  // add your own modes
  StrList.push_back("Flat Lines");
  StrList.push_back("Shaded");
  StrList.push_back("Wireframe");
  StrList.push_back("Points");

  return StrList;
}
