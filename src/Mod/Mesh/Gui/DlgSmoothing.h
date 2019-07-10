/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESHGUI_DLGSMOOTHING_H
#define MESHGUI_DLGSMOOTHING_H

#include "stdexport.h"
#include <QDialog>
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"

class QButtonGroup;

namespace MeshGui {

class Selection;
class Ui_DlgSmoothing;
class DlgSmoothing : public QWidget
{
    Q_OBJECT

public:
    enum Smooth {
        None,
        Taubin,
        Laplace
    };

    DlgSmoothing(QWidget* parent = 0);
    ~DlgSmoothing();
    int iterations() const;
    double lambdaStep() const;
    double microStep() const;
    Smooth method() const;
    bool smoothSelection() const;

private Q_SLOTS:
    void method_clicked(int);
    void on_checkBoxSelection_toggled(bool);

Q_SIGNALS:
    void toggledSelection(bool);

private:
    Ui_DlgSmoothing* ui;
    QButtonGroup* bg;
};

/**
 * Embed the panel into a dialog.
 */
class MeshGuiExport SmoothingDialog : public QDialog
{
    Q_OBJECT

public:
    SmoothingDialog(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~SmoothingDialog();

    int iterations() const
    { return widget->iterations(); }
    double lambdaStep() const
    { return widget->lambdaStep(); }
    double microStep() const
    { return widget->microStep(); }
    DlgSmoothing::Smooth method() const
    { return widget->method(); }
    bool smoothSelection() const
    { return widget->smoothSelection(); }

private:
    DlgSmoothing* widget;
};

/**
 * Embed the panel into a task dialog.
 */
class TaskSmoothing : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskSmoothing();
    ~TaskSmoothing();

public:
    bool accept();

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok | QDialogButtonBox::Cancel; }
    virtual bool isAllowedAlterDocument(void) const
    { return true; }

private:
    DlgSmoothing* widget;
    Selection* selection;
};

}

#endif // MESHGUI_DLGSMOOTHING_H
