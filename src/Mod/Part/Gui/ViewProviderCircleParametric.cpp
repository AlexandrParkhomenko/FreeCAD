/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "ViewProviderCircleParametric.h"


using namespace PartGui;
using namespace std;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderCircleParametric, PartGui::ViewProviderPart)


ViewProviderCircleParametric::ViewProviderCircleParametric()
{
  sPixmap = "Part_Circle_Parametric.svg";
}

ViewProviderCircleParametric::~ViewProviderCircleParametric()
{

}



// **********************************************************************************

std::vector<std::string> ViewProviderCircleParametric::getDisplayModes(void) const
{
  // get the modes of the father
  std::vector<std::string> StrList;

  // add your own modes
  StrList.push_back("Wireframe");
  StrList.push_back("Points");

  return StrList;
}
