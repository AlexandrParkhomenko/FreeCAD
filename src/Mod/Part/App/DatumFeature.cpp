/***************************************************************************
 *   Copyright (c) 2013 Jan Rheinländer <jrheinlaender[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "DatumFeature.h"


using namespace Part;
using namespace Attacher;

PROPERTY_SOURCE_ABSTRACT_WITH_EXTENSIONS(Part::Datum, Part::Feature)

Datum::Datum(void)
{
    AttachExtension::initExtension(this);
    touch();
}

Datum::~Datum()
{
}

void Datum::onDocumentRestored()
{
    // This seems to be the only way to make the ViewProvider display the datum feature
    Support.touch();
    Part::Feature::onDocumentRestored();
}

TopoDS_Shape Datum::getShape() const
{
    Part::TopoShape sh = Shape.getShape();
    sh.setPlacement(Placement.getValue());
    return sh.getShape();
}

Base::Vector3d Datum::getBasePoint () const {
    return Placement.getValue().getPosition();
}

void Datum::handleChangedPropertyName(Base::XMLReader &reader, const char* TypeName, const char* PropName)
{
    extHandleChangedPropertyName(reader, TypeName, PropName); // AttachExtension
}
