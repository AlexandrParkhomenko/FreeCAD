/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QMessageBox>

#include "DlgReportViewImp.h"
#include "PrefWidgets.h"


using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgReportViewImp */

/**
 *  Constructs a DlgReportViewImp which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgReportViewImp::DlgReportViewImp( QWidget* parent )
  : PreferencePage(parent)
{
    this->setupUi(this);
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgReportViewImp::~DlgReportViewImp()
{
}

void DlgReportViewImp::saveSettings()
{
    checkLogging->onSave();
    checkWarning->onSave();
    checkError->onSave();
    colorText->onSave();
    colorLogging->onSave();
    colorWarning->onSave();
    colorError->onSave();
    pythonOutput->onSave();
    pythonError->onSave();
}

void DlgReportViewImp::loadSettings()
{
    checkLogging->onRestore();
    checkWarning->onRestore();
    checkError->onRestore();
    colorText->onRestore();
    colorLogging->onRestore();
    colorWarning->onRestore();
    colorError->onRestore();
    pythonOutput->blockSignals(true);
    pythonOutput->onRestore();
    pythonOutput->blockSignals(false);
    pythonError->blockSignals(true);
    pythonError->onRestore();
    pythonError->blockSignals(false);
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgReportViewImp::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgReportViewImp.cpp"
