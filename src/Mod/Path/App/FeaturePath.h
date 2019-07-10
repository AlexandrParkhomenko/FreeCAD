/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PATH_FeaturePath_H
#define PATH_FeaturePath_H

#include "stdexport.h"
#include "App/DocumentObject.h"
#include "App/GeoFeature.h"
#include "App/PropertyFile.h"
#include "App/PropertyGeo.h"
#include "App/FeaturePython.h"

#include "Path.h"
#include "PropertyPath.h"

namespace Path
{

class Standard_EXPORT Feature : public App::GeoFeature
{
    PROPERTY_HEADER(Path::Feature);

public:
    /// Constructor
    Feature(void);
    virtual ~Feature();

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "PathGui::ViewProviderPath";
    }
    virtual App::DocumentObjectExecReturn *execute(void) {
        return App::DocumentObject::StdReturn;
    }
    virtual short mustExecute(void) const;
    virtual PyObject *getPyObject(void);

    PropertyPath           Path;


protected:
    /// get called by the container when a property has changed
    virtual void onChanged (const App::Property* prop);

};

typedef App::FeaturePythonT<Feature> FeaturePython;

} //namespace Path


#endif // PATH_FeaturePath_H
