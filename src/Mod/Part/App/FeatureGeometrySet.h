/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2010     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#ifndef PART_FeatureGeometrySet_H
#define PART_FeatureGeometrySet_H

#include "stdexport.h"
#include "PropertyGeometryList.h"

#include "PartFeature.h"

namespace Part
{


class Standard_EXPORT FeatureGeometrySet :public Part::Feature
{
    PROPERTY_HEADER(Part::FeatureGeometrySet);

public:
    FeatureGeometrySet();

    PropertyGeometryList GeometrySet;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
     /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderGeometrySet";
    }
    //@}

};

} //namespace Part


#endif // PART_FeatureGeometrySet_H
