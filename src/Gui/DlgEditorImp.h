/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGEDITORSETTINGSIMP_H
#define GUI_DIALOG_DLGEDITORSETTINGSIMP_H

#include "ui_DlgEditor.h"
#include "PropertyPage.h"

namespace Gui {
class PythonSyntaxHighlighter;

namespace Dialog {

/** This class implements a preferences page for the editor settings.
 *  Here you can change different color settings and font for editors.
 *  @author Werner Mayer
 */
struct DlgSettingsEditorP;
class DlgSettingsEditorImp : public PreferencePage, public Ui_DlgEditorSettings
{
    Q_OBJECT

public:
    DlgSettingsEditorImp( QWidget* parent = 0 );
    ~DlgSettingsEditorImp();

public:
    void saveSettings();
    void loadSettings();

protected Q_SLOTS:
    void on_displayItems_currentItemChanged(QTreeWidgetItem *i);
    void on_colorButton_changed();
    void on_fontFamily_activated(const QString&);
    void on_fontSize_valueChanged(const QString&);

protected:
    void changeEvent(QEvent *e);

private:
    DlgSettingsEditorP* d;
    Gui::PythonSyntaxHighlighter* pythonSyntax;

    DlgSettingsEditorImp( const DlgSettingsEditorImp & );
    DlgSettingsEditorImp& operator=( const DlgSettingsEditorImp & );
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGEDITORSETTINGSIMP_H
