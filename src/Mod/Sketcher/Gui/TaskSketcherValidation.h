/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef SKETCHERGUI_TASKSKETCHERVALIDATION_H
#define SKETCHERGUI_TASKSKETCHERVALIDATION_H

#include <vector>
#include <memory>
#include "Base/Vector3D.h"
#include "Gui/TaskView/TaskDialog.h"
#include "Mod/Sketcher/App/SketchAnalysis.h"

class SoGroup;
namespace Sketcher { class SketchObject; } 

namespace SketcherGui {

class Ui_TaskSketcherValidation;
class SketcherValidation : public QWidget
{
    Q_OBJECT

public:
    SketcherValidation(Sketcher::SketchObject* Obj, QWidget* parent = 0);
    ~SketcherValidation();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
    void on_findButton_clicked();
    void on_fixButton_clicked();
    void on_highlightButton_clicked();
    void on_findConstraint_clicked();
    void on_fixConstraint_clicked();
    void on_findReversed_clicked();
    void on_swapReversed_clicked();
    void on_orientLockEnable_clicked();
    void on_orientLockDisable_clicked();
    void on_delConstrExtr_clicked();

private:
    void showPoints(const std::vector<Base::Vector3d>&);
    void hidePoints();

private:
    std::unique_ptr<Ui_TaskSketcherValidation> ui;
    Sketcher::SketchObject* sketch;
    Sketcher::SketchAnalysis sketchAnalyser;
    SoGroup* coincidenceRoot;
};

class TaskSketcherValidation : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    TaskSketcherValidation(Sketcher::SketchObject* Obj);
    ~TaskSketcherValidation();
    virtual QDialogButtonBox::StandardButtons getStandardButtons(void) const
    { return QDialogButtonBox::Close; }
};

} //namespace SketcherGui

#endif // SKETCHERGUI_TASKSKETCHERVALIDATION_H
