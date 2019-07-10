/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "BitmapFactory.h"
#include "WidgetFactory.h"
#include "Workbench.h"

// INCLUDE YOUR PREFERENCFE PAGES HERE
//
#include "DlgPreferencesImp.h"
#include "DlgSettings3DViewImp.h"
#include "DlgSettingsViewColor.h"
#include "DlgGeneralImp.h"
#include "DlgEditorImp.h"
#include "DlgSettingsMacroImp.h"
#include "DlgSettingsUnitsImp.h"
#include "DlgSettingsDocumentImp.h"
//#include "DlgOnlineHelpImp.h"
#include "DlgReportViewImp.h"

#include "DlgToolbarsImp.h"
#include "DlgWorkbenchesImp.h"
#include "DlgActionsImp.h"
#include "DlgCommandsImp.h"
#include "DlgKeyboardImp.h"
#include "InputField.h"
#include "QuantitySpinBox.h"

using namespace Gui;
using namespace Gui::Dialog;

/**
 * Registers all preference pages or widgets to create them dynamically at any later time.
 */
WidgetFactorySupplier::WidgetFactorySupplier()
{
    // ADD YOUR PREFERENCE PAGES HERE 
    //
    //
    new PrefPageProducer<DlgGeneralImp>         ( QT_TRANSLATE_NOOP("QObject","General") );
  //new PrefPageProducer<DlgOnlineHelpImp>      ( QT_TRANSLATE_NOOP("QObject","General") );
    new PrefPageProducer<DlgSettingsDocumentImp>( QT_TRANSLATE_NOOP("QObject","General") );
    new PrefPageProducer<DlgSettingsEditorImp>  ( QT_TRANSLATE_NOOP("QObject","General") );
    new PrefPageProducer<DlgReportViewImp>      ( QT_TRANSLATE_NOOP("QObject","General") );
    new PrefPageProducer<DlgSettingsMacroImp>   ( QT_TRANSLATE_NOOP("QObject","General") );
    new PrefPageProducer<DlgSettingsUnitsImp>   ( QT_TRANSLATE_NOOP("QObject","General") );
    new PrefPageProducer<DlgSettings3DViewImp>  ( QT_TRANSLATE_NOOP("QObject","Display") );
    new PrefPageProducer<DlgSettingsViewColor>  ( QT_TRANSLATE_NOOP("QObject","Display") );

    // ADD YOUR CUSTOMIZE PAGES HERE
    //
    //
    new CustomPageProducer<DlgCustomCommandsImp>;
    new CustomPageProducer<DlgCustomKeyboardImp>;
    new CustomPageProducer<DlgWorkbenchesImp>;
    new CustomPageProducer<DlgCustomToolbarsImp>;
  //new CustomPageProducer<DlgCustomToolBoxbarsImp>;
    new CustomPageProducer<DlgCustomActionsImp>;

    // ADD YOUR PREFERENCE WIDGETS HERE
    //
    //
    new WidgetProducer<Gui::InputField>;
    new WidgetProducer<Gui::PrefSpinBox>;
    new WidgetProducer<Gui::PrefDoubleSpinBox>;
    new WidgetProducer<Gui::PrefLineEdit>;
    new WidgetProducer<Gui::PrefComboBox>;
    new WidgetProducer<Gui::PrefCheckBox>;
    new WidgetProducer<Gui::PrefRadioButton>;
    new WidgetProducer<Gui::PrefSlider>;
    new WidgetProducer<Gui::PrefFileChooser>;
    new WidgetProducer<Gui::PrefColorButton>;
    new WidgetProducer<Gui::PrefUnitSpinBox>;
    new WidgetProducer<Gui::PrefQuantitySpinBox>;
    new WidgetProducer<Gui::CommandIconView>;
    new WidgetProducer<Gui::AccelLineEdit>;
    new WidgetProducer<Gui::ActionSelector>;
    new WidgetProducer<Gui::ColorButton>;
    new WidgetProducer<Gui::UrlLabel>;
    new WidgetProducer<Gui::FileChooser>;
    new WidgetProducer<Gui::UIntSpinBox>;
    new WidgetProducer<Gui::QuantitySpinBox>;
}
