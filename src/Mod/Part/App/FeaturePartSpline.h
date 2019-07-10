/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#ifndef PART_FEATUREPARTSPLINE_H
#define PART_FEATUREPARTSPLINE_H

#include "stdexport.h"
#include "PartFeature.h"

namespace Part
{

class Standard_EXPORT Spline :public Part::Feature
{
    PROPERTY_HEADER(Part::Spline);

public:
    Spline();
    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "PartGui::ViewProviderSpline";
    }
};

} //namespace Part


#endif // PART_FEATUREPARTSPLINE_H

