/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERPRISM_H
#define PARTGUI_VIEWPROVIDERPRISM_H

#include "stdexport.h"
#include "ViewProvider.h"


namespace PartGui {


class PartGuiExport ViewProviderPrism : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderPrism);

public:
    /// constructor
    ViewProviderPrism();
    /// destructor
    virtual ~ViewProviderPrism();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

class PartGuiExport ViewProviderWedge : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderWedge);

public:
    /// constructor
    ViewProviderWedge();
    /// destructor
    virtual ~ViewProviderWedge();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERPRISM_H

