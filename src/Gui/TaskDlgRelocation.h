/***************************************************************************
 *   Copyright (c) 2010 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_TASKDLGRELOCATE_H
#define GUI_TASKDLGRELOCATE_H

#include "stdexport.h"
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"


class Ui_DlgLocationPos;
class ui_DlgLocationAngle;

namespace Gui {

class TaskBoxPosition : public Gui::TaskView::TaskBox
{
    Q_OBJECT

public:
    TaskBoxPosition(QWidget *parent = 0);
    ~TaskBoxPosition();


private Q_SLOTS:

protected:

private:
    QWidget* proxy;
    Ui_Position* ui;
};

class TaskBoxAngle : public Gui::TaskView::TaskBox
{
    Q_OBJECT

public:
    TaskBoxAngle(QWidget *parent = 0);
    ~TaskBoxAngle();


private Q_SLOTS:

protected:

private:
    QWidget* proxy;
    Ui_Angle* ui;
};


/// 
class GuiExport TaskDlgRelocation : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskDlgRelocation();
    ~TaskDlgRelocation();

public:
    /// is called the TaskView when the dialog is opened
    virtual void open();
    /// is called by the framework if an button is clicked which has no accept or rject role
    virtual void clicked(int);
    /// is called by the framework if the dialog is accepted (Ok)
    virtual bool accept();
    /// is called by the framework if the dialog is rejected (Cancel)
    virtual bool reject();
    /// is called by the framework if the user press the help button 
    virtual void helpRequested();

    /// returns for Close and Help button 
    virtual QDialogButtonBox::StandardButtons getStandardButtons(void) const
	{ return QDialogButtonBox::Ok|QDialogButtonBox::Cancel; }

protected:

};



} //namespace Gui

#endif // ROBOTGUI_TASKDLGSIMULATE_H
