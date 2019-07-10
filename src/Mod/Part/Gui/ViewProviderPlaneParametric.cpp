/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "ViewProviderPlaneParametric.h"
#include "Mod/Part/App/FeatureFace.h"
#include "Mod/Part/App/Part2DObject.h"

using namespace PartGui;


//**************************************************************************
// Construction/Destruction

PROPERTY_SOURCE(PartGui::ViewProviderPlaneParametric, PartGui::ViewProviderPart)


ViewProviderPlaneParametric::ViewProviderPlaneParametric()
{
    sPixmap = "Tree_Part_Plane_Parametric.svg";
}

ViewProviderPlaneParametric::~ViewProviderPlaneParametric()
{

}

std::vector<std::string> ViewProviderPlaneParametric::getDisplayModes(void) const
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

// ----------------------------------------------------------------------------

PROPERTY_SOURCE(PartGui::ViewProviderFace, PartGui::ViewProviderPlaneParametric)


ViewProviderFace::ViewProviderFace()
{
}

ViewProviderFace::~ViewProviderFace()
{
}

std::vector<App::DocumentObject*> ViewProviderFace::claimChildren(void) const
{
    return std::vector<App::DocumentObject*>(static_cast<Part::Face*>(getObject())->Sources.getValues());
}

bool ViewProviderFace::canDragObjects() const
{
    return true;
}

bool ViewProviderFace::canDragObject(App::DocumentObject* obj) const
{
    if (!obj)
        return false;
    if (obj->getTypeId().isDerivedFrom(Part::Part2DObject::getClassTypeId()))
        return true;
    else
        return false;
}

void ViewProviderFace::dragObject(App::DocumentObject* obj)
{
    Part::Face* face = static_cast<Part::Face*>(getObject());
    std::vector<App::DocumentObject*> sources = face->Sources.getValues();
    for (std::vector<App::DocumentObject*>::iterator it = sources.begin(); it != sources.end(); ++it) {
        if (*it == obj) {
            sources.erase(it);
            face->Sources.setValues(sources);
            break;
        }
    }
}

bool ViewProviderFace::canDropObjects() const
{
    return true;
}

bool ViewProviderFace::canDropObject(App::DocumentObject* obj) const
{
    return canDragObject(obj);
}

void ViewProviderFace::dropObject(App::DocumentObject* obj)
{
    Part::Face* face = static_cast<Part::Face*>(getObject());
    std::vector<App::DocumentObject*> sources = face->Sources.getValues();
    sources.push_back(obj);
    face->Sources.setValues(sources);
}
