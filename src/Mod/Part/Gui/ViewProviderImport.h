/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEVPROVIDERIMPORT_H
#define PARTGUI_VIEVPROVIDERIMPORT_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProviderImport : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderImport);

public:
    /// constructor
    ViewProviderImport();
    /// destructor
    virtual ~ViewProviderImport();

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);
};

} // namespace PartGui


#endif // PARTGUI_VIEVPROVIDERIMPORT_H

