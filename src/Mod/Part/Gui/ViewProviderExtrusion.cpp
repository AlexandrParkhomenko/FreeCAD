/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "ViewProviderExtrusion.h"
#include "Mod/Part/App/FeatureExtrusion.h"


using namespace PartGui;

PROPERTY_SOURCE(PartGui::ViewProviderExtrusion,PartGui::ViewProviderPart)

ViewProviderExtrusion::ViewProviderExtrusion()
{
    sPixmap = "Part_Extrude.svg";
}

ViewProviderExtrusion::~ViewProviderExtrusion()
{
}

std::vector<App::DocumentObject*> ViewProviderExtrusion::claimChildren(void)const
{
    std::vector<App::DocumentObject*> temp;
    temp.push_back(static_cast<Part::Extrusion*>(getObject())->Base.getValue());

    return temp;
}
