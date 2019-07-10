/***************************************************************************
 *   Copyright (c) 2012 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_TASKOFFSET_H
#define PARTGUI_TASKOFFSET_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/TaskView/TaskDialog.h"

namespace Part { class Offset; }
namespace PartGui { 

class OffsetWidget : public QWidget
{
    Q_OBJECT

public:
    OffsetWidget(Part::Offset*, QWidget* parent = 0);
    ~OffsetWidget();

    bool accept();
    bool reject();
    Part::Offset* getObject() const;

private Q_SLOTS:
    void on_spinOffset_valueChanged(double);
    void on_modeType_activated(int);
    void on_joinType_activated(int);
    void on_intersection_toggled(bool);
    void on_selfIntersection_toggled(bool);
    void on_fillOffset_toggled(bool);
    void on_updateView_toggled(bool);

private:
    void changeEvent(QEvent *e);

private:
    class Private;
    Private* d;
};

class TaskOffset : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskOffset(Part::Offset*);
    ~TaskOffset();

public:
    void open();
    bool accept();
    bool reject();
    void clicked(int);
    Part::Offset* getObject() const;

    QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok|QDialogButtonBox::Cancel; }

private:
    OffsetWidget* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} //namespace PartGui

#endif // PARTGUI_TASKOFFSET_H
