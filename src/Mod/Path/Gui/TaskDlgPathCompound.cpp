/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "TaskDlgPathCompound.h"
#include "ui_TaskDlgPathCompound.h"

#include "Base/Console.h"
#include "Base/Exception.h"
#include "App/Document.h"
#include "App/DocumentObject.h"
#include "Gui/TaskView/TaskSelectLinkProperty.h"
#include "Gui/Application.h"
#include "Gui/Document.h"
#include "Gui/BitmapFactory.h"
#include "Gui/Command.h"

#include "Mod/Path/App/Tooltable.h"


using namespace PathGui;
using namespace Gui;

/* TRANSLATOR PathGui::TaskWidgetPathCompound */


//**************************************************************************
// TaskWidget
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TaskWidgetPathCompound::TaskWidgetPathCompound(ViewProviderPathCompound *CompoundView,QWidget *parent)
    : TaskBox(Gui::BitmapFactory().pixmap("Path-Compound"),tr("Compound paths"),true, parent)
{
    // we need a separate container widget to add all controls to
    proxy = new QWidget(this);
    ui = new Ui_TaskDlgPathCompound();
    ui->setupUi(proxy);
    QMetaObject::connectSlotsByName(this);

    this->groupLayout()->addWidget(proxy);

    Path::FeatureCompound* pcCompound = static_cast<Path::FeatureCompound*>(CompoundView->getObject());
    const std::vector<App::DocumentObject*> &Paths = pcCompound->Group.getValues();
    for (std::vector<App::DocumentObject*>::const_iterator it= Paths.begin();it!=Paths.end();++it) {
        QString name = QString((*it)->getNameInDocument());
        name += QString(" (");
        name += QString((*it)->Label.getValue());
        name += QString(")");
        ui->PathsList->addItem(name);
    }
}

TaskWidgetPathCompound::~TaskWidgetPathCompound()
{
    delete ui;
}

std::vector<std::string> TaskWidgetPathCompound::getList(void) const {
    std::vector<std::string> names;
    for(int i = 0; i < ui->PathsList->count(); i++)
    {
        QListWidgetItem* item = ui->PathsList->item(i);
        QString name = item->text();
        QStringList result;
        result = name.split(QRegExp(QString("\\s+")));
        std::cout << result[0].toStdString() << std::endl;
        names.push_back(result[0].toStdString());
    }
    return names;
}

void TaskWidgetPathCompound::changeEvent(QEvent *e)
{
    TaskBox::changeEvent(e);
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(proxy);
    }
}

//**************************************************************************
// TaskDialog
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TaskDlgPathCompound::TaskDlgPathCompound(PathGui::ViewProviderPathCompound *obj)
    : TaskDialog(),CompoundView(obj)
{
    assert(CompoundView);
    (void)CompoundView; // fix clang warning
    parameter  = new TaskWidgetPathCompound(CompoundView);
    Content.push_back(parameter);
}

TaskDlgPathCompound::~TaskDlgPathCompound()
{
}

//==== calls from the TaskView ===============================================================


void TaskDlgPathCompound::open()
{
}

void TaskDlgPathCompound::clicked(int button)
{
    Q_UNUSED(button);
}

bool TaskDlgPathCompound::accept()
{
    std::vector<App::DocumentObject*> paths;
    Path::FeatureCompound* pcCompound = static_cast<Path::FeatureCompound*>(CompoundView->getObject());
    App::Document* pcDoc = static_cast<App::Document*>(pcCompound->getDocument());
    std::vector<std::string> names = parameter->getList();
    for(std::size_t i = 0; i < names.size(); i++)
    {
        App::DocumentObject* pcPath = static_cast<App::DocumentObject*>(pcDoc->getObject(names[i].c_str()));
        paths.push_back(pcPath);
    }
    pcCompound->Group.setValues(paths);
    Gui::Command::doCommand(Gui::Command::Gui,"Gui.activeDocument().resetEdit()");
    return true;
}

bool TaskDlgPathCompound::reject()
{
    Gui::Command::doCommand(Gui::Command::Gui,"Gui.activeDocument().resetEdit()");
    return true;
}

void TaskDlgPathCompound::helpRequested()
{
}


#include "moc_TaskDlgPathCompound.cpp"
