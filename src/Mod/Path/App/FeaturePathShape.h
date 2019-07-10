/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/
/* 
 *  Copyright (c) 2017 Zheng, Lei <realthunder.dev@gmail.com> 
 */


#ifndef PATH_FeaturePathShape_H
#define PATH_FeaturePathShape_H

#include "stdexport.h"
#include "App/DocumentObject.h"
#include "App/GeoFeature.h"
#include "App/PropertyGeo.h"
#include "App/FeaturePython.h"
#include "Mod/Part/App/PropertyTopoShape.h"

#include "PropertyPath.h"
#include "FeaturePath.h"
#include "FeatureArea.h"
#include "Area.h"

namespace Path
{

class Standard_EXPORT FeatureShape : public Path::Feature
{
    PROPERTY_HEADER(Path::FeatureShape);

public:
    /// Constructor
    FeatureShape(void);
    virtual ~FeatureShape();
    
    // Part::PropertyPartShape Shape;
    App::PropertyLinkList Sources;
    App::PropertyVector StartPoint;
    App::PropertyBool UseStartPoint;
    PARAM_PROP_DECLARE(AREA_PARAMS_PATH)

    //@{
    /// recalculate the feature
    virtual App::DocumentObjectExecReturn *execute(void);
    //@}

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "PathGui::ViewProviderPathShape";
    }
    
protected:
    /// get called by the container when a property has changed
    //virtual void onChanged (const App::Property* prop);

};

typedef App::FeaturePythonT<FeatureShape> FeatureShapePython;

} //namespace Path


#endif // PATH_FeaturePathShape_H
