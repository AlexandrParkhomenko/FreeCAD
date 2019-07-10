/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "ViewProviderRegularPolygon.h"

using namespace PartGui;
using namespace std;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderRegularPolygon, PartGui::ViewProviderPart)

       
ViewProviderRegularPolygon::ViewProviderRegularPolygon()
{
  sPixmap = "Part_Polygon_Parametric.svg";
}

ViewProviderRegularPolygon::~ViewProviderRegularPolygon()
{

}



// **********************************************************************************

std::vector<std::string> ViewProviderRegularPolygon::getDisplayModes(void) const
{
    // get the modes of the father
    std::vector<std::string> StrList;

    // add your own modes
    StrList.push_back("Wireframe");
    StrList.push_back("Points");

    return StrList;
}
