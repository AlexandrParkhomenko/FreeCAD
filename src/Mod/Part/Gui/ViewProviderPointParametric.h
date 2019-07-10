/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERPOINTPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERPOINTPARAMETRIC_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProviderPointParametric:public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderPointParametric);

public:
    /// constructor
    ViewProviderPointParametric();
    /// destructor
    virtual ~ViewProviderPointParametric();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERPOINTPARAMETRIC_H

