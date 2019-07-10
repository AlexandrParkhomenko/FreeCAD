/***************************************************************************
 *   Copyright (c) Juergen Riegel         <juergen.riegel@web.de>          *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_CONTROL_H
#define GUI_CONTROL_H


#include "stdexport.h"
#include <QObject>
#include <bitset>
#include <stack>

#include "Gui/TaskView/TaskDialog.h"

class QTabWidget;

namespace App
{
  class DocumentObject;
  class Document;
}

namespace Gui
{
namespace TaskView
{
    class TaskDialog;
    class TaskView;
}


/** The control class
 */
class GuiExport ControlSingleton : public QObject
{
     Q_OBJECT

public:
    static ControlSingleton& instance(void);
    static void destruct (void);

    /** @name dialog handling 
     *  These methods are used to control the TaskDialog stuff.
     */
    //@{
    /// This method starts a task dialog in the task view
    void showDialog(Gui::TaskView::TaskDialog *dlg);
    Gui::TaskView::TaskDialog* activeDialog() const;
    //void closeDialog();
    //@}

    /** @name task view handling 
     */
    //@{
    Gui::TaskView::TaskView* taskPanel() const;
    /// raising the model view
    void showModelView();
    /// get the tab panel
    QTabWidget* tabPanel() const;
    //@}

    /*!
      If a task dialog is open then it indicates whether this task dialog allows other commands to modify
      the document while it is open. If no task dialog is open true is returned.
     */
    bool isAllowedAlterDocument(void) const;
    /*!
      If a task dialog is open then it indicates whether this task dialog allows other commands to modify
      the 3d view while it is open. If no task dialog is open true is returned.
     */
    bool isAllowedAlterView(void) const;
    /*!
      If a task dialog is open then it indicates whether this task dialog allows other commands to modify
      the selection while it is open. If no task dialog is open true is returned.
     */
    bool isAllowedAlterSelection(void) const;

public Q_SLOTS:
    void accept();
    void reject();
    void closeDialog();
    /// raises the task view panel 
    void showTaskView();

private Q_SLOTS:
    /// This get called by the TaskView when the Dialog is finished
    void closedDialog();

private:
    Gui::TaskView::TaskView *getTaskPanel();

private:
    struct status {
        std::bitset<32> StatusBits;
    } CurrentStatus;

    std::stack<status> StatusStack;

    Gui::TaskView::TaskDialog *ActiveDialog;
 
private:
    /// Construction
    ControlSingleton();
    /// Destruction
    virtual ~ControlSingleton();

    static ControlSingleton* _pcSingleton;
};

/// Get the global instance
inline ControlSingleton& Control(void)
{
    return ControlSingleton::instance();
}

} //namespace Gui

#endif // GUI_CONTROL_H
