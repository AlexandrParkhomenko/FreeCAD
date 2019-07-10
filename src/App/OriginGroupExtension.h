/***************************************************************************
 *   Copyright (c) Alexander Golubev (Fat-Zer) <fatzer2@gmail.com> 2015    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef ORIGINGROUP_H_QHTU73IF
#define ORIGINGROUP_H_QHTU73IF

#include "stdexport.h"
#include "GeoFeatureGroupExtension.h"
#include "PropertyLinks.h"

namespace App {
class Origin;

/**
 * Represents an abstract placeable group of objects with an associated Origin
 */
class AppExport OriginGroupExtension : public App::GeoFeatureGroupExtension
{
    EXTENSION_PROPERTY_HEADER_WITH_OVERRIDE(App::OriginGroupExtension);
    
public:
    OriginGroupExtension ();
    virtual ~OriginGroupExtension ();

    /// Returns the origin link or throws an exception
    App::Origin *getOrigin () const;

    /// returns the type name of the ViewProvider
    virtual const char* getViewProviderName () const {
        return "Gui::ViewProviderOriginGroup";
    }

    /** 
     * Returns the origin group which contains this object.
     * In case this object is not part of any geoFeatureGroup 0 is returned.
     * @param obj       the object to search for
     */
    static DocumentObject* getGroupOfObject (const DocumentObject* obj);

    /// Returns true on changing OriginFeature set
    virtual short extensionMustExecute () override;
    
    /// Origin linked to the group
    PropertyLink Origin;
    
    //changes all links of obj to a origin to point to this groupes origin
    void relinkToOrigin(App::DocumentObject* obj);
    
    virtual std::vector<DocumentObject*> addObjects(std::vector<DocumentObject*> obj) override;
    virtual bool hasObject(const DocumentObject* obj, bool recursive = false) const override;

protected:
    /// Checks integrity of the Origin
    virtual App::DocumentObjectExecReturn *extensionExecute () override;
    /// Creates the corresponding Origin object
    virtual void onExtendedSetupObject () override;
    /// Removes all planes and axis if they are still linked to the document
    virtual void onExtendedUnsetupObject () override;
};

typedef ExtensionPythonT<GroupExtensionPythonT<OriginGroupExtension>> OriginGroupExtensionPython;

} /* App */

#endif /* end of include guard: ORIGINGROUP_H_QHTU73IF */
