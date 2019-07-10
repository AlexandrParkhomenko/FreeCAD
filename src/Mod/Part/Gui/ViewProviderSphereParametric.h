/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERSPHEREPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERSPHEREPARAMETRIC_H

#include "stdexport.h"
#include "ViewProvider.h"

namespace PartGui {

class PartGuiExport ViewProviderSphereParametric : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderSphereParametric);

public:
    /// constructor
    ViewProviderSphereParametric();
    /// destructor
    virtual ~ViewProviderSphereParametric();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

class PartGuiExport ViewProviderEllipsoid : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderEllipsoid);

public:
    /// constructor
    ViewProviderEllipsoid();
    /// destructor
    virtual ~ViewProviderEllipsoid();
    std::vector<std::string> getDisplayModes(void) const;
};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERSPHEREPARAMETRIC_H

