/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "DlgSettingsMeshView.h"
#include "Gui/PrefWidgets.h"

using namespace MeshGui;

/**
 *  Constructs a DlgSettingsMeshView which is a child of 'parent'.
 */
DlgSettingsMeshView::DlgSettingsMeshView(QWidget* parent)
  : PreferencePage(parent)
{
    this->setupUi(this);
    labelBackfaceColor->hide();
    buttonBackfaceColor->hide();
}

/** 
 *  Destroys the object and frees any allocated resources
 */
DlgSettingsMeshView::~DlgSettingsMeshView()
{
    // no need to delete child widgets, Qt does it all for us
}

void DlgSettingsMeshView::saveSettings()
{
    checkboxRendering->onSave();
    checkboxBoundbox->onSave();
    buttonMeshColor->onSave();
    buttonLineColor->onSave();
    buttonBackfaceColor->onSave();
    spinMeshTransparency->onSave();
    spinLineTransparency->onSave();
    checkboxNormal->onSave();
    spinboxAngle->onSave();
}

void DlgSettingsMeshView::loadSettings()
{
    Base::Reference<ParameterGrp> hGrp = Gui::WindowParameter::getDefaultParameter();
    hGrp = hGrp->GetGroup("View");
    if (!hGrp->GetBool("EnablePreselection",true) &&
        !hGrp->GetBool("EnableSelection",true))
        checkboxBoundbox->setDisabled(true);
    checkboxRendering->onRestore();
    checkboxBoundbox->onRestore();
    buttonMeshColor->onRestore();
    buttonLineColor->onRestore();
    buttonBackfaceColor->onRestore();
    spinMeshTransparency->onRestore();
    spinLineTransparency->onRestore();
    checkboxNormal->onRestore();
    spinboxAngle->onRestore();
}

/**
 * Sets the strings of the subwidgets using the current language.
 */
void DlgSettingsMeshView::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        retranslateUi(this);
    }
    else {
        QWidget::changeEvent(e);
    }
}

#include "moc_DlgSettingsMeshView.cpp"
