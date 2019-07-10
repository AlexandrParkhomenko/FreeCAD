/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERREGULARPOLYGON_H
#define PARTGUI_VIEWPROVIDERREGULARPOLYGON_H

#include "stdexport.h"
#include "ViewProvider.h"


namespace PartGui {


class PartGuiExport ViewProviderRegularPolygon : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderRegularPolygon);

public:
    /// constructor
    ViewProviderRegularPolygon();
    /// destructor
    virtual ~ViewProviderRegularPolygon();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERREGULARPOLYGON_H

