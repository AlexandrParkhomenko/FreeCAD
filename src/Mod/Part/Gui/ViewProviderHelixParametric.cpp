/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include "FCConfig.h"

#include "ViewProviderHelixParametric.h"

using namespace PartGui;


PROPERTY_SOURCE(PartGui::ViewProviderHelixParametric, PartGui::ViewProviderSpline)


ViewProviderHelixParametric::ViewProviderHelixParametric()
{
    sPixmap = "Part_Helix_Parametric.svg";
}

ViewProviderHelixParametric::~ViewProviderHelixParametric()
{

}

std::vector<std::string> ViewProviderHelixParametric::getDisplayModes(void) const
{
    // add your own modes
    std::vector<std::string> StrList;
    StrList.push_back("Wireframe");
    StrList.push_back("Points");

    return StrList;
}

// ------------------------------------------------------------------

PROPERTY_SOURCE(PartGui::ViewProviderSpiralParametric, PartGui::ViewProviderSpline)


ViewProviderSpiralParametric::ViewProviderSpiralParametric()
{
    sPixmap = "Part_Spiral_Parametric.svg";
}

ViewProviderSpiralParametric::~ViewProviderSpiralParametric()
{

}

std::vector<std::string> ViewProviderSpiralParametric::getDisplayModes(void) const
{
    // add your own modes
    std::vector<std::string> StrList;
    StrList.push_back("Wireframe");
    StrList.push_back("Points");

    return StrList;
}
