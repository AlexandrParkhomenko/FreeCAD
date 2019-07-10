/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGMACRORECORDIMP_H
#define GUI_DIALOG_DLGMACRORECORDIMP_H

#include "ui_DlgMacroRecord.h"
#include "Window.h"


namespace Gui {
class MacroManager;
namespace Dialog {

/**
 * The DlgMacroRecordImp class implements a dialog to record a macro.
 * \author Jürgen Riegel
 */
class DlgMacroRecordImp : public QDialog, public Ui_DlgMacroRecord, public Gui::WindowParameter
{ 
    Q_OBJECT

public:
    DlgMacroRecordImp( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    virtual ~DlgMacroRecordImp();

protected Q_SLOTS:
    void on_buttonStart_clicked();
    void on_buttonStop_clicked();
    void on_buttonCancel_clicked();
    void on_pushButtonChooseDir_clicked();
    void on_lineEditMacroPath_textChanged ( const QString & );

protected:
    /// conviniance pointer
    MacroManager* macroManager; 
    QString macroPath; // Macro file to save in
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGMACRORECORDIMP_H
