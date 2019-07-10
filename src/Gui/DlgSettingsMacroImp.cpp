/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "DlgSettingsMacroImp.h"
#include "Application.h"

using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgSettingsMacroImp */

/**
 *  Constructs a DlgSettingsMacroImp which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
DlgSettingsMacroImp::DlgSettingsMacroImp( QWidget* parent )
  : PreferencePage( parent )
{
    this->setupUi(this);

    // Was never implemented, so hide it
    this->FileLogCheckBox->hide();
    this->MacroPath_2->hide();

    if (MacroPath->fileName().isEmpty()) {
        QDir d(QString::fromUtf8(App::GetApplication().getUserMacroDir().c_str()));
        MacroPath->setFileName(d.path());
    }
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgSettingsMacroImp::~DlgSettingsMacroImp()
{
    // no need to delete child widgets, Qt does it all for us
}

void DlgSettingsMacroImp::saveSettings()
{
    PrefCheckBox_LocalEnv->onSave();
    MacroPath->onSave();
    PrefCheckBox_RecordGui->onSave();
    PrefCheckBox_GuiAsComment->onSave();
    PConsoleCheckBox->onSave();
    FileLogCheckBox->onSave();
    MacroPath_2->onSave();
}

void DlgSettingsMacroImp::loadSettings()
{
    PrefCheckBox_LocalEnv->onRestore();
    MacroPath->onRestore();
    PrefCheckBox_RecordGui->onRestore();
    PrefCheckBox_GuiAsComment->onRestore();
    PConsoleCheckBox->onRestore();
    FileLogCheckBox->onRestore();
    MacroPath_2->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsMacroImp::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsMacroImp.cpp"
