/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "TaskEditControl.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>

using namespace Gui::TaskView;

TaskEditControl::TaskEditControl(QWidget *parent)
    : TaskWidget(parent)
{
    hboxLayout = new QHBoxLayout(this);
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(true);

    hboxLayout->addWidget(buttonBox);
}

TaskEditControl::~TaskEditControl()
{
}

QDialogButtonBox* TaskEditControl::standardButtons() const
{
    return buttonBox;
}

#include "moc_TaskEditControl.cpp"
