/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "ViewProviderPointParametric.h"


using namespace PartGui;
using namespace std;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderPointParametric, PartGui::ViewProviderPart)


ViewProviderPointParametric::ViewProviderPointParametric()
{
  sPixmap = "Part_Point_Parametric.svg";
}

ViewProviderPointParametric::~ViewProviderPointParametric()
{

}



// **********************************************************************************

std::vector<std::string> ViewProviderPointParametric::getDisplayModes(void) const
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
