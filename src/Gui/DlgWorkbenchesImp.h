/***************************************************************************
 *   Copyright (c) 2015 FreeCAD Developers                                 *
 *   Author: Przemo Firszt <przemo@firszt.eu>                              *
 *   Based on DlgToolbars.h file                                           *
 *                                                                         *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGWORKBENCHES_IMP_H
#define GUI_DIALOG_DLGWORKBENCHES_IMP_H

#include "ui_DlgWorkbenches.h"
#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

class DlgWorkbenchesImp : public CustomizeActionPage, public Ui_DlgWorkbenches
{
    Q_OBJECT

public:
    DlgWorkbenchesImp(QWidget* parent = 0);
    ~DlgWorkbenchesImp();
    static QStringList load_enabled_workbenches();
    static QStringList load_disabled_workbenches();
    static const QString all_workbenches;

protected:
    void changeEvent(QEvent *e);
    void hideEvent(QHideEvent * event);

protected Q_SLOTS:
    void onAddMacroAction(const QByteArray&);
    void onRemoveMacroAction(const QByteArray&);
    void onModifyMacroAction(const QByteArray&);
    void on_add_to_enabled_workbenches_btn_clicked();
    void on_remove_from_enabled_workbenches_btn_clicked();
    void on_shift_workbench_up_btn_clicked();
    void on_shift_workbench_down_btn_clicked();
    void on_sort_enabled_workbenches_btn_clicked();
    void on_add_all_to_enabled_workbenches_btn_clicked();

private:
    void set_lw_properties(QListWidgetCustom *lw);
    void add_workbench(QListWidgetCustom *lw, const QString& it);
    void move_workbench(QListWidgetCustom *lwc_dest,
                        QListWidgetItem *wi);
    void save_workbenches();
    void shift_workbench(bool up);
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGWORKBENCHES_IMP_H
