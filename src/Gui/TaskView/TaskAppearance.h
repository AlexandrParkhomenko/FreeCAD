/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_TASKVIEW_TASKAPPERANCE_H
#define GUI_TASKVIEW_TASKAPPERANCE_H

#include "TaskView.h"
#include "Gui/Selection.h"
#include <boost/signals2.hpp>


class Ui_TaskAppearance;

namespace App {
class Property;
}

namespace Gui {
class ViewProvider;
namespace TaskView {
typedef boost::signals2::connection TaskAppearance_Connection;

class TaskAppearance : public TaskBox, public Gui::SelectionSingleton::ObserverType
{
    Q_OBJECT

public:
    TaskAppearance(QWidget *parent = 0);
    ~TaskAppearance();
    /// Observer message from the Selection
    void OnChange(Gui::SelectionSingleton::SubjectType &rCaller,
                  Gui::SelectionSingleton::MessageType Reason);

private Q_SLOTS:
    void on_changeMode_activated(const QString&);
    void on_changePlot_activated(const QString&);
    void on_spinTransparency_valueChanged(int);
    void on_spinPointSize_valueChanged(int);
    void on_spinLineWidth_valueChanged(int);

protected:
    void changeEvent(QEvent *e);

private:
    void slotChangedObject(const Gui::ViewProvider&, const App::Property& Prop);
    void setDisplayModes(const std::vector<Gui::ViewProvider*>&);
    void setPointSize(const std::vector<Gui::ViewProvider*>&);
    void setLineWidth(const std::vector<Gui::ViewProvider*>&);
    void setTransparency(const std::vector<Gui::ViewProvider*>&);
    std::vector<Gui::ViewProvider*> getSelection() const;

private:
    QWidget* proxy;
    Ui_TaskAppearance* ui;
    TaskAppearance_Connection connectChangedObject;
};

} //namespace TaskView
} //namespace Gui

#endif // GUI_TASKVIEW_TASKAPPERANCE_H
