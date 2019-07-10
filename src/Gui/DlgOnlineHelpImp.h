/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGONLINEHELP_IMP_H
#define GUI_DIALOG_DLGONLINEHELP_IMP_H

#include "ui_DlgOnlineHelp.h"
#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

/** This class implements the dialog for downloading the online documentation.
 * Moreover it allows to specify location of the start page an an external browser.
 * Here you can specify to use a proxy if necessary and some more stuff.
 * \author Werner Mayer
 */
class DlgOnlineHelpImp : public PreferencePage, public Ui_DlgOnlineHelp
{
    Q_OBJECT

public:
    DlgOnlineHelpImp( QWidget* parent = 0 );
    ~DlgOnlineHelpImp();

    static QString getStartpage();

    void saveSettings();
    void loadSettings();

protected:
    void changeEvent(QEvent *e);

protected:
    void on_lineEditDownload_fileNameSelected(const QString&);
};

} // namespace Dialog
} // namespace Gui

#endif //GUI_DIALOG_DLGONLINEHELP_IMP_H
