/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_DOCUMENTOBJECTGROUP_H
#define APP_DOCUMENTOBJECTGROUP_H

#include "stdexport.h"
#include "FeaturePython.h"
#include "DocumentObject.h"
#include "PropertyLinks.h"
#include "GroupExtension.h"
#include <vector>


namespace App
{
    
class AppExport DocumentObjectGroup : public DocumentObject, public GroupExtension {
    
    PROPERTY_HEADER_WITH_EXTENSIONS(App::DocumentObjectGroup);
    
public:
    /// Constructor
    DocumentObjectGroup(void);
    virtual ~DocumentObjectGroup();
    
    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "Gui::ViewProviderDocumentObjectGroup";
    }
    
    virtual PyObject *getPyObject(void);
};

typedef App::FeaturePythonT<DocumentObjectGroup> DocumentObjectGroupPython;


} //namespace App


#endif // APP_DOCUMENTOBJECTGROUP_H
