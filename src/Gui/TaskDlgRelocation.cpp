/***************************************************************************
 *   Copyright (c) 2010 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "ui_DlgLocationPos.h"
#include "ui_DlgLocationAngle.h"

#include "TaskDlgRelocation.h"
#include "Gui/BitmapFactory.h"

using namespace Gui;

//**************************************************************************
//**************************************************************************
// TaskBoxPosition 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* TRANSLATOR Gui::TaskBoxPosition */

TaskBoxPosition::TaskBoxPosition(QWidget *parent)
    : TaskBox(Gui::BitmapFactory().pixmap("Robot_CreateRobot"),tr("Position"),true, parent)
{
    // we need a separate container widget to add all controls to
    proxy = new QWidget(this);
    ui = new Ui_Position();
    ui->setupUi(proxy);
    QMetaObject::connectSlotsByName(this);

    this->groupLayout()->addWidget(proxy);

    //QObject::connect(ui->horizontalSlider_Axis1,SIGNAL(sliderMoved(int)),this,SLOT(changeSliderA1(int)));
}

TaskBoxPosition::~TaskBoxPosition()
{
    delete ui;
}


//**************************************************************************
//**************************************************************************
// TaskBoxAngle
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* TRANSLATOR Gui::TaskBoxAngle */

TaskBoxAngle::TaskBoxAngle(QWidget *parent)
    : TaskBox(Gui::BitmapFactory().pixmap("Robot_CreateRobot"),tr("Angle"),true, parent)
{
    // we need a separate container widget to add all controls to
    proxy = new QWidget(this);
    ui = new Ui_Angle();
    ui->setupUi(proxy);
    QMetaObject::connectSlotsByName(this);

    this->groupLayout()->addWidget(proxy);

    //QObject::connect(ui->horizontalSlider_Axis1,SIGNAL(sliderMoved(int)),this,SLOT(changeSliderA1(int)));
}

TaskBoxAngle::~TaskBoxAngle()
{
    delete ui;
}


//**************************************************************************
//**************************************************************************
// TaskDialog
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* TRANSLATOR Gui::TaskDlgRelocation */

TaskDlgRelocation::TaskDlgRelocation()
    : TaskDialog()
{
 /*   rob  = new TaskRobot6Axis(pcRobotObject);
    ctr  = new TaskRobotControl(pcRobotObject);
    
    trac = new TaskTrajectory(pcRobotObject,pcTrajectoryObject);
    msg  = new TaskRobotMessages(pcRobotObject);
    
    
    QObject::connect(trac ,SIGNAL(axisChanged(float,float,float,float,float,float,const Base::Placement &)),
                     rob  ,SLOT  (setAxis(float,float,float,float,float,float,const Base::Placement &)));

    Content.push_back(rob);
    Content.push_back(ctr);
    Content.push_back(trac);
    Content.push_back(msg);*/
}

TaskDlgRelocation::~TaskDlgRelocation()
{

}

//==== calls from the TaskView ===============================================================


void TaskDlgRelocation::open()
{
    //msg->hideGroupBox();
    //ctr->hideGroupBox();
}

void TaskDlgRelocation::clicked(int)
{
    
}

bool TaskDlgRelocation::accept()
{
    return true;
}

bool TaskDlgRelocation::reject()
{
    return true;
}

void TaskDlgRelocation::helpRequested()
{

}


#include "moc_TaskDlgRelocation.cpp"
