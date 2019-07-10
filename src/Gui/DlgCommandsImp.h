/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGCOMMANDS_IMP_H
#define GUI_DIALOG_DLGCOMMANDS_IMP_H

#include "ui_DlgCommands.h"
#include "PropertyPage.h"

namespace Gui {
class Command;
namespace Dialog {

/** Shows an overview of all available commands of all groups and modules.
 * You can customize your workbenches just by drag&dropping any commands
 * onto the toolbars or commandbars. But you cannot modify any standard toolbars or
 * commandbars such as "File, View, ...". It is only poosible to
 * customize your own toolbars or commandbars.
 * \author Werner Mayer
 */
class DlgCustomCommandsImp : public CustomizeActionPage, public Ui_DlgCustomCommands
{
  Q_OBJECT

public:
    DlgCustomCommandsImp(QWidget* parent = 0);
    ~DlgCustomCommandsImp();

protected Q_SLOTS:
    void onGroupActivated(QTreeWidgetItem *i);
    void onDescription(QTreeWidgetItem *i);
    void onAddMacroAction(const QByteArray&);
    void onRemoveMacroAction(const QByteArray&);
    void onModifyMacroAction(const QByteArray&);

protected:
    void changeEvent(QEvent *e);
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGCOMMANDS_IMP_H
