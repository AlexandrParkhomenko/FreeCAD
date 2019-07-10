/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef SketcherGui_VIEWPROVIDERPYTHON_H
#define SketcherGui_VIEWPROVIDERPYTHON_H

#include "stdexport.h"
#include "Gui/ViewProviderPythonFeature.h"
#include "Mod/Sketcher/Gui/ViewProviderSketch.h"

namespace SketcherGui {

class SketcherGuiExport ViewProviderCustom : public ViewProviderSketch
{
    PROPERTY_HEADER(SketcherGui::ViewProviderCustom);

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

typedef Gui::ViewProviderPythonFeatureT<ViewProviderSketch> ViewProviderPython;
typedef Gui::ViewProviderPythonFeatureT<ViewProviderCustom> ViewProviderCustomPython;

} // namespace SketcherGui


#endif // SketcherGui_VIEWPROVIDERPYTHON_H

