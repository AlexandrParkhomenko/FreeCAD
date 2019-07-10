/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERELLIPSEPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERELLIPSEPARAMETRIC_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProviderEllipseParametric:public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderEllipseParametric);

public:
    /// constructor
    ViewProviderEllipseParametric();
    /// destructor
    virtual ~ViewProviderEllipseParametric();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERELLIPSEPARAMETRIC_H

