/***************************************************************************
 *   Copyright (c) 2012 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESHGUI_SEGMENTATION_H
#define MESHGUI_SEGMENTATION_H

#include "stdexport.h"
#include <QWidget>
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"

// forward declarations
namespace Mesh { class Feature; }

namespace MeshGui {
class Ui_Segmentation;

class MeshGuiExport Segmentation : public QWidget
{
public:
    Segmentation(Mesh::Feature* mesh, QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~Segmentation();
    void accept();

protected:
    void changeEvent(QEvent *e);

private:
    Ui_Segmentation* ui;
    Mesh::Feature* myMesh;
};

/**
 * Embed the panel into a task dialog.
 */
class TaskSegmentation : public Gui::TaskView::TaskDialog
{
public:
    TaskSegmentation(Mesh::Feature* mesh);
    ~TaskSegmentation();

public:
    bool accept();

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok | QDialogButtonBox::Cancel; }

private:
    Segmentation* widget;
    Gui::TaskView::TaskBox* taskbox;
};

}

#endif // MESHGUI_SEGMENTATION_H
