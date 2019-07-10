/***************************************************************************
 *   Copyright (c) 2015 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com      *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_TASKVIEW_TaskSketcherSolverAdvanced_H
#define GUI_TASKVIEW_TaskSketcherSolverAdvanced_H

#include "Gui/TaskView/TaskView.h"
#include "Gui/Selection.h"

class Ui_TaskSketcherSolverAdvanced;

namespace App {
class Property;
}

namespace SketcherGui { 

class ViewProviderSketch;

class TaskSketcherSolverAdvanced : public Gui::TaskView::TaskBox
{
    Q_OBJECT

public:
    TaskSketcherSolverAdvanced(ViewProviderSketch *sketchView);
    ~TaskSketcherSolverAdvanced();

private Q_SLOTS:
    void on_comboBoxDefaultSolver_currentIndexChanged(int index); 
    void on_comboBoxDogLegGaussStep_currentIndexChanged(int index);    
    void on_spinBoxMaxIter_valueChanged(int i);
    void on_checkBoxSketchSizeMultiplier_stateChanged(int state);    
    void on_lineEditConvergence_editingFinished();
    void on_comboBoxQRMethod_currentIndexChanged(int index);
    void on_lineEditQRPivotThreshold_editingFinished();
    void on_comboBoxRedundantDefaultSolver_currentIndexChanged(int index);
    void on_lineEditRedundantConvergence_editingFinished();
    void on_spinBoxRedundantSolverMaxIterations_valueChanged(int i);
    void on_checkBoxRedundantSketchSizeMultiplier_stateChanged(int state);
    void on_comboBoxDebugMode_currentIndexChanged(int index);
    void on_lineEditSolverParam1_editingFinished();
    void on_lineEditRedundantSolverParam1_editingFinished();
    void on_lineEditSolverParam2_editingFinished();
    void on_lineEditRedundantSolverParam2_editingFinished();
    void on_lineEditSolverParam3_editingFinished();
    void on_lineEditRedundantSolverParam3_editingFinished();
    void on_pushButtonDefaults_clicked(bool checked = false);
    void on_pushButtonSolve_clicked(bool checked = false);

protected:
    void updateDefaultMethodParameters(void);
    void updateRedundantMethodParameters(void);
    void updateSketchObject(void); 
protected:
    ViewProviderSketch *sketchView;

private:
    QWidget* proxy;
    Ui_TaskSketcherSolverAdvanced* ui;
};

} //namespace SketcherGui

#endif // GUI_TASKVIEW_TaskSketcherSolverAdvanced_H
