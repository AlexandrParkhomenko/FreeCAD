/***************************************************************************
 *   Copyright (c) Stefan Tröger          (stefantroeger@gmx.net) 2016     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDEREXTENSION_H
#define GUI_VIEWPROVIDEREXTENSION_H

#include "stdexport.h"
#include "App/Extension.h"
#include "ViewProvider.h"
#include "ViewProviderDocumentObject.h"

namespace Gui {
    
/**
 * @brief Extension with special viewprovider calls
 * 
 */
class GuiExport ViewProviderExtension : public App::Extension
{

    //The cass does not have properties itself, but it is important to provide the property access
    //functions.
    EXTENSION_PROPERTY_HEADER(Gui::ViewProviderExtension);

public:

    ViewProviderExtension ();
    virtual ~ViewProviderExtension ();

    Gui::ViewProviderDocumentObject*       getExtendedViewProvider();
    const Gui::ViewProviderDocumentObject* getExtendedViewProvider() const;
   
    virtual std::vector<App::DocumentObject*> extensionClaimChildren3D(void) const { 
        return std::vector<App::DocumentObject*>(); }
        
    virtual bool extensionOnDelete(const std::vector<std::string> &){ return true;}
 
    virtual std::vector<App::DocumentObject*> extensionClaimChildren(void) const { 
        return std::vector<App::DocumentObject*>(); }

    virtual bool extensionCanDragObjects() const { return false; }
    virtual bool extensionCanDragObject(App::DocumentObject*) const { return true; }
    virtual void extensionDragObject(App::DocumentObject*) { }
    virtual bool extensionCanDropObjects() const { return false; }
    virtual bool extensionCanDropObject(App::DocumentObject*) const { return true; }
    virtual void extensionDropObject(App::DocumentObject*) { }
    virtual void extensionReplaceObject(App::DocumentObject* /*oldValue*/, App::DocumentObject* /*newValue*/) { }

    /// Hides the view provider
    virtual void extensionHide(void) { }
    /// Shows the view provider
    virtual void extensionShow(void) { }
    
    virtual SoSeparator* extensionGetFrontRoot(void) const {return nullptr;}
    virtual SoGroup*     extensionGetChildRoot(void) const {return nullptr;}
    virtual SoSeparator* extensionGetBackRoot(void) const {return nullptr;}
    virtual void extensionAttach(App::DocumentObject* ) { }
    virtual void extensionSetDisplayMode(const char* ) { }
    virtual std::vector<std::string> extensionGetDisplayModes(void) const {return std::vector<std::string>();}

    //update data of extended opject
    virtual void extensionUpdateData(const App::Property*);
    
private:
  //Gui::ViewProviderDocumentObject* m_viewBase = nullptr;
};

/**
 * Generic Python extension class which allows to behave every extension
 * derived class as Python extension -- simply by subclassing.
 */
template <class ExtensionT>
class ViewProviderExtensionPythonT : public ExtensionT
{
    EXTENSION_PROPERTY_HEADER(Gui::ViewProviderExtensionPythonT<ExtensionT>);

public:
    typedef ExtensionT Inherited;
    
    ViewProviderExtensionPythonT() {
        ExtensionT::m_isPythonExtension = true;
        ExtensionT::initExtensionType(ViewProviderExtensionPythonT::getExtensionClassTypeId());
        
        EXTENSION_ADD_PROPERTY(ExtensionProxy,(Py::Object()));
    }
    virtual ~ViewProviderExtensionPythonT() {
    }

    App::PropertyPythonObject ExtensionProxy;
};

typedef ViewProviderExtensionPythonT<Gui::ViewProviderExtension> ViewProviderExtensionPython;

} //Gui

#endif // GUI_VIEWPROVIDEREXTENSION_H
