/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_TASKSWEEP_H
#define PARTGUI_TASKSWEEP_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/TaskView/TaskDialog.h"

class QTreeWidgetItem;

namespace Gui {
class SelectionObject;
class StatusWidget;
}
namespace PartGui { 

class SweepWidget : public QWidget
{
    Q_OBJECT

public:
    SweepWidget(QWidget* parent = 0);
    ~SweepWidget();

    bool accept();
    bool reject();

private Q_SLOTS:
    void onCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*);
    void on_buttonPath_clicked();

private:
    void changeEvent(QEvent *e);
    void findShapes();
    bool isPathValid(const Gui::SelectionObject& sel) const;

private:
    class Private;
    Private* d;
};

class TaskSweep : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskSweep();
    ~TaskSweep();

public:
    void open();
    bool accept();
    bool reject();
    void clicked(int);

    QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok|QDialogButtonBox::Cancel|QDialogButtonBox::Help; }

private:
    SweepWidget* widget;
    Gui::StatusWidget* label;
    Gui::TaskView::TaskBox* taskbox;
};

} //namespace PartGui

#endif // PARTGUI_TASKSWEEP_H
