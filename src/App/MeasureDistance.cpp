/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "MeasureDistance.h"

using namespace App;

PROPERTY_SOURCE(App::MeasureDistance, App::DocumentObject)


MeasureDistance::MeasureDistance() 
{
    ADD_PROPERTY_TYPE(P1,(Base::Vector3d()),"Measurement",Prop_None,"First point of measurement");
    ADD_PROPERTY_TYPE(P2,(Base::Vector3d()),"Measurement",Prop_None,"Second point of measurement");
    ADD_PROPERTY_TYPE(Distance,(0.0)       ,"Measurement",App::PropertyType(Prop_ReadOnly|Prop_Output),
                                            "Distance between the points");

}

MeasureDistance::~MeasureDistance()
{
}

DocumentObjectExecReturn *MeasureDistance::execute(void)
{
    Distance.setValue(Base::Distance(P1.getValue(), P2.getValue()));
    return DocumentObject::StdReturn;
}

void MeasureDistance::onChanged(const App::Property* prop)
{
    if (prop == &P1 || prop == &P2) {
        if (!isRestoring()) {
            App::DocumentObjectExecReturn *ret = recompute();
            delete ret;
        }
    }
    DocumentObject::onChanged(prop);
}
