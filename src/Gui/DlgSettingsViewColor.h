/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_DLGSETTINGSVIEWCOLOR_H
#define GUI_DIALOG_DLGSETTINGSVIEWCOLOR_H

#include "ui_DlgSettingsViewColor.h"
#include "PropertyPage.h"

namespace Gui {
namespace Dialog {

/**
 * The DlgSettingsViewColor class implements a preference page to change color settings
 * for the Inventor viewer like background and selection.
 * @author Werner Mayer
 */
class DlgSettingsViewColor : public PreferencePage, public Ui_DlgSettingsViewColor
{ 
  Q_OBJECT

public:
  DlgSettingsViewColor(QWidget* parent = 0);
  ~DlgSettingsViewColor();

  void saveSettings();
  void loadSettings();

protected:
  void changeEvent(QEvent *e);
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_DLGSETTINGSVIEWCOLOR_H
