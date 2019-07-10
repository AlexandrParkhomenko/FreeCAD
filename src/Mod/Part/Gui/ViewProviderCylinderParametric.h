/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERCYLINDERPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERCYLINDERPARAMETRIC_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProviderCylinderParametric:public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderCylinderParametric);

public:
    /// constructor
    ViewProviderCylinderParametric();
    /// destructor
    virtual ~ViewProviderCylinderParametric();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERCYLINDERPARAMETRIC_H

