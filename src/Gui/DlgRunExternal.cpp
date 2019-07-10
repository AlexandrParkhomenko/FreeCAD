/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <QFileDialog>
# include <QMessageBox>

#include "Application.h"
#include "MainWindow.h"
#include "DlgRunExternal.h"
#include "FileDialog.h"

#include "ui_DlgRunExternal.h"


using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgRunExternal */

/**
 *  Constructs a DlgRunExternal which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgRunExternal::DlgRunExternal( QWidget* parent, Qt::WindowFlags fl )
    : QDialog(parent, fl),process(this),advancedHidden(true)
{
    ui = new Ui_DlgRunExternal();
    ui->setupUi(this);
    connect(&process,SIGNAL(finished(int, QProcess::ExitStatus)),
            this,SLOT(finished(int, QProcess::ExitStatus)));
    connect(ui->buttonAccept,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->buttonDiscard,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui->buttonAbort,SIGNAL(clicked()),this,SLOT(abort()));
    connect(ui->buttonAdvanced,SIGNAL(clicked()),this,SLOT(advanced()));

    ui->gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    ui->extensionWidget->hide();
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgRunExternal::~DlgRunExternal()
{
    // no need to delete child widgets, Qt does it all for us
    delete ui;
}

int DlgRunExternal::Do(void)
{
    QFileInfo ifo (ProcName);

    ui->programName->setText(ifo.baseName());
    ui->programPath->setText(ProcName);
    process.start(ProcName,arguments);

    ui->buttonAccept->setEnabled(false);
    ui->buttonDiscard->setEnabled(false);
    return exec();
}

void DlgRunExternal::reject (void)
{
    QDialog::reject();
}

void DlgRunExternal::accept (void)
{
    QDialog::accept();
}

void DlgRunExternal::abort (void)
{
    process.terminate();
    DlgRunExternal::reject();
}

void DlgRunExternal::advanced (void)
{
    if (advancedHidden){
        ui->extensionWidget->show();
        advancedHidden = false;
    }
    else {
        ui->extensionWidget->hide();
        advancedHidden = true;
    }
}

void DlgRunExternal::finished (int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode); 
    Q_UNUSED(exitStatus); 
    ui->buttonAccept->setEnabled(true);
    ui->buttonDiscard->setEnabled(true);
    ui->buttonAbort->setEnabled(false);
}

void DlgRunExternal::on_chooseProgram_clicked()
{
    QString fn;
    fn = QFileDialog::getOpenFileName(this, tr("Select a file"), ui->programPath->text());
    if (!fn.isEmpty()) {
        ui->programPath->setText(fn);
    }
}

#include "moc_DlgRunExternal.cpp"

