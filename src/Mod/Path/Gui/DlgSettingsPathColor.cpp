/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "DlgSettingsPathColor.h"
#include "Gui/PrefWidgets.h"
#include "Base/Console.h"

using namespace PathGui;

/* TRANSLATOR PathGui::DlgSettingsPathColor */

/**
 *  Constructs a DlgSettingsObjectColor which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 */
DlgSettingsPathColor::DlgSettingsPathColor(QWidget* parent)
    : PreferencePage(parent)
{
    this->setupUi(this);
}

/**
 *  Destroys the object and frees any allocated resources
 */
DlgSettingsPathColor::~DlgSettingsPathColor()
{
    // no need to delete child widgets, Qt does it all for us
}

void DlgSettingsPathColor::saveSettings()
{
    // Part
    DefaultNormalPathColor->onSave();
    DefaultRapidPathColor->onSave();
    DefaultPathLineWidth->onSave();
    DefaultPathMarkerColor->onSave();
    DefaultExtentsColor->onSave();
    DefaultProbePathColor->onSave();
    DefaultHighlightPathColor->onSave();
    DefaultBBoxSelectionColor->onSave();
    DefaultBBoxNormalColor->onSave();
	DefaultSelectionStyle->onSave();
    DefaultTaskPanelLayout->onSave();
}

void DlgSettingsPathColor::loadSettings()
{
    // Part
    DefaultNormalPathColor->onRestore();
    DefaultRapidPathColor->onRestore();
    DefaultPathLineWidth->onRestore();
    DefaultPathMarkerColor->onRestore();
    DefaultExtentsColor->onRestore();
    DefaultProbePathColor->onRestore();
    DefaultHighlightPathColor->onRestore();
    DefaultBBoxSelectionColor->onRestore();
    DefaultBBoxNormalColor->onRestore();
	DefaultSelectionStyle->onRestore();
    DefaultTaskPanelLayout->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsPathColor::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsPathColor.cpp"

