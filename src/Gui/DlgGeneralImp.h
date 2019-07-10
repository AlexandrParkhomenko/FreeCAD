/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGGENERALIMP_H
#define GUI_DIALOG_DLGGENERALIMP_H

#include "PropertyPage.h"
#include <memory>

class QTabWidget;

namespace Gui {
namespace Dialog {
class Ui_DlgGeneral;

/** This class implements the settings for the application.
 *  You can change window style, size of pixmaps, size of recent file list and so on
 *  \author Werner Mayer
 */
class DlgGeneralImp : public PreferencePage
{
    Q_OBJECT

public:
    DlgGeneralImp( QWidget* parent = 0 );
    ~DlgGeneralImp();

    void saveSettings();
    void loadSettings();

protected:
    void changeEvent(QEvent *e);

private:
    void setRecentFileSize();

private:
    std::unique_ptr<Ui_DlgGeneral> ui;
    QString selectedStyleSheet;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGGENERALIMP_H
