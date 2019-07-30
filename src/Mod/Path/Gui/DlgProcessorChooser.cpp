/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QPixmap>
# include <QDialog>
# include <QListIterator>

#include "Gui/Application.h"
#include "Gui/BitmapFactory.h"
#include "Gui/MainWindow.h"

#include "App/Document.h"
#include "Base/Tools.h"

#include "DlgProcessorChooser.h"
#include "ui_DlgProcessorChooser.h"

using namespace PathGui;

/* TRANSLATOR PathGui::DlgProcessorChooser */

DlgProcessorChooser::DlgProcessorChooser(std::vector<std::string> &scriptnames, bool withArguments)
  : QDialog(Gui::getMainWindow()), ui(new Ui_DlgProcessorChooser)
{
    ui->setupUi(this);
    ui->comboBox->addItem(tr("None"));
    for (std::vector<std::string>::const_iterator it = scriptnames.begin(); it != scriptnames.end(); ++it)
        ui->comboBox->addItem(QString((*it).c_str()));
    QMetaObject::connectSlotsByName(this);
    if (withArguments) {
      ui->argsLabel->setEnabled(true);
      ui->argsLineEdit->setEnabled(true);
    }
}

DlgProcessorChooser::~DlgProcessorChooser()
{
    delete ui;
}

std::string DlgProcessorChooser::getProcessor()
{
    return processor;
}

std::string DlgProcessorChooser::getArguments()
{
  return arguments;
}

void DlgProcessorChooser::accept()
{
    if (ui->comboBox->currentText() == tr("None")) {
        processor = "";
        arguments = "";
    } else {
        processor = ui->comboBox->currentText().toUtf8().data();
        arguments = ui->argsLineEdit->text().toUtf8().data();
    }
    QDialog::accept();
}
#include "moc_DlgProcessorChooser.cpp"
