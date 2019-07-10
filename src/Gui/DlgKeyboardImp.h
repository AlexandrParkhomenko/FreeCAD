/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGKEYBOARD_IMP_H
#define GUI_DIALOG_DLGKEYBOARD_IMP_H

#include "ui_DlgKeyboard.h"
#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

/** Shows an overview of all available commands of all groups and modules.
 * You can customize your workbenches just by drag&dropping any commands
 * onto the toolbars or commandbars. But you cannot modify any standard toolbars or
 * commandbars such as "File, View, ...". It is only possible to
 * customize your own toolbars or commandbars.
 * \author Werner Mayer
 */
class DlgCustomKeyboardImp : public CustomizeActionPage, public Ui_DlgCustomKeyboard
{
    Q_OBJECT;

public:
    DlgCustomKeyboardImp( QWidget* parent = 0 );
    ~DlgCustomKeyboardImp();

protected:
    void showEvent(QShowEvent* e);

protected Q_SLOTS:
    void on_categoryBox_activated(int index);
    void on_commandTreeWidget_currentItemChanged(QTreeWidgetItem*);
    void on_buttonAssign_clicked();
    void on_buttonClear_clicked();
    void on_buttonReset_clicked();
    void on_buttonResetAll_clicked();
    void on_editShortcut_textChanged(const QString&);
    void onAddMacroAction(const QByteArray&);
    void onRemoveMacroAction(const QByteArray&);
    void onModifyMacroAction(const QByteArray&);

protected:
    void changeEvent(QEvent *e);

private:
    bool firstShow;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGKEYBOARD_IMP_H
