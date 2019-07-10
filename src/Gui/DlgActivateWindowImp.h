/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGACTIVATEWINDOW_IMP_H
#define GUI_DIALOG_DLGACTIVATEWINDOW_IMP_H

#include <QDialog>

namespace Gui {
namespace Dialog {
class Ui_DlgActivateWindow;
/**
 * The DlgActivateWindowImp class provides a dialog to activate the MDI window
 * of the main window you wish. Since there could be a lot of MDI windows in
 * an application you cannot put all of them into the "Windows" popup menu.
 * \author Werner Mayer
 */
class DlgActivateWindowImp : public QDialog
{
    Q_OBJECT

public:
    DlgActivateWindowImp(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgActivateWindowImp();

protected:
    void accept();

private:
    Ui_DlgActivateWindow* ui;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGACTIVATEWINDOW_IMP_H
