/***************************************************************************
 *   Copyright (c) 2015 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com      *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef SKETCHERGUI_SketchMirrorDialog_H
#define SKETCHERGUI_SketchMirrorDialog_H

#include <QDialog>
#include "../App/Constraint.h"

namespace SketcherGui {

class Ui_SketchMirrorDialog;
class SketchMirrorDialog : public QDialog
{
    Q_OBJECT

public:
    SketchMirrorDialog(void);
    ~SketchMirrorDialog();

    int RefGeoid;
    Sketcher::PointPos RefPosid;

    void accept();

private:
    Ui_SketchMirrorDialog* ui;
};

}

#endif // SKETCHERGUI_SketchMirrorDialog_H
