/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGSETTINGS3DVIEWIMP_H
#define GUI_DIALOG_DLGSETTINGS3DVIEWIMP_H

#include "ui_DlgSettings3DView.h"
#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

/**
 * The DlgSettings3DViewImp class implements a preference page to change settings
 * for the Inventor viewer.
 * \author Jürgen Riegel
 */
class DlgSettings3DViewImp : public PreferencePage, public Ui_DlgSettings3DView
{
    Q_OBJECT

public:
    DlgSettings3DViewImp(QWidget* parent = 0);
    ~DlgSettings3DViewImp();

    void saveSettings();
    void loadSettings();

private Q_SLOTS:
    void on_mouseButton_clicked();
    void onAliasingChanged(int);
    void onNewDocViewChanged(int);

protected:
    void changeEvent(QEvent *e);
    void retranslate();

private:
    static bool showMsg;
    double q0, q1, q2, q3;
};

class CameraDialog : public QDialog
{
    Q_OBJECT

public:
    CameraDialog(QWidget* parent=0);
    ~CameraDialog();
    void setValues(double q0, double q1, double q2, double q3);
    void getValues(double& q0, double& q1, double& q2, double& q3) const;


private Q_SLOTS:
    void on_currentView_clicked();

private:
    QDoubleSpinBox* sb0;
    QDoubleSpinBox* sb1;
    QDoubleSpinBox* sb2;
    QDoubleSpinBox* sb3;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGSETTINGS3DVIEWIMP_H
