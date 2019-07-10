/***************************************************************************
 *   Copyright (c) 2013 Jan Rheinländer <jrheinlaender[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_DATUMFEATURE_H
#define PART_DATUMFEATURE_H

#include "stdexport.h"
#include <QString>
#include "App/PropertyLinks.h"

#include "PartFeature.h"
#include "AttachExtension.h"

namespace Part
{

// This generic class is defined here so that the Sketcher module can access datum features
// without creating a dependency on PartDesign

class Standard_EXPORT Datum : public Part::Feature, public Part::AttachExtension
{
    PROPERTY_HEADER_WITH_EXTENSIONS(Part::Datum);

public:
    Datum();
    virtual ~Datum();
    //short mustExecute();

    /// returns the type name of the view provider
    virtual const char* getViewProviderName(void) const = 0;

    /// Return a shape including Placement representing the datum feature
    TopoDS_Shape getShape() const;

    /// Returns a point of the feature it counts as it's base
    virtual Base::Vector3d getBasePoint () const;

protected:
    void onDocumentRestored();
    void handleChangedPropertyName(Base::XMLReader &reader, const char* TypeName, const char* PropName);
};

} //namespace Part


#endif // PART_DATUMFEATURE_H
