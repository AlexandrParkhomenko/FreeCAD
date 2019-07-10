/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2012     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef ORIGINFEATURE_H_6ZWJPB5V
#define ORIGINFEATURE_H_6ZWJPB5V

#include "stdexport.h"
#include "GeoFeature.h"

namespace App
{

class Origin;

/** Plane Object
 *  Used to define planar support for all kind of operations in the document space
 */
class AppExport OriginFeature: public App::GeoFeature
{
    PROPERTY_HEADER(App::OriginFeature);
public:
    /// additional information about the feature usage (e.g. "BasePlane-XY" or "Axis-X" in a Origin)
    PropertyString Role;

    /// Constructor
    OriginFeature(void);
    virtual ~OriginFeature();

    /// Finds the origin object this plane belongs to
    App::Origin *getOrigin ();
};

class AppExport Plane: public App::OriginFeature {
    PROPERTY_HEADER(App::OriginFeature);
public:
    virtual const char* getViewProviderName(void) const {
        return "Gui::ViewProviderPlane";
    }
};

class AppExport Line: public App::OriginFeature {
    PROPERTY_HEADER(App::OriginFeature);
public:
    virtual const char* getViewProviderName(void) const {
        return "Gui::ViewProviderLine";
    }
};

} //namespace App

#endif /* end of include guard: ORIGINFEATURE_H_6ZWJPB5V */
