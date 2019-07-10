/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef FeatureMeshCurvature_H
#define FeatureMeshCurvature_H

#include "stdexport.h"
#include "App/DocumentObject.h"
#include "App/PropertyLinks.h"
#include "App/PropertyGeo.h"

#include "Mesh.h"
#include "MeshProperties.h"

namespace Mesh
{

/**
 * The Curvature class calculates the curvature values of a related mesh feature.
 * @author Werner Mayer
 */
class Standard_EXPORT Curvature : public App::DocumentObject
{
    PROPERTY_HEADER(Mesh::Curvature);

public:
    Curvature();

    App::PropertyLink Source;
    PropertyCurvatureList CurvInfo;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const { 
        return "MeshGui::ViewProviderMeshCurvature"; 
    }
  //@}
};

}

#endif // Curvature_H 
