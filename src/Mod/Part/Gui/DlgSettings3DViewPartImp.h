/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_DLGSETTINGS3DVIEWIMP_H
#define PARTGUI_DLGSETTINGS3DVIEWIMP_H

#include "Gui/PropertyPage.h"
#include <memory>

namespace PartGui {
class Ui_DlgSettings3DViewPart;
/**
 * The DlgSettings3DViewPartImp class implements a preference page to change settings
 * for the Inventor viewer.
 * \author Jürgen Riegel
 */
class DlgSettings3DViewPart : public Gui::Dialog::PreferencePage
{ 
    Q_OBJECT

public:
    DlgSettings3DViewPart(QWidget* parent = 0);
    ~DlgSettings3DViewPart();

protected:
    void saveSettings();
    void loadSettings();
    void changeEvent(QEvent *e);

private Q_SLOTS:
    void on_maxDeviation_valueChanged(double);

private:
    std::unique_ptr<Ui_DlgSettings3DViewPart> ui;
    bool checkValue;
};

} // namespace Gui

#endif // PARTGUI_DLGSETTINGS3DVIEWIMP_H
