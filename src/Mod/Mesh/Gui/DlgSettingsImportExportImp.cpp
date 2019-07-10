/***************************************************************************
 *   Copyright (c) 2016 Ian Rees         <ian.rees@gmail.com>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "DlgSettingsImportExportImp.h"
#include "ui_DlgSettingsImportExport.h"
#include "App/Application.h"


using namespace MeshGui;

DlgSettingsImportExport::DlgSettingsImportExport(QWidget* parent)
  : PreferencePage(parent), ui(new Ui_DlgSettingsImportExport)
{
    ui->setupUi(this);
    ui->exportAmfCompressed->setToolTip(tr("This parameter indicates whether ZIP compression\n"
                                           "is used when writing a file in AMF format"));
}

DlgSettingsImportExport::~DlgSettingsImportExport()
{
    // no need to delete child widgets, Qt does it all for us
    delete ui;
}

void DlgSettingsImportExport::saveSettings()
{
    ParameterGrp::handle handle = App::GetApplication().GetParameterGroupByPath
        ("User parameter:BaseApp/Preferences/Mod/Mesh");
    double value = ui->maxDeviationExport->value().getValue();
    handle->SetFloat("MaxDeviationExport", value);
    
    ui->exportAmfCompressed->onSave();
}

void DlgSettingsImportExport::loadSettings()
{
    ParameterGrp::handle handle = App::GetApplication().GetParameterGroupByPath
        ("User parameter:BaseApp/Preferences/Mod/Mesh");
    double value = ui->maxDeviationExport->value().getValue();
    value = handle->GetFloat("MaxDeviationExport", value);
    ui->maxDeviationExport->setValue(value);
    
    ui->exportAmfCompressed->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsImportExport::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsImportExportImp.cpp"

