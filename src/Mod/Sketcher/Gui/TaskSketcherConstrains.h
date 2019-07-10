/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_TASKVIEW_TaskSketcherConstrains_H
#define GUI_TASKVIEW_TaskSketcherConstrains_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/Selection.h"
#include <boost/signals2.hpp>
#include <QListWidget>

namespace App {
class Property;
}

namespace SketcherGui {

class ViewProviderSketch;
class Ui_TaskSketcherConstrains;

class ConstraintView : public QListWidget
{
    Q_OBJECT

public:
    explicit ConstraintView(QWidget *parent = 0);
    ~ConstraintView();

protected:
    void contextMenuEvent (QContextMenuEvent* event);

Q_SIGNALS:
    void onUpdateDrivingStatus(QListWidgetItem *item, bool status);
    void emitCenterSelectedItems();

protected Q_SLOTS:
    void modifyCurrentItem();
    void renameCurrentItem();
    void centerSelectedItems();
    void deleteSelectedItems();
    void doSelectConstraints();
    void updateDrivingStatus();
    void swapNamedOfSelectedItems();
    void showConstraints();
    void hideConstraints();
};

class TaskSketcherConstrains : public Gui::TaskView::TaskBox, public Gui::SelectionObserver
{
    Q_OBJECT

public:
    TaskSketcherConstrains(ViewProviderSketch *sketchView);
    ~TaskSketcherConstrains();

    /// Observer message from the Selection
    void onSelectionChanged(const Gui::SelectionChanges& msg);

private:
    void slotConstraintsChanged(void);

public Q_SLOTS:
    void on_comboBoxFilter_currentIndexChanged(int);
    void on_listWidgetConstraints_itemSelectionChanged(void);
    void on_listWidgetConstraints_itemActivated(QListWidgetItem *item);
    void on_listWidgetConstraints_itemChanged(QListWidgetItem * item);
    void on_listWidgetConstraints_updateDrivingStatus(QListWidgetItem *item, bool status);
    void on_listWidgetConstraints_emitCenterSelectedItems(void);
    void on_filterInternalAlignment_stateChanged(int state);
    void on_extendedInformation_stateChanged(int state);

protected:
    void changeEvent(QEvent *e);
    ViewProviderSketch *sketchView;
    typedef boost::signals2::connection Connection;
    Connection connectionConstraintsChanged;

private:
    QWidget* proxy;
    bool inEditMode;
    Ui_TaskSketcherConstrains* ui;
};

} //namespace SketcherGui

#endif // GUI_TASKVIEW_TASKAPPERANCE_H
