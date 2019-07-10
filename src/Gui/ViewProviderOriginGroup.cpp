/***************************************************************************
 *   Copyright (c) Alexander Golubev (Fat-Zer) <fatzer2@gmail.com> 2015    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <Inventor/actions/SoGetBoundingBoxAction.h>
# include <Inventor/nodes/SoSeparator.h>
# include <boost/bind.hpp>

#include "Base/Console.h"
#include "App/OriginGroupExtension.h"
#include "App/Origin.h"

#include "Application.h"
#include "Document.h"
#include "View3DInventor.h"
#include "View3DInventorViewer.h"
#include "ViewProviderOrigin.h"
#include "ViewProviderOriginFeature.h"

#include "ViewProviderOriginGroup.h"


using namespace Gui;


PROPERTY_SOURCE_WITH_EXTENSIONS(Gui::ViewProviderOriginGroup, Gui::ViewProviderDocumentObject)

ViewProviderOriginGroup::ViewProviderOriginGroup ()
{
    initExtension(this);
}

ViewProviderOriginGroup::~ViewProviderOriginGroup () 
{
}
