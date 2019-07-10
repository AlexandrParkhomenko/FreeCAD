/***************************************************************************
 *   Copyright (c) 2015 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef SKETCHERGUI_SketchRectangularArrayDialog_H
#define SKETCHERGUI_SketchRectangularArrayDialog_H

#include "Base/Placement.h"
#include <QDialog>

namespace SketcherGui {

class Ui_SketchRectangularArrayDialog;
class SketchRectangularArrayDialog : public QDialog
{
    Q_OBJECT

public:
    SketchRectangularArrayDialog(void);
    ~SketchRectangularArrayDialog();

    void accept();
    
    int Rows;
    int Cols;
    bool ConstraintSeparation;
    bool EqualVerticalHorizontalSpacing;
    bool Clone;

protected:
    void updateValues(void);
private:
    Ui_SketchRectangularArrayDialog* ui;
};

}

#endif // SKETCHERGUI_SketchRectangularArrayDialog_H
