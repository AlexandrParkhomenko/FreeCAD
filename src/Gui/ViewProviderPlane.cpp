/***************************************************************************
 *   Copyright (c) Juergen Riegel          (juergen.riegel@web.de) 2012    *
 *   Copyright (c) Alexander Golubev (Fat-Zer) <fatzer2@gmail.com> 2015    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <Inventor/nodes/SoAsciiText.h>
# include <Inventor/nodes/SoCoordinate3.h>
# include <Inventor/nodes/SoFont.h>
# include <Inventor/nodes/SoIndexedLineSet.h>
# include <Inventor/nodes/SoSeparator.h>
# include <Inventor/nodes/SoTranslation.h>

#include "ViewProviderOrigin.h"

#include "ViewProviderPlane.h"

using namespace Gui;

PROPERTY_SOURCE(Gui::ViewProviderPlane, Gui::ViewProviderOriginFeature)


ViewProviderPlane::ViewProviderPlane()
{ 
    sPixmap = "Std_Plane";
}

ViewProviderPlane::~ViewProviderPlane()
{ }

void ViewProviderPlane::attach ( App::DocumentObject *obj ) {
    ViewProviderOriginFeature::attach ( obj );
    static const float size = ViewProviderOrigin::defaultSize ();

    static const SbVec3f verts[4] = {
        SbVec3f(size,size,0),   SbVec3f(size,-size,0),
        SbVec3f(-size,-size,0), SbVec3f(-size,size,0),
    };

    // indexes used to create the edges
    static const int32_t lines[6] = { 0, 1, 2, 3, 0, -1 };

    SoSeparator *sep = getOriginFeatureRoot ();

    SoCoordinate3 *pCoords = new SoCoordinate3 ();
    pCoords->point.setNum (4);
    pCoords->point.setValues ( 0, 4, verts );
    sep->addChild ( pCoords );

    SoIndexedLineSet *pLines  = new SoIndexedLineSet ();
    pLines->ref();
    pLines->coordIndex.setNum(6);
    pLines->coordIndex.setValues(0, 6, lines);
    sep->addChild ( pLines );

    SoTranslation *textTranslation = new SoTranslation ();
    textTranslation->ref ();
    textTranslation->translation.setValue ( SbVec3f ( -size * 49. / 50., size * 9./10., 0 ) );
    sep->addChild ( textTranslation );

    sep->addChild ( getLabel () );
}
