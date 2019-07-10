/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERCIRCLEPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERCIRCLEPARAMETRIC_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProviderCircleParametric:public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderCircleParametric);

public:
    /// constructor
    ViewProviderCircleParametric();
    /// destructor
    virtual ~ViewProviderCircleParametric();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERCIRCLEPARAMETRIC_H

