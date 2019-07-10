/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <QMessageBox>

#include "Application.h"
#include "MainWindow.h"
#include "DlgEditFileIncludeProptertyExternal.h"
#include "FileDialog.h"


using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgEditFileIncludePropertyExternal */

/**
 *  Constructs a DlgEditFileIncludePropertyExternal which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgEditFileIncludePropertyExternal::
DlgEditFileIncludePropertyExternal(App::PropertyFileIncluded& Prop,
                                   QWidget* parent, Qt::WindowFlags fl)
    : DlgRunExternal(parent, fl), Prop(Prop)
{

}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgEditFileIncludePropertyExternal::~DlgEditFileIncludePropertyExternal()
{
    // no need to delete child widgets, Qt does it all for us
}


int DlgEditFileIncludePropertyExternal::Do(void)
{
    QFileInfo file = QString::fromUtf8(Prop.getValue());
    assert(file.exists());

    QDir tmp = QString::fromUtf8(App::Application::getTempPath().c_str());
    QString TempFile = tmp.absoluteFilePath(file.fileName());
    QFile::remove(TempFile);

    QFile::copy(file.absoluteFilePath(),TempFile);

    arguments.append(TempFile);

    int ret = DlgRunExternal::Do();

    if (ret == QDialog::Accepted)
        Prop.setValue(TempFile.toUtf8());

    QFile::remove(TempFile);
    return ret;
}

#include "moc_DlgEditFileIncludeProptertyExternal.cpp"

