/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERRULEDSURFACE_H
#define PARTGUI_VIEWPROVIDERRULEDSURFACE_H

#include "stdexport.h"
#include "ViewProvider.h"




namespace PartGui {


class PartGuiExport ViewProviderRuledSurface:public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderRuledSurface);

public:
    /// constructor
    ViewProviderRuledSurface();
    /// destructor
    virtual ~ViewProviderRuledSurface();

    std::vector<std::string> getDisplayModes(void) const;
    std::vector<App::DocumentObject*> claimChildren() const;
    void updateData(const App::Property*);
    bool onDelete(const std::vector<std::string> &);
    

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERRULEDSURFACE_H

