/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef PARTGUI_MIRRORING_H
#define PARTGUI_MIRRORING_H

#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"

class QTreeWidgetItem;

namespace App {
class DocumentObject;
class Property;
}
namespace PartGui {

class Ui_Mirroring;
class Mirroring : public QWidget
{
    Q_OBJECT

public:
    Mirroring(QWidget* parent = 0);
    ~Mirroring();
    bool accept();

protected:
    void changeEvent(QEvent *e);

private:
    void findShapes();

private:
    QString document;
    Ui_Mirroring* ui;
};

class TaskMirroring : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskMirroring();
    ~TaskMirroring();

public:
    bool accept();

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok | QDialogButtonBox::Cancel; }
    virtual bool isAllowedAlterDocument(void) const
    { return false; }
    virtual bool needsFullSpace() const
    { return false; }

private:
    Mirroring* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} // namespace PartGui

#endif // PARTGUI_MIRRORING_H
