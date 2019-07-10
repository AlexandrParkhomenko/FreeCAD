/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_TASKVIEW_TaskSketcherCreateCommands_H
#define GUI_TASKVIEW_TaskSketcherCreateCommands_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/Selection.h"




namespace App {
class Property;
}

namespace Gui {
class ViewProvider;
namespace TaskView {



class TaskSketcherCreateCommands : public TaskBox, public Gui::SelectionSingleton::ObserverType
{
    Q_OBJECT

public:
    TaskSketcherCreateCommands(QWidget *parent = 0);
    ~TaskSketcherCreateCommands();
    /// Observer message from the Selection
    void OnChange(Gui::SelectionSingleton::SubjectType &rCaller,
                  Gui::SelectionSingleton::MessageType Reason);

private Q_SLOTS:
 
protected:
    void changeEvent(QEvent *e);


private:
    //QWidget* proxy;
};

} //namespace TaskView
} //namespace Gui

#endif // GUI_TASKVIEW_TASKAPPERANCE_H
