/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERPLANEPARAMETRIC_H
#define PARTGUI_VIEWPROVIDERPLANEPARAMETRIC_H

#include "stdexport.h"
#include "ViewProvider.h"


class TopoDS_Shape;
class TopoDS_Face;
class SoSeparator;
class SbVec3f;
class SoTransform;

namespace PartGui {


class PartGuiExport ViewProviderPlaneParametric : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderPlaneParametric);

public:
    /// constructor
    ViewProviderPlaneParametric();
    /// destructor
    virtual ~ViewProviderPlaneParametric();

    std::vector<std::string> getDisplayModes(void) const;

protected:

};

class PartGuiExport ViewProviderFace : public ViewProviderPlaneParametric
{
    PROPERTY_HEADER(PartGui::ViewProviderFace);

public:
    ViewProviderFace();
    virtual ~ViewProviderFace();

    virtual std::vector<App::DocumentObject*> claimChildren(void) const;
    virtual bool canDragObjects() const;
    virtual bool canDragObject(App::DocumentObject*) const;
    virtual void dragObject(App::DocumentObject*);
    virtual bool canDropObjects() const;
    virtual bool canDropObject(App::DocumentObject*) const;
    virtual void dropObject(App::DocumentObject*);
};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERPLANEPARAMETRIC_H

