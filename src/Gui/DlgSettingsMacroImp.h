/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGSETTINGSMACROIMP_H
#define GUI_DIALOG_DLGSETTINGSMACROIMP_H

#include "ui_DlgSettingsMacro.h"
#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

/**
 * The DlgSettingsMacroImp class implements a preference page to change settings
 * for macro stuff.
 * \author Jürgen Riegel
 */
class DlgSettingsMacroImp : public PreferencePage, public Ui_DlgSettingsMacro
{
    Q_OBJECT

public:
    DlgSettingsMacroImp( QWidget* parent = 0 );
    ~DlgSettingsMacroImp();

    void saveSettings();
    void loadSettings();

protected:
    void changeEvent(QEvent *e);
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGSETTINGSMACROIMP_H
