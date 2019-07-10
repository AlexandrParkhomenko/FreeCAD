/***************************************************************************
 *   Copyright (c) 2018 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_BOXSELECTION_H
#define PARTGUI_BOXSELECTION_H

class SoEventCallback;
class TopoDS_Shape;

namespace Base {
class Polygon2d;
}

namespace Gui {
class View3DInventorViewer;
class ViewVolumeProjection;
}

namespace PartGui {

class BoxSelection
{
public:
    BoxSelection();
    ~BoxSelection();

    void start();

private:
    class FaceSelectionGate;
    void addFacesToSelection(const char* doc, const char* obj,
                             const Gui::ViewVolumeProjection& proj,
                             const Base::Polygon2d& polygon,
                             const TopoDS_Shape& shape);
    static void selectionCallback(void * ud, SoEventCallback * cb);
};

} //namespace PartGui

#endif // PARTGUI_BOXSELECTION_H
