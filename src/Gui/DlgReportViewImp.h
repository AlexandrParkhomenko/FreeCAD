/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLG_REPORT_VIEW_IMP
#define GUI_DIALOG_DLG_REPORT_VIEW_IMP

#include "ui_DlgReportView.h"
#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

/** The DlgReportViewImp class implements the available settings for the 
 * report output window to change.
 * \author Werner Mayer
 */
class DlgReportViewImp : public PreferencePage, public Ui_DlgReportView
{
    Q_OBJECT

public:
    DlgReportViewImp( QWidget* parent = 0 );
    ~DlgReportViewImp();

    void saveSettings();
    void loadSettings();

protected:
    void changeEvent(QEvent *e);
};

} // namespace Dialog
} // namespace Gui

#endif //GUI_DIALOG_DLG_REPORT_VIEW_IMP
