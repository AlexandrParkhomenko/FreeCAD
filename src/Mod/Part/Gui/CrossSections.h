/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PARTGUI_CROSSSECTIONS_H
#define PARTGUI_CROSSSECTIONS_H

#include "Gui/TaskView/TaskDialog.h"
#include "Gui/TaskView/TaskView.h"
#include "Base/BoundBox.h"
#include <QDialog>
#include <QPointer>

namespace Gui {
class View3DInventor;
}

namespace PartGui {

class ViewProviderCrossSections;
class Ui_CrossSections;
class CrossSections : public QDialog
{
    Q_OBJECT

    enum Plane { XY, XZ, YZ };

public:
    CrossSections(const Base::BoundBox3d& bb, QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~CrossSections();
    void accept();
    void apply();

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent(QKeyEvent*);

private Q_SLOTS:
    void on_xyPlane_clicked();
    void on_xzPlane_clicked();
    void on_yzPlane_clicked();
    void on_position_valueChanged(double);
    void on_distance_valueChanged(double);
    void on_countSections_valueChanged(int);
    void on_checkBothSides_toggled(bool);
    void on_sectionsBox_toggled(bool);

private:
    std::vector<double> getPlanes() const;
    void calcPlane(Plane, double);
    void calcPlanes(Plane/*, double, bool, int*/);
    void makePlanes(Plane, const std::vector<double>&, double[4]);
    Plane plane() const;

private:
    Ui_CrossSections* ui;
    Base::BoundBox3d bbox;
    ViewProviderCrossSections* vp;
    QPointer<Gui::View3DInventor> view;
};

class TaskCrossSections : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskCrossSections(const Base::BoundBox3d& bb);
    ~TaskCrossSections();

public:
    bool accept();
    void clicked(int id);

    virtual QDialogButtonBox::StandardButtons getStandardButtons() const
    { return QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel; }

private:
    CrossSections* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} // namespace PartGui

#endif // PARTGUI_CROSSSECTIONS_H
