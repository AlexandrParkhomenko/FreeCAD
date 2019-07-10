/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_DLGSETTINGSGENERAL_H
#define PARTGUI_DLGSETTINGSGENERAL_H

#include "Gui/PropertyPage.h"

class QButtonGroup;

namespace PartGui {

class Ui_DlgSettingsGeneral;
class DlgSettingsGeneral : public Gui::Dialog::PreferencePage
{
    Q_OBJECT

public:
    DlgSettingsGeneral(QWidget* parent = 0);
    ~DlgSettingsGeneral();

protected:
    void saveSettings();
    void loadSettings();
    void changeEvent(QEvent *e);

private:
    Ui_DlgSettingsGeneral* ui;
};

class Ui_DlgImportExportIges;
class DlgImportExportIges : public Gui::Dialog::PreferencePage
{
    Q_OBJECT

public:
    DlgImportExportIges(QWidget* parent = 0);
    ~DlgImportExportIges();

protected:
    void saveSettings();
    void loadSettings();
    void changeEvent(QEvent *e);

private:
    Ui_DlgImportExportIges* ui;
    QButtonGroup* bg;
};

class Ui_DlgImportExportStep;
class DlgImportExportStep : public Gui::Dialog::PreferencePage
{
    Q_OBJECT

public:
    DlgImportExportStep(QWidget* parent = 0);
    ~DlgImportExportStep();

protected:
    void saveSettings();
    void loadSettings();
    void changeEvent(QEvent *e);

private:
    Ui_DlgImportExportStep* ui;
};

} // namespace Gui

#endif // PARTGUI_DLGSETTINGSGENERAL_H
