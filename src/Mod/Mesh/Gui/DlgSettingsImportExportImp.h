/***************************************************************************
 *   Copyright (c) 2016 Ian Rees         <ian.rees@gmail.com>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESHGUI_DLGSETTINGSIMPORTEXPORTIMP_H
#define MESHGUI_DLGSETTINGSIMPORTEXPORTIMP_H

#include "Gui/PropertyPage.h"

namespace MeshGui {

class Ui_DlgSettingsImportExport;
/**
 * The DlgSettingsImportExportImp class implements a preference page to change settings
 * for Importing and Exporting mesh objects.
 */
class DlgSettingsImportExport : public Gui::Dialog::PreferencePage
{
    Q_OBJECT

public:
    DlgSettingsImportExport(QWidget* parent = 0);
    ~DlgSettingsImportExport();

protected:
    void saveSettings();
    void loadSettings();
    void changeEvent(QEvent *e);

private:
    Ui_DlgSettingsImportExport* ui;
};  // end class DlgSettingsImportExport

} // namespace MeshGui

#endif // MESHGUI_DLGSETTINGSIMPORTEXPORTIMP_H

