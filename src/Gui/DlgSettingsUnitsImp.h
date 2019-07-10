/***************************************************************************
 *   Copyright (c) 2010 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGSETTINGSUnitsIMP_H
#define GUI_DIALOG_DLGSETTINGSUnitsIMP_H

#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

/**
 * The DlgSettingsUnitsImp class implements a preference page to change settings
 * for the Unit system.
 * \author Jürgen Riegel
 */
class Ui_DlgSettingsUnits;
class DlgSettingsUnitsImp : public PreferencePage
{
    Q_OBJECT

public:
    DlgSettingsUnitsImp(QWidget* parent = 0);
    ~DlgSettingsUnitsImp();

    void saveSettings();
    void loadSettings();

protected:
    void changeEvent(QEvent *e);

public Q_SLOTS:
    void on_comboBox_ViewSystem_currentIndexChanged(int index);

private:
    Ui_DlgSettingsUnits* ui;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGSETTINGS3DVIEWIMP_H
