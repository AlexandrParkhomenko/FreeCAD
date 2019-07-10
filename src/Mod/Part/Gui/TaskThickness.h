/***************************************************************************
 *   Copyright (c) 2012 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_TASKTHICKNESS_H
#define PARTGUI_TASKTHICKNESS_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/TaskView/TaskDialog.h"

namespace Part { class Thickness; }
namespace PartGui { 

class ThicknessWidget : public QWidget
{
    Q_OBJECT

public:
    ThicknessWidget(Part::Thickness*, QWidget* parent = 0);
    ~ThicknessWidget();

    bool accept();
    bool reject();
    Part::Thickness* getObject() const;

private Q_SLOTS:
    void on_spinOffset_valueChanged(double);
    void on_modeType_activated(int);
    void on_joinType_activated(int);
    void on_intersection_toggled(bool);
    void on_selfIntersection_toggled(bool);
    void on_facesButton_clicked();
    void on_updateView_toggled(bool);

private:
    void changeEvent(QEvent *e);

private:
    class Private;
    Private* d;
};

class TaskThickness : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskThickness(Part::Thickness*);
    ~TaskThickness();

public:
    void open();
    bool accept();
    bool reject();
    void clicked(int);
    Part::Thickness* getObject() const;

    QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok|QDialogButtonBox::Cancel; }

private:
    ThicknessWidget* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} //namespace PartGui

#endif // PARTGUI_TASKTHICKNESS_H
