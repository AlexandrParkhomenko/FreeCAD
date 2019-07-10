/***************************************************************************
 *   Copyright (c) 2011 Juergen Riegel <FreeCAD@juergen-riegel.net>        *
 *   Copyright (c) 2015 Alexander Golubev (Fat-Zer) <fatzer2@gmail.com>    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_ViewProviderGeoFeatureGroup_H
#define GUI_VIEWPROVIDER_ViewProviderGeoFeatureGroup_H


#include "stdexport.h"
#include "ViewProviderDocumentObject.h"
#include "ViewProviderGeoFeatureGroupExtension.h"
#include "ViewProviderPythonFeature.h"

namespace Gui {

class GuiExport ViewProviderGeoFeatureGroup : public ViewProviderDocumentObject,
                                              public ViewProviderGeoFeatureGroupExtension
{
    PROPERTY_HEADER_WITH_EXTENSIONS(Gui::ViewProviderGeoFeatureGroup);

public:
    /// constructor.
    ViewProviderGeoFeatureGroup();
    /// destructor.
    virtual ~ViewProviderGeoFeatureGroup();
};

typedef ViewProviderPythonFeatureT<ViewProviderGeoFeatureGroup> ViewProviderGeoFeatureGroupPython;

} // namespace Gui

#endif // GUI_VIEWPROVIDER_ViewProviderGeoFeatureGroup_H

