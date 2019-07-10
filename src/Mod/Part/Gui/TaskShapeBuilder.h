/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_TASKSHAPEBUILDER_H
#define PARTGUI_TASKSHAPEBUILDER_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/Selection.h"

namespace PartGui { 

class ShapeBuilderWidget : public QWidget,
                           public Gui::SelectionObserver
{
    Q_OBJECT

public:
    ShapeBuilderWidget(QWidget* parent = 0);
    ~ShapeBuilderWidget();

    bool accept();
    bool reject();

private Q_SLOTS:
    void on_createButton_clicked();
    void switchMode(int);

private:
    virtual void onSelectionChanged(const Gui::SelectionChanges& msg);

private:
    void createEdgeFromVertex();
    void createWireFromEdge();
    void createFaceFromVertex();
    void createFaceFromEdge();
    void createShellFromFace();
    void createSolidFromShell();
    void changeEvent(QEvent *e);

private:
    class Private;
    Private* d;
};

class TaskShapeBuilder : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskShapeBuilder();
    ~TaskShapeBuilder();

public:
    void open();
    bool accept();
    bool reject();
    void clicked(int);

    QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Close; }

private:
    ShapeBuilderWidget* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} //namespace PartGui

#endif // PARTGUI_TASKSHAPEBUILDER_H
