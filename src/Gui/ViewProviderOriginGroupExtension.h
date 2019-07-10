/***************************************************************************
 *   Copyright (c) 2015 Alexander Golubev (Fat-Zer) <fatzer2@gmail.com>    *
 *   Copyright (c) 2016 Stefan Tröger <stefantroeger@gmx.net>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDERORIGINGROUPEXTENSION_H
#define GUI_VIEWPROVIDERORIGINGROUPEXTENSION_H

#include "stdexport.h"
#include "App/Extension.h"
#include "ViewProviderGeoFeatureGroup.h"

namespace Gui
{

class GuiExport ViewProviderOriginGroupExtension : public ViewProviderGeoFeatureGroupExtension
{
    EXTENSION_PROPERTY_HEADER_WITH_OVERRIDE(Gui::ViewProviderOriginGroupExtension);

public:
    /// Constructor
    ViewProviderOriginGroupExtension(void);
    virtual ~ViewProviderOriginGroupExtension();

    virtual std::vector<App::DocumentObject*> extensionClaimChildren(void)const override;
    virtual std::vector<App::DocumentObject*> extensionClaimChildren3D(void)const override;

    virtual void extensionAttach(App::DocumentObject *pcObject) override;
    virtual void extensionUpdateData(const App::Property* prop) override;
    
    void updateOriginSize();

protected:
    void slotChangedObjectApp ( const App::DocumentObject& obj );
    void slotChangedObjectGui ( const Gui::ViewProviderDocumentObject& obj );

private:
    std::vector<App::DocumentObject*> constructChildren (
            const std::vector<App::DocumentObject*> &children ) const;

    boost::signals2::connection connectChangedObjectApp;
    boost::signals2::connection connectChangedObjectGui;
};

typedef ViewProviderExtensionPythonT<Gui::ViewProviderOriginGroupExtension> ViewProviderOriginGroupExtensionPython;

} //namespace Gui

#endif // GUI_VIEWPROVIDERORIGINGROUPEXTENSION_H
