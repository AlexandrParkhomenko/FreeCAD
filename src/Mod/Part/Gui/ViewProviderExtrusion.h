/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDEREXTRUSION_H
#define PARTGUI_VIEWPROVIDEREXTRUSION_H

#include "stdexport.h"
#include "ViewProvider.h"


namespace PartGui {

class PartGuiExport ViewProviderExtrusion : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderExtrusion);

public:
    /// constructor
    ViewProviderExtrusion();
    /// destructor
    virtual ~ViewProviderExtrusion();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void)const;
};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDEREXTRUSION_H
