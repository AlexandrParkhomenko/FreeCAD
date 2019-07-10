/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "Gui/BitmapFactory.h"
#include "Gui/Application.h"
#include "Mod/Part/App/PartFeature.h"
#include "Mod/Path/App/FeaturePathShape.h"
#include "ViewProviderPathShape.h"

using namespace Gui;
using namespace PathGui;

PROPERTY_SOURCE(PathGui::ViewProviderPathShape, PathGui::ViewProviderPath)

QIcon ViewProviderPathShape::getIcon() const
{
    return Gui::BitmapFactory().pixmap("Path-Shape");
}

std::vector<App::DocumentObject*> ViewProviderPathShape::claimChildren(void) const
{
    return std::vector<App::DocumentObject*>(
            static_cast<Path::FeatureShape*>(getObject())->Sources.getValues());
}

bool ViewProviderPathShape::canDragObjects() const
{
    return true;
}

bool ViewProviderPathShape::canDragObject(App::DocumentObject* obj) const
{
    return obj && obj->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId());
}

void ViewProviderPathShape::dragObject(App::DocumentObject* obj)
{
    Path::FeatureShape *feature = static_cast<Path::FeatureShape*>(getObject());
    std::vector<App::DocumentObject*> sources = feature->Sources.getValues();
    for (std::vector<App::DocumentObject*>::iterator it = sources.begin(); it != sources.end(); ++it) {
        if (*it == obj) {
            sources.erase(it);
            feature->Sources.setValues(sources);
            break;
        }
    }
}

bool ViewProviderPathShape::canDropObjects() const
{
    return true;
}

bool ViewProviderPathShape::canDropObject(App::DocumentObject* obj) const
{
    return canDragObject(obj);
}

void ViewProviderPathShape::dropObject(App::DocumentObject* obj)
{
    Path::FeatureShape *feature = static_cast<Path::FeatureShape*>(getObject());
    std::vector<App::DocumentObject*> sources = feature->Sources.getValues();
    sources.push_back(obj);
    feature->Sources.setValues(sources);
}

void ViewProviderPathShape::updateData(const App::Property* prop)
{
    PathGui::ViewProviderPath::updateData(prop);
    if (prop->getTypeId().isDerivedFrom(App::PropertyLinkList::getClassTypeId())) {
        std::vector<App::DocumentObject*> pShapes = static_cast<const App::PropertyLinkList*>(prop)->getValues();
        for (std::vector<App::DocumentObject*>::iterator it = pShapes.begin(); it != pShapes.end(); ++it) {
            if (*it)
                Gui::Application::Instance->hideViewProvider(*it);
        }
    }
}

bool ViewProviderPathShape::onDelete(const std::vector<std::string> &)
{
    // get the input shapes
    Path::FeatureShape *feature = static_cast<Path::FeatureShape*>(getObject());
    std::vector<App::DocumentObject*> pShapes =feature->Sources.getValues();
    for (std::vector<App::DocumentObject*>::iterator it = pShapes.begin(); it != pShapes.end(); ++it) {
        if (*it)
            Gui::Application::Instance->showViewProvider(*it);
    }
    return true;
}
