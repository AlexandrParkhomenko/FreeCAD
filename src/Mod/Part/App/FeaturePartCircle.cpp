/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <BRepBuilderAPI_MakeEdge.hxx>
# include <gp_Circ.hxx>
# include <TopoDS.hxx>
# include <TopoDS_Edge.hxx>

#include "FeaturePartCircle.h"
#include "Base/Tools.h"

using namespace Part;

App::PropertyQuantityConstraint::Constraints Circle::angleRange = {0.0,360.0,1.0};

PROPERTY_SOURCE(Part::Circle, Part::Primitive)


Circle::Circle()
{
    ADD_PROPERTY(Radius,(2.0f));
    ADD_PROPERTY(Angle0,(0.0f));
    Angle0.setConstraints(&angleRange);
    ADD_PROPERTY(Angle1,(360.0f));
    Angle1.setConstraints(&angleRange);
}

Circle::~Circle()
{
}

short Circle::mustExecute() const
{
    if (Angle0.isTouched() ||
        Angle1.isTouched() ||
        Radius.isTouched())
        return 1;
    return Part::Feature::mustExecute();
}

App::DocumentObjectExecReturn *Circle::execute(void)
{
    gp_Circ circle;
    circle.SetRadius(this->Radius.getValue());
    
    BRepBuilderAPI_MakeEdge clMakeEdge(circle, Base::toRadians<double>(this->Angle0.getValue()),
                                               Base::toRadians<double>(this->Angle1.getValue()));
    const TopoDS_Edge& edge = clMakeEdge.Edge();
    this->Shape.setValue(edge);
    return Primitive::execute();
}

void Circle::onChanged(const App::Property* prop)
{
    if (!isRestoring()) {
        if (prop == &Radius || prop == &Angle0 || prop == &Angle1){
            try {
                App::DocumentObjectExecReturn *ret = recompute();
                delete ret;
            }
            catch (...) {
            }
        }
    }
    Part::Feature::onChanged(prop);
}
