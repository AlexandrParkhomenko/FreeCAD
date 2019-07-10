/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#ifndef PART_FeaturePartCurveNet_H
#define PART_FeaturePartCurveNet_H


#include "PartFeature.h"

namespace Part
{


class CurveNet :public Part::Feature
{
    PROPERTY_HEADER(Part::FeaturePartCurveNet);

public:
    CurveNet();

    App::PropertyString FileName;

    /** @name methods override Feature */
    //@{
    /// recalculate the Feature
    App::DocumentObjectExecReturn *execute(void);
    short mustExecute() const;
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderCurveNet";
    }
    //@}
};

}


#endif // PART_FeaturePartCurveNet_H
