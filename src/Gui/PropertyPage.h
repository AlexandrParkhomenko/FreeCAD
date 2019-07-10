/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_PROPERTYPAGE_H
#define GUI_DIALOG_PROPERTYPAGE_H

#include "stdexport.h"
#include <QWidget>

namespace Gui {
namespace Dialog {

/** Base class for property pages.
 * \author Werner Mayer
 */
class GuiExport PropertyPage : public QWidget
{
    Q_OBJECT

public:
    PropertyPage(QWidget* parent = 0);
    virtual ~PropertyPage();

    bool isModified();
    void setModified(bool b);
    void onApply();
    void onCancel();
    void onReset();

protected:
    virtual void apply();
    virtual void cancel();
    virtual void reset();

private:
    bool bChanged; /**< for internal use only */

protected Q_SLOTS:
    virtual void loadSettings()=0;
    virtual void saveSettings()=0;
};

/** Base class for preferences pages.
 * \author Werner Mayer
 */
class GuiExport PreferencePage : public QWidget
{
    Q_OBJECT

public:
    PreferencePage(QWidget* parent = 0);
    virtual ~PreferencePage();

public Q_SLOTS:
    virtual void loadSettings()=0;
    virtual void saveSettings()=0;

protected:
    virtual void changeEvent(QEvent *e) = 0;
};

/** Subclass that embeds a form from a UI file.
 * \author Werner Mayer
 */
class GuiExport PreferenceUiForm : public PreferencePage
{
    Q_OBJECT

public:
    PreferenceUiForm(const QString& fn, QWidget* parent = 0);
    virtual ~PreferenceUiForm();

    void loadSettings();
    void saveSettings();

protected:
    void changeEvent(QEvent *e);

private:
    template <typename PW>
    void loadPrefWidgets();
    template <typename PW>
    void savePrefWidgets();

private:
    QWidget* form;
};

/** Base class for custom pages.
 * \author Werner Mayer
 */
class GuiExport CustomizeActionPage : public QWidget
{
    Q_OBJECT

public:
    CustomizeActionPage(QWidget* parent = 0);
    virtual ~CustomizeActionPage();

protected:
    bool event(QEvent* e);
    virtual void changeEvent(QEvent *e) = 0;

protected Q_SLOTS:
    virtual void onAddMacroAction(const QByteArray&)=0;
    virtual void onRemoveMacroAction(const QByteArray&)=0;
    virtual void onModifyMacroAction(const QByteArray&)=0;
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_PROPERTYPAGE_H
