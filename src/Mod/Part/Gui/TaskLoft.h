/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_TASKLOFT_H
#define PARTGUI_TASKLOFT_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/TaskView/TaskDialog.h"

class QTreeWidgetItem;

namespace PartGui { 

class LoftWidget : public QWidget
{
    Q_OBJECT

public:
    LoftWidget(QWidget* parent = 0);
    ~LoftWidget();

    bool accept();
    bool reject();

private Q_SLOTS:
    void onCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*);

private:
    void changeEvent(QEvent *e);
    void findShapes();

private:
    class Private;
    Private* d;
};

class TaskLoft : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskLoft();
    ~TaskLoft();

public:
    void open();
    bool accept();
    bool reject();
    void clicked(int);

    QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok|QDialogButtonBox::Cancel; }

private:
    LoftWidget* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} //namespace PartGui

#endif // PARTGUI_TASKLOFT_H
