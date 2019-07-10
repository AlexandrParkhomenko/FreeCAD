/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESHGUI_SELECTION_H
#define MESHGUI_SELECTION_H

#include <vector>
#include <QWidget>
#include <Inventor/nodes/SoEventCallback.h>
#include "Gui/SelectionObject.h"
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"
#include "MeshSelection.h"

namespace MeshGui {

class Ui_Selection;
class Selection : public QWidget
{
    Q_OBJECT

public:
    Selection(QWidget* parent = 0);
    ~Selection();
    void setObjects(const std::vector<Gui::SelectionObject>&);
    std::vector<App::DocumentObject*> getObjects() const;
    bool eventFilter(QObject*, QEvent*);

private Q_SLOTS:
    void on_addSelection_clicked();
    void on_clearSelection_clicked();
    void on_visibleTriangles_toggled(bool);
    void on_screenTriangles_toggled(bool);

private:
    MeshSelection meshSel;
    Ui_Selection* ui;
};

}

#endif // MESHGUI_SELECTION_H
