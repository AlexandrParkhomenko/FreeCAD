/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDERGROUPEXTENSION_H
#define GUI_VIEWPROVIDERGROUPEXTENSION_H

#include "stdexport.h"
#include "App/Extension.h"
#include "ViewProviderExtension.h"

namespace Gui
{

class GuiExport ViewProviderGroupExtension : public ViewProviderExtension
{
    EXTENSION_PROPERTY_HEADER_WITH_OVERRIDE(Gui::ViewProviderGroupExtension);

public:
    /// Constructor
    ViewProviderGroupExtension(void);
    virtual ~ViewProviderGroupExtension();

    virtual std::vector<App::DocumentObject*> extensionClaimChildren(void)const override;
    virtual bool extensionCanDragObjects() const override; 
    virtual bool extensionCanDragObject(App::DocumentObject*) const override;
    virtual void extensionDragObject(App::DocumentObject*) override;
    virtual bool extensionCanDropObjects() const override;
    virtual bool extensionCanDropObject(App::DocumentObject*) const override;
    virtual void extensionDropObject(App::DocumentObject*) override;   
    virtual void extensionReplaceObject(App::DocumentObject* oldValue, App::DocumentObject* newValue) override;
 
    virtual void extensionHide(void) override;
    virtual void extensionShow(void) override;

    virtual bool extensionOnDelete(const std::vector<std::string> &) override;

private:
    bool visible; // helper variable
    bool guard;
    std::vector<ViewProvider*> nodes;
};

typedef ViewProviderExtensionPythonT<Gui::ViewProviderGroupExtension> ViewProviderGroupExtensionPython;

} //namespace Gui

#endif // GUI_VIEWPROVIDERGROUPEXTENSION_H
