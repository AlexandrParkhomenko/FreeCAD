/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERPYTHON_H
#define PARTGUI_VIEWPROVIDERPYTHON_H

#include "stdexport.h"
#include "Gui/ViewProviderPythonFeature.h"
#include "Mod/Part/Gui/ViewProvider.h"

namespace PartGui {

class PartGuiExport ViewProviderCustom : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderCustom);

public:
    /// constructor
    ViewProviderCustom();
    /// destructor
    virtual ~ViewProviderCustom();
    virtual void updateData(const App::Property*);

protected:
    virtual void onChanged(const App::Property* prop);
    std::map<const App::Property*, Gui::ViewProvider*> propView;
};

typedef Gui::ViewProviderPythonFeatureT<ViewProviderPart> ViewProviderPython;
typedef Gui::ViewProviderPythonFeatureT<ViewProviderCustom> ViewProviderCustomPython;

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERPYTHON_H

