/****************************************************************************
 *   Copyright (c) 2017 Zheng, Lei (realthunder) <realthunder.dev@gmail.com>*
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ****************************************************************************/

#ifndef PATH_FeatureArea_H
#define PATH_FeatureArea_H

#include "stdexport.h"
#include "App/DocumentObject.h"
#include "App/GeoFeature.h"
#include "App/PropertyUnits.h"
#include "App/FeaturePython.h"
#include "Mod/Part/App/PartFeature.h"

#include "Area.h"

namespace Path
{

class Standard_EXPORT FeatureArea : public Part::Feature
{
    PROPERTY_HEADER(Path::FeatureArea);

public:
    /// Constructor
    FeatureArea(void);
    virtual ~FeatureArea();

    Area &getArea();
    const std::vector<TopoDS_Shape> &getShapes();

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "PathGui::ViewProviderArea";
    }
    virtual App::DocumentObjectExecReturn *execute(void);
    virtual short mustExecute(void) const;
    virtual PyObject *getPyObject(void);

    App::PropertyLinkList   Sources;
    Part::PropertyPartShape WorkPlane;

    PARAM_PROP_DECLARE(AREA_PARAMS_ALL)

    void setWorkPlane(const TopoDS_Shape &shape) {
        WorkPlane.setValue(shape);
        myArea.setPlane(shape);
    }

private:
    Area myArea;
    std::vector<TopoDS_Shape> myShapes;
    bool myInited;
};

typedef App::FeaturePythonT<FeatureArea> FeatureAreaPython;

class Standard_EXPORT FeatureAreaView : public Part::Feature
{
    PROPERTY_HEADER(Path::FeatureAreaView);

public:
    /// Constructor
    FeatureAreaView(void);

    std::list<TopoDS_Shape> getShapes();

    virtual const char* getViewProviderName(void) const {
        return "PathGui::ViewProviderAreaView";
    }
    virtual App::DocumentObjectExecReturn *execute(void);

    App::PropertyLink       Source;
    App::PropertyInteger    SectionIndex;
    App::PropertyInteger    SectionCount;
};

typedef App::FeaturePythonT<FeatureAreaView> FeatureAreaViewPython;

} //namespace Path


#endif // PATH_FeaturePath_H
