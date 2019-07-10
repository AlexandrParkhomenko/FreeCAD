/***************************************************************************
 *   Copyright (c) Stefan Tröger          (stefantroeger@gmx.net) 2016     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef APP_DOCUMENTOBJECTEXTENSION_H
#define APP_DOCUMENTOBJECTEXTENSION_H

#include "stdexport.h"
#include "Extension.h"
#include "DocumentObject.h"

namespace App {
    
/**
 * @brief Extension with special document object calls
 * 
 */
class AppExport DocumentObjectExtension : public App::Extension
{

    //The cass does not have properties itself, but it is important to provide the property access
    //functions. see cpp file for details
    EXTENSION_PROPERTY_HEADER_WITH_OVERRIDE(App::DocumentObjectExtension );

public:

    DocumentObjectExtension ();
    virtual ~DocumentObjectExtension ();

    App::DocumentObject*       getExtendedObject();
    const App::DocumentObject* getExtendedObject() const;
  
    //override if execution is necessary
    virtual short extensionMustExecute(void);
    virtual App::DocumentObjectExecReturn *extensionExecute(void);
    
    
    /// get called after setting the document
    virtual void onExtendedSettingDocument();
    /// get called after a document has been fully restored
    virtual void onExtendedDocumentRestored();
    /// get called after a brand new object was created
    virtual void onExtendedSetupObject();
    /// get called when object is going to be removed from the document
    virtual void onExtendedUnsetupObject();
  
    virtual PyObject* getExtensionPyObject(void) override;
    
    /// returns the type name of the ViewProviderExtension which is automatically attached 
    /// to the viewprovider object when it is initiated
    virtual const char* getViewProviderExtensionName(void) const {return "";}
};

} //App

#endif // APP_DOCUMENTOBJECTEXTENSION_H
