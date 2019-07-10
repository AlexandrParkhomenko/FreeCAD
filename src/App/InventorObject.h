/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_INVENTOROBJECT_H
#define APP_INVENTOROBJECT_H

#include "stdexport.h"
#include "GeoFeature.h"
#include "PropertyStandard.h"


namespace App
{

class AppExport InventorObject : public GeoFeature
{
    PROPERTY_HEADER(App::InventorObject);

public:
    /// Constructor
    InventorObject(void);
    virtual ~InventorObject();

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "Gui::ViewProviderInventorObject";
    }
    virtual DocumentObjectExecReturn *execute(void) {
        return DocumentObject::StdReturn;
    }
    virtual short mustExecute(void) const;
    virtual PyObject *getPyObject(void);

    PropertyString Buffer;
    PropertyString FileName;
};

} //namespace App


#endif // APP_INVENTOROBJECT_H
