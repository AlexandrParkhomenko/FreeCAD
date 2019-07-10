/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_DIALOG_DLGSETTINGSOBJECTCOLOR_H
#define PARTGUI_DIALOG_DLGSETTINGSOBJECTCOLOR_H

#include "ui_DlgSettingsObjectColor.h"
#include "Gui/PropertyPage.h"

namespace PartGui {

/**
 * The DlgSettingsObjectColor class implements a preference page to change color settings
 * for data objects.
 * @author Werner Mayer
 */
class DlgSettingsObjectColor : public Gui::Dialog::PreferencePage, public Ui_DlgSettingsObjectColor
{ 
  Q_OBJECT

public:
  DlgSettingsObjectColor(QWidget* parent = 0);
  ~DlgSettingsObjectColor();

  void saveSettings();
  void loadSettings();

protected:
  void changeEvent(QEvent *e);
};

} // namespace Gui

#endif // PARTGUI_DIALOG_DLGSETTINGSOBJECTCOLOR_H
