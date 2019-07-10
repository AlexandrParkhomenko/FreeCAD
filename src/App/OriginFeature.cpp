/***************************************************************************
 *   Copyright (c) 2015 Alexander Golubev (Fat-Zer) <fatzer2@gmail.com>    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "Document.h"
#include "Origin.h"

#include "OriginFeature.h"

using namespace App;

PROPERTY_SOURCE(App::OriginFeature, App::GeoFeature)
PROPERTY_SOURCE(App::Plane, App::OriginFeature)
PROPERTY_SOURCE(App::Line, App::OriginFeature)

OriginFeature::OriginFeature()
{
    ADD_PROPERTY_TYPE ( Role, (""), 0, App::Prop_ReadOnly, "Role of the feature in the Origin" ) ;

    // Set placement to read-only
    Placement.setStatus(Property::Hidden, true);
}

OriginFeature::~OriginFeature()
{ }

Origin * OriginFeature::getOrigin () {
    App::Document *doc = getDocument();
    auto origins = doc->getObjectsOfType ( App::Origin::getClassTypeId() );

    auto originIt= std::find_if (origins.begin(), origins.end(), [this] (DocumentObject *origin) {
            assert ( origin->isDerivedFrom ( App::Origin::getClassTypeId() ) );
            return static_cast<App::Origin *> (origin)->hasObject (this);
        } );
    if (originIt == origins.end()) {
        return 0;
    } else {
        assert ( (*originIt)->isDerivedFrom ( App::Origin::getClassTypeId() ) );
        return static_cast<App::Origin *> (*originIt);
    }
}
