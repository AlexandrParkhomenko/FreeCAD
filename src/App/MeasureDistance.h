/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef APP_MEASUREDISTANCE_H
#define APP_MEASUREDISTANCE_H

#include "stdexport.h"
#include "DocumentObject.h"
#include "PropertyGeo.h"
#include "PropertyUnits.h"


namespace App
{

class AppExport MeasureDistance : public DocumentObject
{
    PROPERTY_HEADER(App::MeasureDistance);

public:
    /// Constructor
    MeasureDistance(void);
    virtual ~MeasureDistance();

    App::PropertyVector P1;
    App::PropertyVector P2;
    App::PropertyDistance Distance;

    /// recalculate the object
    virtual DocumentObjectExecReturn *execute(void);

    /// returns the type name of the ViewProvider
    const char* getViewProviderName(void) const {
        return "Gui::ViewProviderMeasureDistance";
    }

protected:
    virtual void onChanged(const Property* prop);
};

} //namespace App


#endif // APP_MEASUREDISTANCE_H
