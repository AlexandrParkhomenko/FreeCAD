/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESHGUI_REMOVECOMPONENTS_H
#define MESHGUI_REMOVECOMPONENTS_H

#include "stdexport.h"
#include <QDialog>
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"
#include "MeshSelection.h"

namespace MeshGui {
class Ui_RemoveComponents;

/**
 * Non-modal dialog to de/select components, regions, the complete or single faces
 * of a mesh and delete them.
 * @author Werner Mayer
 */
class MeshGuiExport RemoveComponents : public QWidget
{
    Q_OBJECT

public:
    RemoveComponents(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~RemoveComponents();
    void reject();
    void deleteSelection();
    void invertSelection();

public Q_SLOTS:
    void on_selectRegion_clicked();
    void on_selectAll_clicked();
    void on_selectComponents_clicked();
    void on_selectTriangle_clicked();
    void on_deselectRegion_clicked();
    void on_deselectAll_clicked();
    void on_deselectComponents_clicked();
    void on_deselectTriangle_clicked();
    void on_visibleTriangles_toggled(bool);
    void on_screenTriangles_toggled(bool);
    void on_cbSelectComp_toggled(bool);
    void on_cbDeselectComp_toggled(bool);

protected:
    void changeEvent(QEvent *e);

private:
    Ui_RemoveComponents* ui;
    MeshSelection meshSel;
};

/**
 * Embed the panel into a dialog.
 */
class MeshGuiExport RemoveComponentsDialog : public QDialog
{
    Q_OBJECT

public:
    RemoveComponentsDialog(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~RemoveComponentsDialog();
    void reject();

private Q_SLOTS:
    void clicked(QAbstractButton* btn);

private:
    RemoveComponents* widget;
};

/**
 * Embed the panel into a task dialog.
 */
class TaskRemoveComponents : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskRemoveComponents();
    ~TaskRemoveComponents();

public:
    bool accept();
    void clicked(int);

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok | QDialogButtonBox::Close; }
    virtual bool isAllowedAlterDocument(void) const
    { return true; }
    virtual void modifyStandardButtons(QDialogButtonBox*);

private:
    RemoveComponents* widget;
    Gui::TaskView::TaskBox* taskbox;
};

}

#endif // MESHGUI_REMOVECOMPONENTS_H
