/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "DlgSettingsViewColor.h"
#include "PrefWidgets.h"

using namespace Gui::Dialog;

/* TRANSLATOR Gui::Dialog::DlgSettingsViewColor */

/**
 *  Constructs a DlgSettingsViewColor which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
DlgSettingsViewColor::DlgSettingsViewColor(QWidget* parent)
    : PreferencePage(parent)
{
    this->setupUi(this);
    this->HighlightColor->setEnabled(this->checkBoxPreselection->isChecked());
    this->SelectionColor->setEnabled(this->checkBoxSelection->isChecked());
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgSettingsViewColor::~DlgSettingsViewColor()
{
    // no need to delete child widgets, Qt does it all for us
}

void DlgSettingsViewColor::saveSettings()
{
    SelectionColor_Background->onSave();
    backgroundColorFrom->onSave();
    backgroundColorTo->onSave();
    backgroundColorMid->onSave();
    radioButtonSimple->onSave();
    radioButtonGradient->onSave();
    checkMidColor->onSave();
    checkBoxPreselection->onSave();
    checkBoxSelection->onSave();
    HighlightColor->onSave();
    SelectionColor->onSave();
    spinPickRadius->onSave();
    TreeEditColor->onSave();
    TreeActiveColor->onSave();
}

void DlgSettingsViewColor::loadSettings()
{
    SelectionColor_Background->onRestore();
    backgroundColorFrom->onRestore();
    backgroundColorTo->onRestore();
    backgroundColorMid->onRestore();
    radioButtonSimple->onRestore();
    radioButtonGradient->onRestore();
    checkMidColor->onRestore();
    checkBoxPreselection->onRestore();
    checkBoxSelection->onRestore();
    HighlightColor->onRestore();
    SelectionColor->onRestore();
    spinPickRadius->onRestore();
    TreeEditColor->onRestore();
    TreeActiveColor->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsViewColor::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsViewColor.cpp"

