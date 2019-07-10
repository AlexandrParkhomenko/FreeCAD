/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <Inventor/SbColor.h>
# include <Inventor/fields/SoSFColor.h> 
# include <Inventor/nodes/SoCamera.h>
# include <Inventor/nodes/SoSeparator.h>
# include <Inventor/nodes/SoDirectionalLight.h>
# include <Inventor/SoPickedPoint.h>
# include <Inventor/actions/SoRayPickAction.h> 

#include "Base/Parameter.h"
#include "App/Document.h"

#include "Window.h"
#include "ViewProviderFeature.h"
#include "View3DInventorViewer.h"


using namespace Gui;


PROPERTY_SOURCE(Gui::ViewProviderFeature, Gui::ViewProviderDocumentObject)

ViewProviderFeature::ViewProviderFeature()
{
    App::Color c;
    ADD_PROPERTY(ColourList,(c));
}

ViewProviderFeature::~ViewProviderFeature()
{
}

void ViewProviderFeature::attach(App::DocumentObject *pcObj)
{
    ViewProviderDocumentObject::attach(pcObj);
}
