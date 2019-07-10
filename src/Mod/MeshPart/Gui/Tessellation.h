/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef MESHPARTGUI_TESSELLATION_H
#define MESHPARTGUI_TESSELLATION_H

#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"
#include "Gui/Selection.h"
#include <memory>

class QButtonGroup;

namespace MeshPartGui {

class Ui_Tessellation;
class Tessellation : public QWidget
{
    Q_OBJECT

public:
    Tessellation(QWidget* parent = 0);
    ~Tessellation();
    bool accept();

protected:
    void changeEvent(QEvent *e);

private:
    void findShapes();

private Q_SLOTS:
    void meshingMethod(int id);
    void on_comboFineness_currentIndexChanged(int);
    void on_checkSecondOrder_toggled(bool);
    void on_checkQuadDominated_toggled(bool);

private:
    QString document;
    QButtonGroup* buttonGroup;
    std::unique_ptr<Ui_Tessellation> ui;
};

class TaskTessellation : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskTessellation();
    ~TaskTessellation();

public:
    virtual void open();
    virtual void clicked(int);
    virtual bool accept();
    virtual bool reject();

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok|QDialogButtonBox::Cancel; }

private:
    Tessellation* widget;
};

} // namespace MeshPartGui

#endif // MESHPARTGUI_TESSELLATION_H
