/***************************************************************************
 *   Copyright (c) 2011 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_TASKVIEW_TaskSketcherMessages_H
#define GUI_TASKVIEW_TaskSketcherMessages_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/Selection.h"
#include <boost/signals2.hpp>

class Ui_TaskSketcherMessages;
typedef boost::signals2::connection Connection;

namespace App {
class Property;
}

namespace SketcherGui { 

class ViewProviderSketch;

class TaskSketcherMessages : public Gui::TaskView::TaskBox
{
    Q_OBJECT

public:
    TaskSketcherMessages(ViewProviderSketch *sketchView);
    ~TaskSketcherMessages();

    void slotSetUp(QString msg);
    void slotSolved(QString msg);

private Q_SLOTS:
    void on_labelConstrainStatus_linkActivated(const QString &);
    void on_autoUpdate_stateChanged(int state);
    void on_autoRemoveRedundants_stateChanged(int state);
    void on_manualUpdate_clicked(bool checked);
    
protected:
    ViewProviderSketch *sketchView;
    Connection connectionSetUp;
    Connection connectionSolved;

private:
    QWidget* proxy;
    Ui_TaskSketcherMessages* ui;
};

} //namespace SketcherGui

#endif // GUI_TASKVIEW_TaskSketcherMessages_H
