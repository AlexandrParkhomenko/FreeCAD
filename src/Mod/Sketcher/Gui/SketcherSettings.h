/***************************************************************************
 *   Copyright (c) 2014 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef SKETCHERGUI_SKETCHERSETTINGS_H
#define SKETCHERGUI_SKETCHERSETTINGS_H

#include "Gui/PropertyPage.h"

namespace SketcherGui {
class Ui_SketcherSettings;
class Ui_SketcherSettingsColors;
class SketcherGeneralWidget;
/**
 * The SketcherSettings class implements a preference page to change sketcher settings.
 * @author Werner Mayer
 */
class SketcherSettings : public Gui::Dialog::PreferencePage
{
    Q_OBJECT

public:
    SketcherSettings(QWidget* parent = 0);
    ~SketcherSettings();

    void saveSettings();
    void loadSettings();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
    void onBtnTVApplyClicked(bool);

private:
    Ui_SketcherSettings* ui;
    SketcherGeneralWidget* form;
};

/**
 * The SketcherSettings class implements a preference page to change sketcher settings.
 * @author Werner Mayer
 */
class SketcherSettingsColors : public Gui::Dialog::PreferencePage
{
    Q_OBJECT

public:
    SketcherSettingsColors(QWidget* parent = 0);
    ~SketcherSettingsColors();

    void saveSettings();
    void loadSettings();

protected:
    void changeEvent(QEvent *e);

private:
    Ui_SketcherSettingsColors* ui;
};

} // namespace SketcherGui

#endif // SKETCHERGUI_SKETCHERSETTINGS_H
