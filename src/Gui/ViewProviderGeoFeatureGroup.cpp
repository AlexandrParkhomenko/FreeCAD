/***************************************************************************
 *   Copyright (c) 2011 Juergen Riegel <FreeCAD@juergen-riegel.net>        *
 *   Copyright (c) 2015 Alexander Golubev (Fat-Zer) <fatzer2@gmail.com>    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "stdexport.h"
#include <Inventor/nodes/SoGroup.h>

#include "App/GeoFeatureGroupExtension.h"

#include "ViewProviderGeoFeatureGroup.h"


using namespace Gui;


PROPERTY_SOURCE_WITH_EXTENSIONS(Gui::ViewProviderGeoFeatureGroup, Gui::ViewProviderDocumentObject)

ViewProviderGeoFeatureGroup::ViewProviderGeoFeatureGroup()
{
    ViewProviderGeoFeatureGroupExtension::initExtension(this);
}

ViewProviderGeoFeatureGroup::~ViewProviderGeoFeatureGroup()
{
}


// Python feature -----------------------------------------------------------------------

namespace Gui {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Gui::ViewProviderGeoFeatureGroupPython, Gui::ViewProviderGeoFeatureGroup)
/// @endcond

// explicit template instantiation
template class GuiExport ViewProviderPythonFeatureT<ViewProviderGeoFeatureGroup>;
}
