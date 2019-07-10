/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGPROJECTUTILITY_H
#define GUI_DIALOG_DLGPROJECTUTILITY_H

#include <QDialog>
#include <string>

namespace Gui { namespace Dialog {

class Ui_DlgProjectUtility;
class DlgProjectUtility : public QDialog
{
    Q_OBJECT

public:
    DlgProjectUtility(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgProjectUtility();

private Q_SLOTS:
    void on_extractButton_clicked();
    void on_createButton_clicked();

protected:
    static std::string doctools;
    Ui_DlgProjectUtility* ui;
};

} // namespace Dialog
} // namespace Gui


#endif // GUI_DIALOG_DLGPROJECTUTILITY_H

