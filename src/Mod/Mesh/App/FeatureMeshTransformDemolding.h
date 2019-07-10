/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef FEATURE_MESH_TRANSFORM_DEMOLDING_H
#define FEATURE_MESH_TRANSFORM_DEMOLDING_H

#include "FeatureMeshTransform.h"

#include "App/PropertyLinks.h"
#include "App/PropertyGeo.h"
#include "App/PropertyStandard.h"


namespace Mesh
{

/**
 * The TransformDemolding class.
 */
class TransformDemolding : public Transform
{
    PROPERTY_HEADER(Mesh::TransformDemolding);

public:
    TransformDemolding();

    App::PropertyLink Source;
    App::PropertyFloat Rotation;
    App::PropertyVector Axis;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    virtual App::DocumentObjectExecReturn *execute(void);
    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "MeshGui::ViewProviderMeshTransformDemolding";
    }
    //@}
};

}

#endif // FEATURE_MESH_TRANSFORM_H 
