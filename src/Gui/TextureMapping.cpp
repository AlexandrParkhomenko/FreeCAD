/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <Inventor/nodes/SoGroup.h>
# include <Inventor/nodes/SoTexture2.h>
# include <QImage>
# include <QMessageBox>
# include <QImageReader>
# include <QKeyEvent>

#include <Inventor/nodes/SoTextureCoordinateEnvironment.h>
#include <QDialogButtonBox>

#include "App/Application.h"

#include "TextureMapping.h"
#include "BitmapFactory.h"
#include "ui_TextureMapping.h"
#include "Application.h"
#include "Document.h"
#include "View3DInventor.h"
#include "View3DInventorViewer.h"

using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::TextureMapping */

TextureMapping::TextureMapping(QWidget* parent, Qt::WindowFlags fl)
  : QDialog(parent, fl), grp(0), tex(0), env(0)
{
    ui = new Ui_TextureMapping();
    ui->setupUi(this);
    ui->checkGlobal->hide();

    // set a dummy string which is not a valid file name
    fileName = QLatin1String("<>");

    // add all supported QImage formats
    QStringList formats;
    QList<QByteArray> qtformats = QImageReader::supportedImageFormats();
    for (QList<QByteArray>::Iterator it = qtformats.begin(); it != qtformats.end(); ++it) {
        formats << QString::fromLatin1("*.%1").arg(QLatin1String(*it));
    }
    
    ui->fileChooser->setFilter(tr("Image files (%1)").arg(formats.join(QLatin1String(" "))));

    this->tex = new SoTexture2();
    this->tex->ref();
    this->env = new SoTextureCoordinateEnvironment();
    this->env->ref();

    std::string path = App::GetApplication().Config()["TextureImage"];
    if (!path.empty()) {
        QString file = QString::fromUtf8(path.c_str());
        ui->fileChooser->setFileName(file);
        on_fileChooser_fileNameSelected(file);
    }
}

TextureMapping::~TextureMapping()
{
    this->tex->unref();
    this->env->unref();
    delete ui;
}

void TextureMapping::accept()
{
    QDialog::accept();
}

void TextureMapping::reject()
{
    if (this->grp) {
        this->grp->removeChild(this->tex);
        if (this->grp->findChild(this->env) > -1)
            this->grp->removeChild(this->env);
        this->grp->unref();
    }

    QDialog::reject();
}

void TextureMapping::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    else {
        QDialog::changeEvent(e);
    }
}

void TextureMapping::keyPressEvent(QKeyEvent *e)
{
    // The texture mapping dialog is embedded into a task panel
    // which is a parent widget and will handle the event
    e->ignore();
}

void TextureMapping::on_fileChooser_fileNameSelected(const QString& s)
{
    QImage image;
    if (!image.load(s)) {
        // This slot is always invoked when leaving the focus of the line edit
        // and to avoid to run into an infinite loop of popping up the dialog
        // there is a check to report the last selected file name (which might
        // be an empty string) only once.
        if (fileName != s) {
            QMessageBox::warning(this, tr("No image"), tr("The specified file is not a valid image file."));
            fileName = s;
        }
        return;
    }

    if (!this->grp) {
        Gui::Document* doc = Gui::Application::Instance->activeDocument();
        if (doc) {
            Gui::MDIView* mdi = doc->getActiveView();
            if (mdi && mdi->isDerivedFrom(View3DInventor::getClassTypeId())) {
                Gui::View3DInventorViewer* view = static_cast<View3DInventor*>(mdi)->getViewer();
                this->grp = static_cast<SoGroup *>(view->getSceneGraph());
                this->grp->ref();
                this->grp->insertChild(this->tex,1);
                if (ui->checkEnv->isChecked())
                    this->grp->insertChild(this->env,2);
            }
        }
    }

    if (!this->grp) {
        QMessageBox::warning(this, tr("No 3d view"), tr("No active 3d view found."));
        return;
    }

    SoSFImage texture;
    Gui::BitmapFactory().convert(image, texture);
    this->tex->image = texture;
    //this->tex->filename = (const char*)s.toUtf8();
    App::GetApplication().Config()["TextureImage"] = (const char*)s.toUtf8();
}

void TextureMapping::on_checkEnv_toggled(bool b)
{
    if (!this->grp)
        return;
    if (b) {
        this->grp->insertChild(this->env,2);
    }
    else {
        this->grp->removeChild(this->env);
    }
}

// ---------------------------------------

TaskTextureMapping::TaskTextureMapping()
{
    dialog = new TextureMapping();
    taskbox = new Gui::TaskView::TaskBox(QPixmap(), dialog->windowTitle(), true, 0);
    taskbox->groupLayout()->addWidget(dialog);
    Content.push_back(taskbox);
}

TaskTextureMapping::~TaskTextureMapping()
{
    // automatically deleted in the sub-class
}

bool TaskTextureMapping::accept()
{
    dialog->accept();
    return (dialog->result() == QDialog::Accepted);
}

bool TaskTextureMapping::reject()
{
    dialog->reject();
    return (dialog->result() == QDialog::Rejected);
}

#include "moc_TextureMapping.cpp"
