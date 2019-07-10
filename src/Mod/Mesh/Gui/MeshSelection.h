/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESHGUI_MESHSELECTION_H
#define MESHGUI_MESHSELECTION_H

#include "stdexport.h"
#include <vector>
#include <QWidget>
#include <Inventor/nodes/SoEventCallback.h>
#include "Gui/SelectionObject.h"
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"

namespace Gui {
    class View3DInventorViewer;
}

namespace MeshGui {

class ViewProviderMesh;

class MeshGuiExport MeshSelection
{
public:
    MeshSelection();
    ~MeshSelection();

    void startSelection();
    void startDeselection();
    void stopSelection();
    bool deleteSelection();
    bool deleteSelectionBorder();
    void fullSelection();
    void clearSelection();
    void invertSelection();

    void selectComponent(int);
    void deselectComponent(int);
    void selectTriangle();
    void deselectTriangle();

    void setCheckOnlyPointToUserTriangles(bool);
    bool isCheckedOnlyPointToUserTriangles() const;
    void setCheckOnlyVisibleTriangles(bool);
    bool isCheckedOnlyVisibleTriangles() const;
    void setAddComponentOnClick(bool);
    void setRemoveComponentOnClick(bool);
    void setObjects(const std::vector<Gui::SelectionObject>&);
    std::vector<App::DocumentObject*> getObjects() const;
    void setViewer(Gui::View3DInventorViewer* v);

protected:
    void setCallback(SoEventCallbackCB *cb);
    std::list<ViewProviderMesh*> getViewProviders() const;
    Gui::View3DInventorViewer* getViewer() const;
    void prepareFreehandSelection(bool,SoEventCallbackCB *cb);
    void startInteractiveCallback(Gui::View3DInventorViewer* viewer,SoEventCallbackCB *cb);
    void stopInteractiveCallback(Gui::View3DInventorViewer* viewer);

private:
    static void selectGLCallback(void * ud, SoEventCallback * n);
    static void pickFaceCallback(void * ud, SoEventCallback * n);

private:
    bool onlyPointToUserTriangles, onlyVisibleTriangles;
    bool addToSelection, addComponent, removeComponent;
    SoEventCallbackCB *activeCB;
    SoEventCallbackCB *selectionCB;
    Gui::View3DInventorViewer* ivViewer;
    mutable std::vector<Gui::SelectionObject> meshObjects;

    static unsigned char cross_bitmap[];
    static unsigned char cross_mask_bitmap[];
};

}

#endif // MESHGUI_MESHSELECTION_H
