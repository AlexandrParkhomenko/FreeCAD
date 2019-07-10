/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2008                        *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_DOCUMENTOBJECTFILEINCLUDED_H
#define APP_DOCUMENTOBJECTFILEINCLUDED_H

#include "stdexport.h"
#include "DocumentObject.h"
#include "PropertyFile.h"



namespace App
{

class AppExport DocumentObjectFileIncluded : public DocumentObject
{
    PROPERTY_HEADER(App::DocumentObjectFileIncluded);

public:
    /// Constructor
    DocumentObjectFileIncluded(void);
    virtual ~DocumentObjectFileIncluded();

 
    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "Gui::ViewProviderDocumentObject";
    }
 
    /// Properties
    PropertyFileIncluded File;

};

} //namespace App


#endif // APP_DOCUMENTOBJECTFILEINCLUDED_H
