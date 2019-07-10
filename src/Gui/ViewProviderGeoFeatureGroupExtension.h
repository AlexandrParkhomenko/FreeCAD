/***************************************************************************
 *   Copyright (c) 2011 Juergen Riegel <FreeCAD@juergen-riegel.net>        *
 *   Copyright (c) 2015 Alexander Golubev (Fat-Zer) <fatzer2@gmail.com>    *
 *   Copyright (c) 2016 Stefan Tröger <stefantroeger@gmx.net>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDERGEOFEATUREGROUPEXTENSION_H
#define GUI_VIEWPROVIDERGEOFEATUREGROUPEXTENSION_H

#include "stdexport.h"
#include "App/Extension.h"
#include "ViewProviderGroupExtension.h"

namespace Gui
{

class GuiExport ViewProviderGeoFeatureGroupExtension : public ViewProviderGroupExtension
{
    EXTENSION_PROPERTY_HEADER_WITH_OVERRIDE(Gui::ViewProviderGeoFeatureGroupExtension);

public:
    /// Constructor
    ViewProviderGeoFeatureGroupExtension(void);
    virtual ~ViewProviderGeoFeatureGroupExtension();

    virtual std::vector<App::DocumentObject*> extensionClaimChildren3D(void)const override;
    virtual std::vector< App::DocumentObject* > extensionClaimChildren(void) const override;
    virtual SoGroup* extensionGetChildRoot(void) const override {return pcGroupChildren;};
    virtual void extensionAttach(App::DocumentObject* pcObject) override;
    virtual void extensionSetDisplayMode(const char* ModeName) override;
    virtual std::vector<std::string> extensionGetDisplayModes(void) const override;

    /// Show the object in the view: suppresses behavior of DocumentObjectGroup
    virtual void extensionShow(void) override {
        ViewProviderExtension::extensionShow();
    }
    /// Hide the object in the view: suppresses behavior of DocumentObjectGroup
    virtual void extensionHide(void) override {
        ViewProviderExtension::extensionHide();
    }

    virtual void extensionUpdateData(const App::Property*) override;

protected:
    SoGroup *pcGroupChildren;
};

typedef ViewProviderExtensionPythonT<Gui::ViewProviderGeoFeatureGroupExtension> ViewProviderGeoFeatureGroupExtensionPython;

} //namespace Gui

#endif // GUI_VIEWPROVIDERGEOFEATUREGROUPEXTENSION_H
