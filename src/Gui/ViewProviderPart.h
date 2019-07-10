/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_ViewProviderPart_H
#define GUI_VIEWPROVIDER_ViewProviderPart_H


#include "stdexport.h"
#include "ViewProviderOriginGroup.h"
#include "ViewProviderDragger.h"
#include "ViewProviderPythonFeature.h"


namespace Gui {

class GuiExport ViewProviderPart : public ViewProviderDragger,
                                   public ViewProviderOriginGroupExtension
{
    PROPERTY_HEADER_WITH_EXTENSIONS(Gui::ViewProviderPart);

public:
    /// constructor.
    ViewProviderPart();
    /// destructor.
    virtual ~ViewProviderPart();

    virtual bool doubleClicked(void);
    virtual void setupContextMenu(QMenu* menu, QObject* receiver, const char* member);

protected:
    /// get called by the container whenever a property has been changed
    virtual void onChanged(const App::Property* prop);
};

typedef ViewProviderPythonFeatureT<ViewProviderPart> ViewProviderPartPython;

} // namespace Gui

#endif // GUI_VIEWPROVIDER_ViewProviderPart_H

