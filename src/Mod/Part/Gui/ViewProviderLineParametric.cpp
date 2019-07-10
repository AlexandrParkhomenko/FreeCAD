/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "ViewProviderLineParametric.h"


using namespace PartGui;
using namespace std;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderLineParametric, PartGui::ViewProviderPart)


ViewProviderLineParametric::ViewProviderLineParametric()
{
  sPixmap = "Part_Line_Parametric.svg";
}

ViewProviderLineParametric::~ViewProviderLineParametric()
{

}



// **********************************************************************************

std::vector<std::string> ViewProviderLineParametric::getDisplayModes(void) const
{
  // get the modes of the father
  std::vector<std::string> StrList;

  // add your own modes
  StrList.push_back("Wireframe");
  StrList.push_back("Points");

  return StrList;
}
