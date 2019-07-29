/***************************************************************************
 *   Copyright (c) 2009 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QSplitter>

#include "CombiView.h"
#include "BitmapFactory.h"
#include "PropertyView.h"
#include "ProjectView.h"
#include "Application.h"
#include "Document.h"
#include "Tree.h"
#include "TaskView/TaskView.h"
#include "propertyeditor/PropertyEditor.h"

using namespace Gui;
using namespace Gui::DockWnd;


/* TRANSLATOR Gui::DockWnd::CombiView */

CombiView::CombiView(Gui::Document* pcDocument, QWidget *parent)
  : DockWindow(pcDocument,parent), oldTabIndex(0)
{
    setWindowTitle(tr("CombiView"));

    QGridLayout* pLayout = new QGridLayout(this); 
    pLayout->setSpacing( 0 );
    pLayout->setMargin ( 0 );

    // tabs to switch between Tree/Properties and TaskPanel
    tabs = new QTabWidget ();
    tabs->setObjectName(QString::fromUtf8("combiTab"));
    tabs->setTabPosition(QTabWidget::North);
    pLayout->addWidget( tabs, 0, 0 );

    // splitter between tree and property view
    QSplitter *splitter = new QSplitter();
    splitter->setOrientation(Qt::Vertical);

    // tree widget
    tree =  new TreePanel(this);
    splitter->addWidget(tree);

    // property view
    prop = new PropertyView(this);
    splitter->addWidget(prop);
    tabs->addTab(splitter, QString::fromUtf8("Model"));

    // task panel
    taskPanel = new Gui::TaskView::TaskView(this);
    tabs->addTab(taskPanel,  QString::fromUtf8("Tasks"));

    // task panel
    //projectView = new Gui::ProjectWidget(this);
    //tabs->addTab(projectView,  QString::fromUtf8("Project"));
}

CombiView::~CombiView()
{
}

void CombiView::showDialog(Gui::TaskView::TaskDialog *dlg)
{
    static QIcon icon = Gui::BitmapFactory().pixmap("edit-edit.svg");

    // switch to the TaskView tab
    oldTabIndex = tabs->currentIndex();
    tabs->setCurrentIndex(1);
    tabs->setTabIcon(1, icon);
    // set the dialog
    taskPanel->showDialog(dlg);
}

void CombiView::closeDialog()
{
    // close the dialog
    taskPanel->removeDialog();
}

void CombiView::closedDialog()
{
    static QIcon icon = QIcon();

    // dialog has been closed
    tabs->setCurrentIndex(oldTabIndex);
    tabs->setTabIcon(1, icon);
}

void CombiView::showTreeView()
{
    // switch to the tree view
    tabs->setCurrentIndex(0);
}

void CombiView::showTaskView()
{
    // switch to the task view
    tabs->setCurrentIndex(1);
}

void CombiView::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        tabs->setTabText(0,  QString::fromUtf8("Model"));
        tabs->setTabText(1,  QString::fromUtf8("Tasks"));
        //tabs->setTabText(2,  QString::fromUtf8("Project"));
    }

    DockWindow::changeEvent(e);
}


#include "moc_CombiView.cpp"
