/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PATHGUI_DIALOG_DLGSETTINGSPATHCOLOR_H
#define PATHGUI_DIALOG_DLGSETTINGSPATHCOLOR_H

#include "ui_DlgSettingsPathColor.h"
#include "Gui/PropertyPage.h"

namespace PathGui {

class DlgSettingsPathColor : public Gui::Dialog::PreferencePage, public Ui_DlgSettingsPathColor
{ 
  Q_OBJECT

public:
  DlgSettingsPathColor(QWidget* parent = 0);
  ~DlgSettingsPathColor();

  void saveSettings();
  void loadSettings();

protected:
  void changeEvent(QEvent *e);
};

} // namespace PathGui

#endif // PATHGUI_DIALOG_DLGSETTINGSPATHCOLOR_H
