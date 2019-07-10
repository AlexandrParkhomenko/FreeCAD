/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef FEATURE_MESH_SETOPERATIONS_H
#define FEATURE_MESH_SETOPERATIONS_H

#include "App/PropertyStandard.h"

#include "MeshFeature.h"

#include "App/PropertyLinks.h"
#include "App/PropertyGeo.h"


namespace Mesh
{

/**
 * Set Operations on meshes
 * Operations so far: Intersections, Union, Difference
 * @author Berthold Grupp
 */
class SetOperations : public Mesh::Feature
{
    PROPERTY_HEADER(Mesh::SetOperations);

public:
    SetOperations();

    App::PropertyLink   Source1;
    App::PropertyLink   Source2;
    App::PropertyString OperationType;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    //@}
};

}

#endif // FEATURE_MESH_SEGMENT_H 
