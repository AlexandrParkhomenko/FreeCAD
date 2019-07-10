/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <Inventor/nodes/SoMaterial.h>

#include "ViewProviderBuilder.h"
#include "SoFCSelection.h"
#include "Window.h"
#include "App/PropertyStandard.h"

using namespace Gui;

std::map<Base::Type, Base::Type> ViewProviderBuilder::_prop_to_view;

ViewProviderBuilder::ViewProviderBuilder() 
{
}

ViewProviderBuilder::~ViewProviderBuilder()
{
}

void ViewProviderBuilder::add(const Base::Type& prop, const Base::Type& view)
{
    _prop_to_view[prop] = view;
}

ViewProvider* ViewProviderBuilder::create(const Base::Type& type)
{
    std::map<Base::Type, Base::Type>::iterator it = _prop_to_view.find(type);
    if (it != _prop_to_view.end())
        return reinterpret_cast<ViewProvider*>(it->second.createInstance());
    return 0;
}

Gui::SoFCSelection* ViewProviderBuilder::createSelection()
{
    Gui::SoFCSelection* sel = new Gui::SoFCSelection();

    float transparency;
    ParameterGrp::handle hGrp = Gui::WindowParameter::getDefaultParameter()->GetGroup("View");
    bool enablePre = hGrp->GetBool("EnablePreselection", true);
    bool enableSel = hGrp->GetBool("EnableSelection", true);
    if (!enablePre) {
        sel->highlightMode = Gui::SoFCSelection::OFF;
    }
    else {
        // Search for a user defined value with the current color as default
        SbColor highlightColor = sel->colorHighlight.getValue();
        unsigned long highlight = (unsigned long)(highlightColor.getPackedValue());
        highlight = hGrp->GetUnsigned("HighlightColor", highlight);
        highlightColor.setPackedValue((uint32_t)highlight, transparency);
        sel->colorHighlight.setValue(highlightColor);
    }
    if (!enableSel) {
        sel->selectionMode = Gui::SoFCSelection::SEL_OFF;
    }
    else {
        // Do the same with the selection color
        SbColor selectionColor = sel->colorSelection.getValue();
        unsigned long selection = (unsigned long)(selectionColor.getPackedValue());
        selection = hGrp->GetUnsigned("SelectionColor", selection);
        selectionColor.setPackedValue((uint32_t)selection, transparency);
        sel->colorSelection.setValue(selectionColor);
    }

    return sel;
}

// --------------------------------------

ViewProviderColorBuilder::ViewProviderColorBuilder() 
{
}

ViewProviderColorBuilder::~ViewProviderColorBuilder()
{
}

void ViewProviderColorBuilder::buildNodes(const App::Property* prop, std::vector<SoNode*>& node) const
{
    const App::PropertyColorList* color = static_cast<const App::PropertyColorList*>(prop);
    const std::vector<App::Color>& val = color->getValues();
    unsigned long i=0;

    SoMaterial* material = new SoMaterial();
    material->diffuseColor.setNum(val.size());

    SbColor* colors = material->diffuseColor.startEditing();
    for (std::vector<App::Color>::const_iterator it = val.begin(); it != val.end(); ++it) {
        colors[i].setValue(it->r, it->g, it->b);
        i++;
    }
    material->diffuseColor.finishEditing();
    node.push_back(material);
}
