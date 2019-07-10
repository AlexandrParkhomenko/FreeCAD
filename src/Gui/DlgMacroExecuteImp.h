/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGMACROEXECUTEIMP_H
#define GUI_DIALOG_DLGMACROEXECUTEIMP_H

#include "ui_DlgMacroExecute.h"
#include "Window.h"

namespace Gui {
namespace Dialog {

/**
 * The DlgMacroExecuteImp class implements a dialog to execute or edit a
 * recorded macro. 
 * \author Jürgen Riegel
 */
class DlgMacroExecuteImp : public QDialog, public Ui_DlgMacroExecute, public Gui::WindowParameter
{ 
    Q_OBJECT

public:
    DlgMacroExecuteImp( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~DlgMacroExecuteImp();

    void accept();

public Q_SLOTS:
    void on_fileChooser_fileNameChanged(const QString&);
    void on_createButton_clicked();
    void on_deleteButton_clicked();
    void on_editButton_clicked();
    void on_renameButton_clicked();
    void on_duplicateButton_clicked();
    void on_addonsButton_clicked();

protected Q_SLOTS:
    void on_userMacroListBox_currentItemChanged(QTreeWidgetItem*);
    void on_systemMacroListBox_currentItemChanged(QTreeWidgetItem*);
    void on_tabMacroWidget_currentChanged(int index);

protected:
    void fillUpList(void);

protected:
    QString macroPath;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGMACROEXECUTEIMP_H
