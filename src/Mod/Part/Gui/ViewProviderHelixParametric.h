/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERHELIXPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERHELIXPARAMETRIC_H

#include "stdexport.h"
#include "ViewProviderSpline.h"

namespace PartGui {


class PartGuiExport ViewProviderHelixParametric : public ViewProviderSpline
{
    PROPERTY_HEADER(PartGui::ViewProviderHelixParametric);

public:
    /// constructor
    ViewProviderHelixParametric();
    /// destructor
    virtual ~ViewProviderHelixParametric();
    std::vector<std::string> getDisplayModes(void) const;
};

class PartGuiExport ViewProviderSpiralParametric : public ViewProviderSpline
{
    PROPERTY_HEADER(PartGui::ViewProviderSpiralParametric);

public:
    /// constructor
    ViewProviderSpiralParametric();
    /// destructor
    virtual ~ViewProviderSpiralParametric();
    std::vector<std::string> getDisplayModes(void) const;
};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERHELIXPARAMETRIC_H

