/***************************************************************************
 *   Copyright (c) 2013 Jürgen Riegel (FreeCAD@juergen-riegel.net)         *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_MaterialObject_H
#define APP_MaterialObject_H

#include "stdexport.h"
#include "DocumentObject.h"
#include "PropertyStandard.h"
#include "FeaturePython.h"


namespace App
{

class AppExport MaterialObject : public DocumentObject
{
    PROPERTY_HEADER(App::MaterialObject);

public:
    /// Constructor
    MaterialObject(void);
    virtual ~MaterialObject();

    App::PropertyMap Material;


    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "Gui::ViewProviderMaterialObject";
    }

};

typedef App::FeaturePythonT<MaterialObject> MaterialObjectPython;


} //namespace App


#endif // APP_MaterialObject_H
