/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <QMessageBox>

#include "TaskDialog.h"

using namespace Gui::TaskView;


//**************************************************************************
//**************************************************************************
// TaskDialog
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TaskDialog::TaskDialog()
    : QObject(0), pos(North)
{

}

TaskDialog::~TaskDialog()
{
    for (std::vector<QWidget*>::iterator it=Content.begin();it!=Content.end();++it) {
        delete *it;
        *it = 0;
    }
}

//==== Slots ===============================================================

const std::vector<QWidget*> &TaskDialog::getDialogContent(void) const
{
    return Content;
}

bool TaskDialog::canClose() const
{
    QMessageBox msgBox;
    msgBox.setText(tr("A dialog is already open in the task panel"));
    msgBox.setInformativeText(QObject::tr("Do you want to close this dialog?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
        return true;
    else
        return false;
}

//==== calls from the TaskView ===============================================================

void TaskDialog::open()
{

}

void TaskDialog::clicked(int)
{

}

bool TaskDialog::accept()
{
    return true;
}

bool TaskDialog::reject()
{
    return true;
}

void TaskDialog::helpRequested()
{

}




#include "moc_TaskDialog.cpp"
