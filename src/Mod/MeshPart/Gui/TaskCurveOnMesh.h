/***************************************************************************
 *   Copyright (c) 2017 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHPART_GUI_TASKCURVEONMESH_H
#define MESHPART_GUI_TASKCURVEONMESH_H

#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"
#include <QPointer>

namespace Gui {
class View3DInventor;
}

namespace MeshPartGui
{

class Ui_TaskCurveOnMesh;
class CurveOnMeshHandler;

class CurveOnMeshWidget : public QWidget
{
    Q_OBJECT

public:
    CurveOnMeshWidget(Gui::View3DInventor* view, QWidget* parent=0);
    ~CurveOnMeshWidget();

    void reject();

protected:
    void changeEvent(QEvent *e);
    void setup();

private Q_SLOTS:
    void on_startButton_clicked();

private:
    Ui_TaskCurveOnMesh* ui;
    CurveOnMeshHandler* myCurveHandler;
    QPointer<Gui::View3DInventor> myView;
};

class TaskCurveOnMesh : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskCurveOnMesh(Gui::View3DInventor* view);
    ~TaskCurveOnMesh();

public:
    bool reject();

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Close; }

private:
    CurveOnMeshWidget* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} //namespace MeshPartGui

#endif // MESHPART_GUI_TASKCURVEONMESH_H
