/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "ViewProviderEllipseParametric.h"


using namespace PartGui;
using namespace std;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderEllipseParametric, PartGui::ViewProviderPart)


ViewProviderEllipseParametric::ViewProviderEllipseParametric()
{
  sPixmap = "Part_Ellipse_Parametric.svg";
}

ViewProviderEllipseParametric::~ViewProviderEllipseParametric()
{

}



// **********************************************************************************

std::vector<std::string> ViewProviderEllipseParametric::getDisplayModes(void) const
{
  // get the modes of the father
  std::vector<std::string> StrList;

  // add your own modes
  StrList.push_back("Wireframe");
  StrList.push_back("Points");

  return StrList;
}
