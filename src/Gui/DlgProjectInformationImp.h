/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGPROJECTINFORMATIONIMP_H
#define GUI_DIALOG_DLGPROJECTINFORMATIONIMP_H

#include <QDialog>

namespace App {
class Document;
}

namespace Gui {

namespace Dialog {

class Ui_DlgProjectInformation;
class DlgProjectInformationImp : public QDialog
{
    Q_OBJECT

public:
    DlgProjectInformationImp(App::Document* doc, QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgProjectInformationImp();
    void accept();

private Q_SLOTS:
    void open_url();
    void onLicenseTypeChanged(int index);

private:
    App::Document* _doc;
    Ui_DlgProjectInformation* ui;
};

} // namespace Dialog
} // namespace Gui


#endif // GUI_DIALOG_DLGPROJECTINFORMATIONIMP_H

