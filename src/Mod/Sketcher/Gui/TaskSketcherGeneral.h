/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_TASKVIEW_TaskSketcherGerneral_H
#define GUI_TASKVIEW_TaskSketcherGerneral_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/Selection.h"
#include <boost/signals2.hpp>

class Ui_TaskSketcherGeneral;

namespace App {
class Property;
}

namespace Gui {
class ViewProvider;
}

namespace SketcherGui {

class ViewProviderSketch;

class SketcherGeneralWidget : public QWidget
{
    Q_OBJECT

public:
    SketcherGeneralWidget(QWidget *parent=0);
    ~SketcherGeneralWidget();

    void saveSettings();
    void loadSettings();
    void setGridSize(double val);
    void checkGridView(bool);
    void checkGridSnap(bool);
    void checkAutoconstraints(bool);

    bool isGridViewChecked() const;
    void saveGridViewChecked();

Q_SIGNALS:
    void emitToggleGridView(bool);
    void emitToggleGridSnap(int);
    void emitSetGridSize(double);
    void emitToggleAutoconstraints(int);
    void emitRenderOrderChanged();

private Q_SLOTS:
    void onToggleGridView(bool on);
    void onSetGridSize(double val);
    void onToggleGridSnap(int state);
    void onRenderOrderChanged();
    void on_checkBoxRedundantAutoconstraints_stateChanged(int);

protected:
    void changeEvent(QEvent *e);

private:
    Ui_TaskSketcherGeneral* ui;
};

class TaskSketcherGeneral : public Gui::TaskView::TaskBox,
                            public Gui::SelectionSingleton::ObserverType
{
    Q_OBJECT

public:
    TaskSketcherGeneral(ViewProviderSketch *sketchView);
    ~TaskSketcherGeneral();
    /// Observer message from the Selection
    void OnChange(Gui::SelectionSingleton::SubjectType &rCaller,
                  Gui::SelectionSingleton::MessageType Reason);

public Q_SLOTS:
    void onToggleGridView(bool on);
    void onSetGridSize(double val);
    void onToggleGridSnap(int state);
    void onToggleAutoconstraints(int state);
    void onRenderOrderChanged();

private:
    void onChangedSketchView(const Gui::ViewProvider&,
                             const App::Property&);

private:
    ViewProviderSketch *sketchView;
    SketcherGeneralWidget* widget;
    boost::signals2::scoped_connection changedSketchView;
};

} //namespace SketcherGui

#endif // GUI_TASKVIEW_TaskSketcherGerneral_H
