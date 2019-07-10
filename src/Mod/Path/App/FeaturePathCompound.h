/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PATH_FeatureCompound_H
#define PATH_FeatureCompound_H

#include "stdexport.h"
#include "App/GeoFeature.h"
#include "App/PropertyFile.h"
#include "App/PropertyGeo.h"
#include "App/PropertyUnits.h"

#include "Path.h"
#include "FeaturePath.h"
#include "PropertyPath.h"

namespace Path
{

class Standard_EXPORT FeatureCompound : public Path::Feature
{
    PROPERTY_HEADER(Path::Feature);

public:
    /// Constructor
    FeatureCompound(void);
    virtual ~FeatureCompound();

    App::PropertyLinkList     Group;
    App::PropertyBool         UsePlacements;

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "PathGui::ViewProviderPathCompound";
    }
    virtual App::DocumentObjectExecReturn *execute(void);
    
    /// Checks whether the object \a obj is part of this group.
    bool hasObject(const DocumentObject* obj) const;
    /// Adds an object to this group.
    void addObject(DocumentObject* obj);
    /// Removes an object from this group.
    void removeObject(DocumentObject* obj);
    virtual PyObject *getPyObject(void);

};

typedef App::FeaturePythonT<FeatureCompound> FeatureCompoundPython;

} //namespace Path


#endif // PATH_FeatureCompound_H
