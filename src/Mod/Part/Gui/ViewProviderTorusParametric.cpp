/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "ViewProviderTorusParametric.h"


using namespace PartGui;
using namespace std;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderTorusParametric, PartGui::ViewProviderPart)


ViewProviderTorusParametric::ViewProviderTorusParametric()
{
  sPixmap = "Tree_Part_Torus_Parametric.svg";
}

ViewProviderTorusParametric::~ViewProviderTorusParametric()
{

}



// **********************************************************************************

std::vector<std::string> ViewProviderTorusParametric::getDisplayModes(void) const
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
