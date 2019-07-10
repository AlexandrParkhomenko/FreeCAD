/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "DlgSettingsObjectColor.h"
#include "Gui/PrefWidgets.h"

using namespace PartGui;

/* TRANSLATOR PartGui::DlgSettingsObjectColor */

/**
 *  Constructs a DlgSettingsObjectColor which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
DlgSettingsObjectColor::DlgSettingsObjectColor(QWidget* parent)
    : PreferencePage(parent)
{
    this->setupUi(this);
    this->DefaultShapeColor->setDisabled(this->checkRandomColor->isChecked());
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgSettingsObjectColor::~DlgSettingsObjectColor()
{
    // no need to delete child widgets, Qt does it all for us
}

void DlgSettingsObjectColor::saveSettings()
{
    // Part
    DefaultShapeColor->onSave();
    checkRandomColor->onSave();
    DefaultShapeLineColor->onSave();
    DefaultShapeLineWidth->onSave();
    DefaultShapeVertexColor->onSave();
    DefaultShapeVertexWidth->onSave();
    BoundingBoxColor->onSave();
    // Annotations
    AnnotationTextColor->onSave();
}

void DlgSettingsObjectColor::loadSettings()
{
    // Part
    DefaultShapeColor->onRestore();
    checkRandomColor->onRestore();
    DefaultShapeLineColor->onRestore();
    DefaultShapeLineWidth->onRestore();
    DefaultShapeVertexColor->onRestore();
    DefaultShapeVertexWidth->onRestore();
    BoundingBoxColor->onRestore();
    // Annotations
    AnnotationTextColor->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsObjectColor::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsObjectColor.cpp"

