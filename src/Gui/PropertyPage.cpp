/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "PropertyPage.h"
#include "PrefWidgets.h"
#include "WidgetFactory.h"
#include "Base/Console.h"

using namespace Gui::Dialog;

/** Construction */
PropertyPage::PropertyPage(QWidget* parent) : QWidget(parent) 
{
  bChanged = false;
}

/** Destruction */
PropertyPage::~PropertyPage() 
{
}

/** Applies all changes. Reimplement this in your subclasses. */
void PropertyPage::apply()
{
}

/** Discards all changes. Reimplement this in your subclasses. */
void PropertyPage::cancel()
{
}

/** Resets to the default values. Reimplement this in your subclasses. */
void PropertyPage::reset()
{
}

/** Returns whether the page was modified or not. */
bool PropertyPage::isModified()
{
  return bChanged;
}

/** Sets the page to be modified. */
void PropertyPage::setModified(bool b)
{
  bChanged = b;
}

/** Applies all changes calling @ref apply() and resets the modified state. */
void PropertyPage::onApply()
{
  if (isModified())
    apply();

  setModified(false);
}

/** Discards all changes calling @ref cancel() and resets the modified state. */
void PropertyPage::onCancel()
{
  if (isModified())
  {
    cancel();
    setModified(false);
  }
}

/** Resets to the default values. */
void PropertyPage::onReset()
{
  reset();
}

// ----------------------------------------------------------------

/** Construction */
PreferencePage::PreferencePage(QWidget* parent) : QWidget(parent) 
{
}

/** Destruction */
PreferencePage::~PreferencePage() 
{
}

void PreferencePage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
}

// ----------------------------------------------------------------

PreferenceUiForm::PreferenceUiForm(const QString& fn, QWidget* parent)
  : PreferencePage(parent), form(0)
{
    UiLoader loader;
    loader.setLanguageChangeEnabled(false);
    QFile file(fn);
    if (file.open(QFile::ReadOnly))
        form = loader.load(&file, this);
    file.close();
    if (form) {
        this->setWindowTitle(form->windowTitle());
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(form);
        setLayout(layout);
    }
    else {
        Base::Console().Error("Failed to load UI file from '%s'\n",
            (const char*)fn.toUtf8());
    }
}

PreferenceUiForm::~PreferenceUiForm()
{
}

void PreferenceUiForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
}

template <typename PW>
void PreferenceUiForm::loadPrefWidgets(void)
{
    QList<PW> pw = form->findChildren<PW>();
    for (typename QList<PW>::iterator it = pw.begin(); it != pw.end(); ++it)
        (*it)->onRestore();
}

template <typename PW>
void PreferenceUiForm::savePrefWidgets(void)
{
    QList<PW> pw = form->findChildren<PW>();
    for (typename QList<PW>::iterator it = pw.begin(); it != pw.end(); ++it)
        (*it)->onSave();
}

void PreferenceUiForm::loadSettings()
{
    if (!form)
        return;

    // search for all pref widgets to restore their settings
    loadPrefWidgets<Gui::PrefSpinBox        *>();
    loadPrefWidgets<Gui::PrefDoubleSpinBox  *>();
    loadPrefWidgets<Gui::PrefLineEdit       *>();
    loadPrefWidgets<Gui::PrefFileChooser    *>();
    loadPrefWidgets<Gui::PrefComboBox       *>();
    loadPrefWidgets<Gui::PrefCheckBox       *>();
    loadPrefWidgets<Gui::PrefRadioButton    *>();
    loadPrefWidgets<Gui::PrefSlider         *>();
    loadPrefWidgets<Gui::PrefColorButton    *>();
    loadPrefWidgets<Gui::PrefUnitSpinBox    *>();
}

void PreferenceUiForm::saveSettings()
{
    if (!form)
        return;

    // search for all pref widgets to save their settings
    savePrefWidgets<Gui::PrefSpinBox        *>();
    savePrefWidgets<Gui::PrefDoubleSpinBox  *>();
    savePrefWidgets<Gui::PrefLineEdit       *>();
    savePrefWidgets<Gui::PrefFileChooser    *>();
    savePrefWidgets<Gui::PrefComboBox       *>();
    savePrefWidgets<Gui::PrefCheckBox       *>();
    savePrefWidgets<Gui::PrefRadioButton    *>();
    savePrefWidgets<Gui::PrefSlider         *>();
    savePrefWidgets<Gui::PrefColorButton    *>();
    savePrefWidgets<Gui::PrefUnitSpinBox    *>();
}

// ----------------------------------------------------------------

/** Construction */
CustomizeActionPage::CustomizeActionPage(QWidget* parent) : QWidget(parent) 
{
}

/** Destruction */
CustomizeActionPage::~CustomizeActionPage() 
{
}

bool CustomizeActionPage::event(QEvent* e)
{
    bool ok = QWidget::event(e);

    if (e->type() == QEvent::ParentChange || e->type() == QEvent::ParentAboutToChange) {
        QWidget* topLevel = this->parentWidget();
        while (topLevel && !topLevel->inherits("QDialog"))
            topLevel = topLevel->parentWidget();
        if (topLevel) {
            int index = topLevel->metaObject()->indexOfSignal( QMetaObject::normalizedSignature("addMacroAction(const QByteArray&)") );
            if (index >= 0) {
                if (e->type() == QEvent::ParentChange) {
                    connect(topLevel, SIGNAL(addMacroAction( const QByteArray& )),
                            this, SLOT(onAddMacroAction( const QByteArray& )));
                    connect(topLevel, SIGNAL(removeMacroAction( const QByteArray& )),
                            this, SLOT(onRemoveMacroAction( const QByteArray& )));
                    connect(topLevel, SIGNAL(modifyMacroAction( const QByteArray& )),
                            this, SLOT(onModifyMacroAction( const QByteArray& )));
                }
                else {
                    disconnect(topLevel, SIGNAL(addMacroAction( const QByteArray& )),
                               this, SLOT(onAddMacroAction( const QByteArray& )));
                    disconnect(topLevel, SIGNAL(removeMacroAction( const QByteArray& )),
                               this, SLOT(onRemoveMacroAction( const QByteArray& )));
                    disconnect(topLevel, SIGNAL(modifyMacroAction( const QByteArray& )),
                               this, SLOT(onModifyMacroAction( const QByteArray& )));
                }
            }
        }
    }

    return ok;
}

void CustomizeActionPage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
}

#include "moc_PropertyPage.cpp"
