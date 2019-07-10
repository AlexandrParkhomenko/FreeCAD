/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESH_FEATURE_H
#define MESH_FEATURE_H

#include "stdexport.h"
#include "App/GeoFeature.h"
#include "App/FeatureCustom.h"
#include "App/FeaturePython.h"

#include "Core/MeshKernel.h"
#include "Mesh.h"
#include "MeshProperties.h"

namespace Base{
  class XMLReader;
  class Writer;
}

namespace MeshCore {
  class MeshKernel;
}

namespace Mesh
{

class Property;
class MeshFeaturePy;

/** Base class of all mesh feature classes in FreeCAD.
 * This class holds a MeshKernel object.
 * \author Werner Mayer
 */
class Standard_EXPORT Feature : public App::GeoFeature
{
    PROPERTY_HEADER(Mesh::Feature);

public:
    /// Constructor
    Feature(void);
    virtual ~Feature();

    /** @name Properties */
    //@{
    /** Property that holds the mesh data. */
    PropertyMeshKernel Mesh;
    //@}

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    virtual App::DocumentObjectExecReturn *execute(void);
    virtual void onChanged(const App::Property* prop);
    //@}

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName(void) const {
        return "MeshGui::ViewProviderMeshFaceSet";
    }
    virtual const App::PropertyComplexGeoData* getPropertyOfGeometry() const {
        return &Mesh;
    }

    /// handles the MeshPy object
    virtual PyObject* getPyObject(void);
};

typedef App::FeatureCustomT<Feature> FeatureCustom;
typedef App::FeaturePythonT<Feature> FeaturePython;

} //namespace Mesh



#endif 
