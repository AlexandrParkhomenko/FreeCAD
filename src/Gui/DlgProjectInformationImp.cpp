/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "App/Document.h"
#include "App/PropertyStandard.h"

#include "DlgProjectInformationImp.h"
#include "ui_DlgProjectInformation.h"
#include "Document.h"

#include <QApplication>
#include <QByteArray>
#include <QUrl>
#include <QDesktopServices>

using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgProjectInformationImp */

/**
 *  Constructs a Gui::Dialog::DlgProjectInformationImp as a child of 'parent', with the
 *  name 'name' and widget flags set to 'fl'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgProjectInformationImp::DlgProjectInformationImp(App::Document* doc, QWidget* parent, Qt::WindowFlags fl)
  : QDialog(parent, fl), _doc(doc), ui(new Ui_DlgProjectInformation)
{
    ui->setupUi(this);
    ui->lineEditName->setText(QString(doc->Label.getValue()));
    ui->lineEditPath->setText(QString(doc->FileName.getValue()));
    ui->lineEditUuid->setText(QString(doc->Uid.getValueStr().c_str()));
    ui->lineEditCreator->setText(QString(doc->CreatedBy.getValue()));
    ui->lineEditDate->setText(QString(doc->CreationDate.getValue()));
    ui->lineEditLastMod->setText(QString(doc->LastModifiedBy.getValue()));
    ui->lineEditLastModDate->setText(QString(doc->LastModifiedDate.getValue()));
    ui->lineEditCompany->setText(QString(doc->Company.getValue()));

    QList<QByteArray> rawLicenses; rawLicenses
        << "All rights reserved"
        << "CreativeCommons Attribution"
        << "CreativeCommons Attribution-ShareAlike"
        << "CreativeCommons Attribution-NoDerivatives"
        << "CreativeCommons Attribution-NonCommercial"
        << "CreativeCommons Attribution-NonCommercial-ShareAlike"
        << "CreativeCommons Attribution-NonCommercial-NoDerivatives"
        << "Public Domain"
        << "FreeArt"
        << "Other";
    for (QList<QByteArray>::iterator it = rawLicenses.begin(); it != rawLicenses.end(); ++it) {
        QString text = QApplication::translate("Gui::Dialog::DlgSettingsDocument", it->constData());
        ui->comboLicense->addItem(text, *it);
    }

    int index = ui->comboLicense->findData(QByteArray(doc->License.getValue()));
    if (index >= 0) {
        ui->comboLicense->setCurrentIndex(index);
    }
    else {
        index = ui->comboLicense->count();
        QString text = QString(doc->License.getValue());
        ui->comboLicense->addItem(text);
        ui->comboLicense->setCurrentIndex(index);
    }

    ui->lineEditLicenseURL->setText(QString(doc->LicenseURL.getValue()));

    // When saving the text to XML the newlines get lost. So we store also the newlines as '\n'.
    // See also accept().
    QString comment = QString(doc->Comment.getValue());
    QStringList lines = comment.split(QString("\\n"), QString::KeepEmptyParts);
    QString text = lines.join(QString("\n"));
    ui->textEditComment->setPlainText( text );
    connect(ui->pushButtonOpenURL, SIGNAL(clicked()),this, SLOT(open_url()));
    connect(ui->comboLicense, SIGNAL(currentIndexChanged(int)), this, SLOT(onLicenseTypeChanged(int)));
}

/**
 *  Destroys the object and frees any allocated resources
 */
DlgProjectInformationImp::~DlgProjectInformationImp()
{
    // no need to delete child widgets, Qt does it all for us
    delete ui;
}

/**
 * Applies the changes to the project information of the given document.
 */
void DlgProjectInformationImp::accept()
{
    _doc->CreatedBy.setValue(ui->lineEditCreator->text().toUtf8());
    _doc->LastModifiedBy.setValue(ui->lineEditCreator->text().toUtf8());
    _doc->Company.setValue(ui->lineEditCompany->text().toUtf8());
    QByteArray license = ui->comboLicense->itemData(ui->comboLicense->currentIndex()).toByteArray();
    if (license.isEmpty())
        license = ui->comboLicense->itemText(ui->comboLicense->currentIndex()).toUtf8();
    _doc->License.setValue(license);
    _doc->LicenseURL.setValue(ui->lineEditLicenseURL->text().toUtf8());

    // Replace newline escape sequence through '\\n' string
    QStringList lines = ui->textEditComment->toPlainText().split
        (QString("\n"), QString::KeepEmptyParts);
    QString text = lines.join(QString("\\n"));
    _doc->Comment.setValue(text.isEmpty() ? "" : text.toUtf8());

    QDialog::accept();
}

void DlgProjectInformationImp::onLicenseTypeChanged(int index)
{
    switch (index) {
        case 0:
            ui->lineEditLicenseURL->setText(QString("http://en.wikipedia.org/wiki/All_rights_reserved"));
            break;
        case 1:
            ui->lineEditLicenseURL->setText(QString("http://creativecommons.org/licenses/by/4.0/"));
            break;
        case 2:
            ui->lineEditLicenseURL->setText(QString("http://creativecommons.org/licenses/by-sa/4.0/"));
            break;
        case 3:
            ui->lineEditLicenseURL->setText(QString("http://creativecommons.org/licenses/by-nd/4.0/"));
            break;
        case 4:
            ui->lineEditLicenseURL->setText(QString("http://creativecommons.org/licenses/by-nc/4.0/"));
            break;
        case 5:
            ui->lineEditLicenseURL->setText(QString("http://creativecommons.org/licenses/by-nc-sa/4.0/"));
            break;
        case 6:
            ui->lineEditLicenseURL->setText(QString("http://creativecommons.org/licenses/by-nc-nd/4.0/"));
            break;
        case 7:
            ui->lineEditLicenseURL->setText(QString("http://en.wikipedia.org/wiki/Public_domain"));
            break;
        case 8:
            ui->lineEditLicenseURL->setText(QString("http://artlibre.org/licence/lal"));
            break;
        default:
            ui->lineEditLicenseURL->setText(QString(_doc->LicenseURL.getValue()));
            break;
    }
}

/**
 * Opens the text in the LicenseURL property in external browser.
 */
void DlgProjectInformationImp::open_url()
{
    QString url = ui->lineEditLicenseURL->text();
    QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
}

#include "moc_DlgProjectInformationImp.cpp"
