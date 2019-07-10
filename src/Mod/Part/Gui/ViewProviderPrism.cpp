/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "ViewProviderPrism.h"

using namespace PartGui;
using namespace std;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderPrism, PartGui::ViewProviderPart)


ViewProviderPrism::ViewProviderPrism()
{
    sPixmap = "Tree_Part_Prism.svg";
}

ViewProviderPrism::~ViewProviderPrism()
{

}

// **********************************************************************************

std::vector<std::string> ViewProviderPrism::getDisplayModes(void) const
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

//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderWedge, PartGui::ViewProviderPart)


ViewProviderWedge::ViewProviderWedge()
{
    sPixmap = "Tree_Part_Wedge.svg";
}

ViewProviderWedge::~ViewProviderWedge()
{

}

// **********************************************************************************

std::vector<std::string> ViewProviderWedge::getDisplayModes(void) const
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
