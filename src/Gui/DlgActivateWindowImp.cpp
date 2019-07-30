/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QApplication>
# include <QHeaderView>
# include <QPushButton>

#include "DlgActivateWindowImp.h"
#include "ui_DlgActivateWindow.h"
#include "MainWindow.h"
#include "MDIView.h"

using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgActivateWindowImp */

/**
 *  Constructs a DlgActivateWindowImp which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgActivateWindowImp::DlgActivateWindowImp(QWidget* parent, Qt::WindowFlags fl)
  : QDialog(parent, fl), ui(new Ui_DlgActivateWindow)
{
    // create widgets
    ui->setupUi(this);
    QPushButton* buttonOk = ui->buttonBox->button(QDialogButtonBox::Ok);
    buttonOk->setText(QApplication::translate("Gui::Dialog::DlgActivateWindow", "&Activate"));
    QTreeWidgetItem* active=0;
    QStringList labels; labels << tr("Windows");
    ui->treeWidget->setHeaderLabels(labels);
    ui->treeWidget->header()->hide();

    QList<QWidget*> windows = getMainWindow()->windows();
    if (windows.isEmpty()) {
        buttonOk->setDisabled(true);
        return;
    }

    QWidget* activeWnd = getMainWindow()->activeWindow();

    for (QList<QWidget*>::ConstIterator it = windows.begin(); it != windows.end(); ++it) {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
        QString title = (*it)->windowTitle();
        title.replace(QString("[*]"), QString(""));
        if ((*it)->isWindowModified())
            title += QString("*");
        item->setText(0, title);
        if (*it == activeWnd)
            active = item;
    }

    if (active)
        ui->treeWidget->setCurrentItem( active );
    ui->treeWidget->setFocus();
}

/** Destroys the object and frees any allocated resources */
DlgActivateWindowImp::~DlgActivateWindowImp()
{
    delete ui;
}

/**
 * Activates the MDI window you wish and closes the dialog.
 */
void DlgActivateWindowImp::accept()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    QList<QWidget*> windows = getMainWindow()->windows();

    if (item) {
        int index = ui->treeWidget->indexOfTopLevelItem(item);
        getMainWindow()->setActiveWindow((MDIView*)windows.at(index));
    }

    QDialog::accept();
}

#include "moc_DlgActivateWindowImp.cpp"
