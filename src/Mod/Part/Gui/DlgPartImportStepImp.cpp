/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <qlineedit.h>

#include "Gui/FileDialog.h"
#include "Gui/MainWindow.h"
#include "DlgPartImportStepImp.h"

using namespace PartGui;

/* TRANSLATOR PartGui::DlgPartImportStepImp */

/* 
 *  Constructs a DlgPartImportStep which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgPartImportStepImp::DlgPartImportStepImp( QWidget* parent, Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
    this->setupUi(this);
}

/*  
 *  Destroys the object and frees any allocated resources
 */
DlgPartImportStepImp::~DlgPartImportStepImp()
{
    // no need to delete child widgets, Qt does it all for us
}

/* 
 * public slot
 */
void DlgPartImportStepImp::OnApply()
{
    qWarning( "DlgPartImportStepImp::OnApply() not yet implemented!" ); 
}

void DlgPartImportStepImp::onChooseFileName()
{
    QString fn = Gui::FileDialog::getOpenFileName(Gui::getMainWindow(), QString::null, QString::null,
        QString::fromLatin1("%1 (*.stp *.step);;%2 (*.*)"))
        .arg(tr("STEP"),
             tr("All Files"));
    if (!fn.isEmpty()) {
        FileName->setText(fn);
    }
}


#include "moc_DlgPartImportStepImp.cpp"
