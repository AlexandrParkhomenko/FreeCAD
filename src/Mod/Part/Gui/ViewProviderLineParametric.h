/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERLINEPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERLINEPARAMETRIC_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProviderLineParametric:public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderLineParametric);

public:
    /// constructor
    ViewProviderLineParametric();
    /// destructor
    virtual ~ViewProviderLineParametric();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERLINEPARAMETRIC_H

