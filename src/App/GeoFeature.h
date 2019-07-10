/***************************************************************************
 *   Copyright (c) Juergen Riegel          (juergen.riegel@web.de) 2002    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_GEOFEATURE_H
#define APP_GEOFEATURE_H

#include "stdexport.h"
#include "DocumentObject.h"
#include "PropertyGeo.h"



namespace App
{


/** Base class of all geometric document objects.
 */
class AppExport GeoFeature : public App::DocumentObject
{
    PROPERTY_HEADER(App::GeoFeature);

public:
    PropertyPlacement Placement;

    /// Constructor
    GeoFeature(void);
    virtual ~GeoFeature();

    /**
     * @brief transformPlacement applies transform to placement of this shape.
     * Override this function to propagate the change of placement to base
     * features, for example. By the time of writing this comment, the function
     * was only called by alignment task (Edit->Alignment)
     * @param transform (input).
     */
    virtual void transformPlacement(const Base::Placement &transform);
    /**
     * This method returns the main property of a geometric object that holds
     * the actual geometry. For a part object this is the Shape property, for
     * a mesh object the Mesh property and so on.
     * The default implementation returns null.
     */
    virtual const PropertyComplexGeoData* getPropertyOfGeometry() const;
    /**
     * @brief getPyObject returns the Python binding object
     * @return the Python binding object
     */
    virtual PyObject* getPyObject(void);
       
    /**
     * @brief Calculates the placement in the global reference coordinate system
     * 
     * In FreeCAD the GeoFeature placement describes the local placement of the object in its parent
     * coordinate system. This is however not always the same as the global reference system. If the
     * object is in a GeoFeatureGroup, hence in another local coordinate system, the Placement
     * property does only give the local transformation. This function can be used to calculate the 
     * placement of the object in the global reference coordinate system taking all stacked local 
     * systems into account.
     * 
     * @return Base::Placement The transformation from the global reference coordinate system
     */
    Base::Placement globalPlacement() const;
};

} //namespace App


#endif // APP_GEOFEATURE_H
