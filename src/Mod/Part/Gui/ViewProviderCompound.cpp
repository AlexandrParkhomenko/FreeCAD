/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <TopExp.hxx>
# include <TopTools_IndexedMapOfShape.hxx>

#include "Gui/Application.h"
#include "Mod/Part/App/FeatureCompound.h"
#include "ViewProviderCompound.h"


using namespace PartGui;

PROPERTY_SOURCE(PartGui::ViewProviderCompound,PartGui::ViewProviderPart)

ViewProviderCompound::ViewProviderCompound()
{
    sPixmap = "Part_Compound.svg";
}

ViewProviderCompound::~ViewProviderCompound()
{
}

std::vector<App::DocumentObject*> ViewProviderCompound::claimChildren(void) const
{
    return static_cast<Part::Compound*>(getObject())->Links.getValues();
}

bool ViewProviderCompound::onDelete(const std::vector<std::string> &)
{
    // get the input shapes
    Part::Compound* pComp = static_cast<Part::Compound*>(getObject());
    std::vector<App::DocumentObject*> pLinks = pComp->Links.getValues();
    for (std::vector<App::DocumentObject*>::iterator it = pLinks.begin(); it != pLinks.end(); ++it) {
        if (*it)
            Gui::Application::Instance->showViewProvider(*it);
    }

    return true;
}

void ViewProviderCompound::updateData(const App::Property* prop)
{
    PartGui::ViewProviderPart::updateData(prop);
    if (prop->getTypeId() == Part::PropertyShapeHistory::getClassTypeId()) {
        const std::vector<Part::ShapeHistory>& hist = static_cast<const Part::PropertyShapeHistory*>
            (prop)->getValues();
        Part::Compound* objComp = static_cast<Part::Compound*>(getObject());
        std::vector<App::DocumentObject*> sources = objComp->Links.getValues();
        if (hist.size() != sources.size())
            return;

        const TopoDS_Shape& compShape = objComp->Shape.getValue();
        TopTools_IndexedMapOfShape compMap;
        TopExp::MapShapes(compShape, TopAbs_FACE, compMap);

        std::vector<App::Color> compCol;
        compCol.resize(compMap.Extent(), this->ShapeColor.getValue());

        int index=0;
        for (std::vector<App::DocumentObject*>::iterator it = sources.begin(); it != sources.end(); ++it, ++index) {
            Part::Feature* objBase = dynamic_cast<Part::Feature*>(*it);
            if (!objBase)
                continue;

            const TopoDS_Shape& baseShape = objBase->Shape.getValue();

            TopTools_IndexedMapOfShape baseMap;
            TopExp::MapShapes(baseShape, TopAbs_FACE, baseMap);

            Gui::ViewProvider* vpBase = Gui::Application::Instance->getViewProvider(objBase);
            std::vector<App::Color> baseCol = static_cast<PartGui::ViewProviderPart*>(vpBase)->DiffuseColor.getValues();
            applyTransparency(static_cast<PartGui::ViewProviderPart*>(vpBase)->Transparency.getValue(),baseCol);
            if (static_cast<int>(baseCol.size()) == baseMap.Extent()) {
                applyColor(hist[index], baseCol, compCol);
            }
            else if (!baseCol.empty() && baseCol[0] != this->ShapeColor.getValue()) {
                baseCol.resize(baseMap.Extent(), baseCol[0]);
                applyColor(hist[index], baseCol, compCol);
            }
        }

        this->DiffuseColor.setValues(compCol);
    }
    else if (prop->getTypeId().isDerivedFrom(App::PropertyLinkList::getClassTypeId())) {
        const std::vector<App::DocumentObject *>& pBases = static_cast<const App::PropertyLinkList*>(prop)->getValues();
        for (std::vector<App::DocumentObject *>::const_iterator it = pBases.begin(); it != pBases.end(); ++it) {
            if (*it) Gui::Application::Instance->hideViewProvider(*it);
        }
    }
}

bool ViewProviderCompound::canDragObjects() const
{
    return true;
}

bool ViewProviderCompound::canDragObject(App::DocumentObject* obj) const
{
    return obj->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId());
}

void ViewProviderCompound::dragObject(App::DocumentObject* obj)
{
    Part::Compound* pComp = static_cast<Part::Compound*>(getObject());
    std::vector<App::DocumentObject*> pShapes = pComp->Links.getValues();
    for (std::vector<App::DocumentObject*>::iterator it = pShapes.begin(); it != pShapes.end(); ++it) {
        if (*it == obj) {
            pShapes.erase(it);
            pComp->Links.setValues(pShapes);
            break;
        }
    }
}

bool ViewProviderCompound::canDropObjects() const
{
    return true;
}

bool ViewProviderCompound::canDropObject(App::DocumentObject* obj) const
{
    return obj->getTypeId().isDerivedFrom(Part::Feature::getClassTypeId());
}

void ViewProviderCompound::dropObject(App::DocumentObject* obj)
{
    Part::Compound* pComp = static_cast<Part::Compound*>(getObject());
    std::vector<App::DocumentObject*> pShapes = pComp->Links.getValues();
    pShapes.push_back(obj);
    pComp->Links.setValues(pShapes);
}

void ViewProviderCompound::replaceObject(App::DocumentObject* oldValue, App::DocumentObject* newValue)
{
    Part::Compound* pBool = static_cast<Part::Compound*>(getObject());
    std::vector<App::DocumentObject*> pShapes = pBool->Links.getValues();
    std::replace(pShapes.begin(), pShapes.end(), oldValue, newValue);
    pBool->Links.setValues(pShapes);
}
