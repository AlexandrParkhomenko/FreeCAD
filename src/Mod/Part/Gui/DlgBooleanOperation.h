/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef PARTGUI_DLGBOOLEANOPERATION_H
#define PARTGUI_DLGBOOLEANOPERATION_H

#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"
#include <boost/signals2.hpp>

class QTreeWidgetItem;

namespace App {
class DocumentObject;
class Property;
}
namespace PartGui {

typedef boost::signals2::connection Connection;
class Ui_DlgBooleanOperation;
class DlgBooleanOperation : public QWidget
{
    Q_OBJECT

public:
    DlgBooleanOperation(QWidget* parent = 0);
    ~DlgBooleanOperation();
    void accept();

private:
    void findShapes();
    bool indexOfCurrentItem(QTreeWidgetItem*, int&, int&) const;
    void slotCreatedObject(const App::DocumentObject&);
    void slotChangedObject(const App::DocumentObject&, const App::Property&);
    bool hasSolids(const App::DocumentObject*) const;

protected:
    void changeEvent(QEvent *e);

public Q_SLOTS:
    void on_swapButton_clicked();

private Q_SLOTS:
    void currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*);

private:
    Ui_DlgBooleanOperation* ui;
    Connection connectNewObject;
    Connection connectModObject;
    std::list<const App::DocumentObject*> observe;
};

class TaskBooleanOperation : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskBooleanOperation();
    ~TaskBooleanOperation();

public:
    void clicked(int);

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Apply | QDialogButtonBox::Close; }
    virtual bool isAllowedAlterDocument(void) const
    { return true; }
    virtual bool needsFullSpace() const
    { return true; }

private:
    DlgBooleanOperation* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} // namespace PartGui

#endif // PARTGUI_DLGBOOLEANOPERATION_H
