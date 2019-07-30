/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QButtonGroup>
# include <QRegExp>
# include <QRegExpValidator>

#include <Interface_Static.hxx>

#include "Base/Parameter.h"
#include "App/Application.h"

#include "DlgSettingsGeneral.h"
#include "ui_DlgSettingsGeneral.h"
#include "ui_DlgImportExportIges.h"
#include "ui_DlgImportExportStep.h"

using namespace PartGui;

DlgSettingsGeneral::DlgSettingsGeneral(QWidget* parent)
  : PreferencePage(parent)
{
    ui = new Ui_DlgSettingsGeneral();
    ui->setupUi(this);
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgSettingsGeneral::~DlgSettingsGeneral()
{
    // no need to delete child widgets, Qt does it all for us
    delete ui;
}

void DlgSettingsGeneral::saveSettings()
{
    ui->checkBooleanCheck->onSave();
    ui->checkBooleanRefine->onSave();
    ui->checkSketchBaseRefine->onSave();
    ui->checkObjectNaming->onSave();
}

void DlgSettingsGeneral::loadSettings()
{
    ui->checkBooleanCheck->onRestore();
    ui->checkBooleanRefine->onRestore();
    ui->checkSketchBaseRefine->onRestore();
    ui->checkObjectNaming->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsGeneral::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

// ----------------------------------------------------------------------------

DlgImportExportIges::DlgImportExportIges(QWidget* parent)
  : PreferencePage(parent)
{
    ui = new Ui_DlgImportExportIges();
    ui->setupUi(this);
    ui->lineEditProduct->setReadOnly(true);

    bg = new QButtonGroup(this);
    bg->addButton(ui->radioButtonBRepOff, 0);
    bg->addButton(ui->radioButtonBRepOn, 1);

    QRegExp rx;
    rx.setPattern(QString("[\\x00-\\x7F]+"));
    QRegExpValidator* companyValidator = new QRegExpValidator(ui->lineEditCompany);
    companyValidator->setRegExp(rx);
    ui->lineEditCompany->setValidator(companyValidator);
    QRegExpValidator* authorValidator = new QRegExpValidator(ui->lineEditAuthor);
    authorValidator->setRegExp(rx);
    ui->lineEditAuthor->setValidator(authorValidator);
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgImportExportIges::~DlgImportExportIges()
{
    // no need to delete child widgets, Qt does it all for us
    delete ui;
}

void DlgImportExportIges::saveSettings()
{
    int unit = ui->comboBoxUnits->currentIndex();
    Base::Reference<ParameterGrp> hGrp = App::GetApplication().GetUserParameter()
        .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part")->GetGroup("IGES");
    hGrp->SetInt("Unit", unit);
    switch (unit) {
        case 1:
            Interface_Static::SetCVal("write.iges.unit","M");
            break;
        case 2:
            Interface_Static::SetCVal("write.iges.unit","IN");
            break;
        default:
            Interface_Static::SetCVal("write.iges.unit","MM");
            break;
    }

    hGrp->SetBool("BrepMode", bg->checkedId() == 1);
    Interface_Static::SetIVal("write.iges.brep.mode", bg->checkedId());

    // Import
    hGrp->SetBool("SkipBlankEntities", ui->checkSkipBlank->isChecked());

    // header info
    hGrp->SetASCII("Company", ui->lineEditCompany->text().toUtf8());
    hGrp->SetASCII("Author", ui->lineEditAuthor->text().toUtf8());
  //hGrp->SetASCII("Product", ui->lineEditProduct->text().toUtf8());

    Interface_Static::SetCVal("write.iges.header.company", ui->lineEditCompany->text().toUtf8());
    Interface_Static::SetCVal("write.iges.header.author", ui->lineEditAuthor->text().toUtf8());
  //Interface_Static::SetCVal("write.iges.header.product", ui->lineEditProduct->text().toUtf8());
}

void DlgImportExportIges::loadSettings()
{
    Base::Reference<ParameterGrp> hGrp = App::GetApplication().GetUserParameter()
        .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part")->GetGroup("IGES");
    int unit = hGrp->GetInt("Unit", 0);
    ui->comboBoxUnits->setCurrentIndex(unit);

    int value = Interface_Static::IVal("write.iges.brep.mode");
    bool brep = hGrp->GetBool("BrepMode", value > 0);
    if (brep)
        ui->radioButtonBRepOn->setChecked(true);
    else
        ui->radioButtonBRepOff->setChecked(true);

    // Import
    ui->checkSkipBlank->setChecked(hGrp->GetBool("SkipBlankEntities", true));

    // header info
    ui->lineEditCompany->setText(QString::fromStdString(hGrp->GetASCII("Company",
        Interface_Static::CVal("write.iges.header.company"))));
    ui->lineEditAuthor->setText(QString::fromStdString(hGrp->GetASCII("Author",
        Interface_Static::CVal("write.iges.header.author"))));
  //ui->lineEditProduct->setText(QString::fromStdString(hGrp->GetASCII("Product")));
    ui->lineEditProduct->setText(QString(
        Interface_Static::CVal("write.iges.header.product")));
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgImportExportIges::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

// ----------------------------------------------------------------------------

DlgImportExportStep::DlgImportExportStep(QWidget* parent)
  : PreferencePage(parent)
{
    ui = new Ui_DlgImportExportStep();
    ui->setupUi(this);
    ui->lineEditProduct->setReadOnly(true);
    ui->radioButtonAP203->setToolTip(tr("Configuration controlled 3D designs of mechanical parts and assemblies"));
    ui->radioButtonAP214->setToolTip(tr("Core data for automotive mechanical design processes"));

    // https://tracker.dev.opencascade.org/view.php?id=25654
    ui->checkBoxPcurves->setToolTip(tr("This parameter indicates whether parametric curves (curves in parametric space of surface)\n"
                                       "should be written into the STEP file. This parameter can be set to off in order to minimize\n"
                                       "the size of the resulting STEP file."));

    QRegExp rx;
    rx.setPattern(QString("[\\x00-\\x7F]+"));
    QRegExpValidator* companyValidator = new QRegExpValidator(ui->lineEditCompany);
    companyValidator->setRegExp(rx);
    ui->lineEditCompany->setValidator(companyValidator);
    QRegExpValidator* authorValidator = new QRegExpValidator(ui->lineEditAuthor);
    authorValidator->setRegExp(rx);
    ui->lineEditAuthor->setValidator(authorValidator);
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgImportExportStep::~DlgImportExportStep()
{
    // no need to delete child widgets, Qt does it all for us
    delete ui;
}

void DlgImportExportStep::saveSettings()
{
    int unit = ui->comboBoxUnits->currentIndex();
    Base::Reference<ParameterGrp> hPartGrp = App::GetApplication().GetUserParameter()
        .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part");

    // General
    Base::Reference<ParameterGrp> hGenGrp = hPartGrp->GetGroup("General");
    int writesurfacecurve = ui->checkBoxPcurves->isChecked() ? 1 : 0;
    hGenGrp->SetInt("WriteSurfaceCurveMode", writesurfacecurve);
    Interface_Static::SetIVal("write.surfacecurve.mode", writesurfacecurve);

    // STEP
    Base::Reference<ParameterGrp> hStepGrp = hPartGrp->GetGroup("STEP");
    hStepGrp->SetInt("Unit", unit);
    switch (unit) {
        case 1:
            Interface_Static::SetCVal("write.step.unit","M");
            break;
        case 2:
            Interface_Static::SetCVal("write.step.unit","IN");
            break;
        default:
            Interface_Static::SetCVal("write.step.unit","MM");
            break;
    }

    // scheme
    if (ui->radioButtonAP203->isChecked()) {
        Interface_Static::SetCVal("write.step.schema","AP203");
        hStepGrp->SetASCII("Scheme", "AP203");
    }
    else {
        // possible values: AP214CD (1996), AP214DIS (1998), AP214IS (2002)
        Interface_Static::SetCVal("write.step.schema","AP214IS");
        hStepGrp->SetASCII("Scheme", "AP214IS");
    }

    // header info
    hStepGrp->SetASCII("Company", ui->lineEditCompany->text().toUtf8());
    hStepGrp->SetASCII("Author", ui->lineEditAuthor->text().toUtf8());
  //hStepGrp->SetASCII("Product", ui->lineEditProduct->text().toUtf8());

    // (h)STEP of Import module
    ui->checkBoxMergeCompound->onSave();
}

void DlgImportExportStep::loadSettings()
{
    Base::Reference<ParameterGrp> hPartGrp = App::GetApplication().GetUserParameter()
        .GetGroup("BaseApp")->GetGroup("Preferences")->GetGroup("Mod/Part");

    // General
    Base::Reference<ParameterGrp> hGenGrp = hPartGrp->GetGroup("General");
    int writesurfacecurve = Interface_Static::IVal("write.surfacecurve.mode");
    writesurfacecurve = hGenGrp->GetInt("WriteSurfaceCurveMode", writesurfacecurve);
    ui->checkBoxPcurves->setChecked(writesurfacecurve == 0 ? false : true);

    // STEP
    Base::Reference<ParameterGrp> hStepGrp = hPartGrp->GetGroup("STEP");
    int unit = hStepGrp->GetInt("Unit", 0);
    ui->comboBoxUnits->setCurrentIndex(unit);

    // scheme
    QString ap = QString::fromStdString(hStepGrp->GetASCII("Scheme",
        Interface_Static::CVal("write.step.schema")));
    if (ap.startsWith(QString("AP203")))
        ui->radioButtonAP203->setChecked(true);
    else
        ui->radioButtonAP214->setChecked(true);

    // header info
    ui->lineEditCompany->setText(QString::fromStdString(hStepGrp->GetASCII("Company")));
    ui->lineEditAuthor->setText(QString::fromStdString(hStepGrp->GetASCII("Author")));
    ui->lineEditProduct->setText(QString(
        Interface_Static::CVal("write.step.product.name")));

    // (h)STEP of Import module
    ui->checkBoxMergeCompound->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgImportExportStep::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsGeneral.cpp"
