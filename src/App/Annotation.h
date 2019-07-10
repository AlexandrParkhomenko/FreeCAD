/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef APP_ANNOTATION_H
#define APP_ANNOTATION_H

#include "stdexport.h"
#include "DocumentObject.h"
#include "PropertyGeo.h"
#include "PropertyStandard.h"


namespace App
{

class AppExport Annotation : public DocumentObject
{
    PROPERTY_HEADER(App::Annotation);

public:
    /// Constructor
    Annotation(void);
    virtual ~Annotation();

    App::PropertyStringList LabelText;
    App::PropertyVector Position;

    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "Gui::ViewProviderAnnotation";
    }
};

class AppExport AnnotationLabel : public DocumentObject
{
    PROPERTY_HEADER(App::AnnotationLabel);

public:
    /// Constructor
    AnnotationLabel(void);
    virtual ~AnnotationLabel();

    App::PropertyStringList LabelText;
    App::PropertyVector BasePosition;
    App::PropertyVector TextPosition;

    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "Gui::ViewProviderAnnotationLabel";
    }
};

} //namespace App


#endif // APP_ANNOTATION_H
