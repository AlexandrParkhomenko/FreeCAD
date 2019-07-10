/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DIALOG_CLIPPING_H
#define GUI_DIALOG_CLIPPING_H

#include "stdexport.h"
#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"
#include <QWidget>

namespace Gui {
class View3DInventor;
namespace Dialog {

/**
 * @author Werner Mayer
 */
class GuiExport Clipping : public QWidget
{
    Q_OBJECT

public:
    Clipping(Gui::View3DInventor* view, QWidget* parent = 0);
    ~Clipping();

protected Q_SLOTS:
    void on_groupBoxX_toggled(bool);
    void on_groupBoxY_toggled(bool);
    void on_groupBoxZ_toggled(bool);
    void on_clipX_valueChanged(double);
    void on_clipY_valueChanged(double);
    void on_clipZ_valueChanged(double);
    void on_flipClipX_clicked();
    void on_flipClipY_clicked();
    void on_flipClipZ_clicked();
    void on_groupBoxView_toggled(bool);
    void on_clipView_valueChanged(double);
    void on_fromView_clicked();
    void on_adjustViewdirection_toggled(bool);
    void on_dirX_valueChanged(double);
    void on_dirY_valueChanged(double);
    void on_dirZ_valueChanged(double);

private:

private:
    class Private;
    Private* d;
};

/**
 * Embed the panel into a task dialog.
 */
class TaskClipping : public Gui::TaskView::TaskDialog
{
public:
    TaskClipping(Gui::View3DInventor* view);
    ~TaskClipping();

public:
    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Close; }
};

} // namespace Dialog
} // namespace Gui

#endif // GUI_DIALOG_CLIPPING_H
