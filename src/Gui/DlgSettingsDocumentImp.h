/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGSETTINGSDOCUMENT_IMP_H
#define GUI_DIALOG_DLGSETTINGSDOCUMENT_IMP_H

#include "ui_DlgSettingsDocument.h"
#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

/**
 * The DlgSettingsDocumentImp class implements a preference page to change settings
 * for the document.
 * \author Jürgen Riegel
 */
class DlgSettingsDocumentImp : public PreferencePage, public Ui_DlgSettingsDocument
{
    Q_OBJECT

public:
    DlgSettingsDocumentImp( QWidget* parent = 0 );
    ~DlgSettingsDocumentImp();

    void saveSettings();
    void loadSettings();

protected Q_SLOTS:
    void onLicenseTypeChanged(int index);

protected:
    void changeEvent(QEvent *e);
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGSETTINGSDOCUMENT_IMP_H
