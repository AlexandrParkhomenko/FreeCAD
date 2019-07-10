/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESHGUI_DLGSETTINGSMESHVIEW_H
#define MESHGUI_DLGSETTINGSMESHVIEW_H

#include "ui_DlgSettingsMeshView.h"
#include "Gui/PropertyPage.h"

namespace MeshGui {

/**
 * The DlgSettingsMeshView class implements a preference page to change settings
 * for display of meshes.
 * @author Werner Mayer
 */
class DlgSettingsMeshView : public Gui::Dialog::PreferencePage, public Ui_DlgSettingsMeshView
{ 
    Q_OBJECT

public:
    DlgSettingsMeshView(QWidget* parent = 0);
    ~DlgSettingsMeshView();

protected:
    void saveSettings();
    void loadSettings();
    void changeEvent(QEvent *e);
};

} // namespace Gui

#endif // MESHGUI_DLGSETTINGSMESHVIEW_H
