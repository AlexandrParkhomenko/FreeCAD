/***************************************************************************
 *   Copyright (c) Alexander Golubev (Fat-Zer) <fatzer2@gmail.com> 2015    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef VIEWPROVIDERORIGINGROUP_H_JIXBOPA7
#define VIEWPROVIDERORIGINGROUP_H_JIXBOPA7

#include "stdexport.h"
#include "ViewProviderGeoFeatureGroup.h"
#include "ViewProviderOriginGroupExtension.h"

namespace Gui {

class GuiExport ViewProviderOriginGroup: public ViewProviderDocumentObject,
                                         public ViewProviderOriginGroupExtension
{
    PROPERTY_HEADER_WITH_EXTENSIONS(Gui::ViewProviderOriginGroup);
public:
    ViewProviderOriginGroup ();
    virtual ~ViewProviderOriginGroup ();
};

} //namespace Gui


#endif /* end of include guard: VIEWPROVIDERORIGINGROUP_H_JIXBOPA7 */
