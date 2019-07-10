/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERCONEPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERCONEPARAMETRIC_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProviderConeParametric:public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderConeParametric);

public:
    /// constructor
    ViewProviderConeParametric();
    /// destructor
    virtual ~ViewProviderConeParametric();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERCONEPARAMETRIC_H

