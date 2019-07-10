/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <gp_Trsf.hxx>
# include <gp_Ax1.hxx>


//#include <strstream>
//#include "Base/Console.h"
//#include "Base/Writer.h"
//#include "Base/Reader.h"
//#include "Base/Exception.h"
//#include "Base/FileInfo.h"
//#include "Base/Stream.h"
#include "Base/Placement.h"
#include "Base/Rotation.h"

#include "PartFeatureReference.h"

using namespace Part;


PROPERTY_SOURCE(Part::FeatureReference, App::GeoFeature)


FeatureReference::FeatureReference(void) 
{
    ADD_PROPERTY(Reference, (0));
}

FeatureReference::~FeatureReference()
{
}

short FeatureReference::mustExecute(void) const
{
    return GeoFeature::mustExecute();
}

App::DocumentObjectExecReturn *FeatureReference::execute(void)
{
    return App::DocumentObject::StdReturn;
}

TopLoc_Location FeatureReference::getLocation() const
{
    Base::Placement pl = this->Placement.getValue();
    Base::Rotation rot(pl.getRotation());
    Base::Vector3d axis;
    double angle;
    rot.getValue(axis, angle);
    gp_Trsf trf;
    trf.SetRotation(gp_Ax1(gp_Pnt(), gp_Dir(axis.x, axis.y, axis.z)), angle);
    trf.SetTranslationPart(gp_Vec(pl.getPosition().x,pl.getPosition().y,pl.getPosition().z));
    return TopLoc_Location(trf);
}

// ---------------------------------------------------------


