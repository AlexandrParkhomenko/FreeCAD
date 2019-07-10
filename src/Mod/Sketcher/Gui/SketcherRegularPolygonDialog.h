/***************************************************************************
 *   Copyright (c) 2017 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef SKETCHERGUI_SketcherRegularPolygonDialog_H
#define SKETCHERGUI_SketcherRegularPolygonDialog_H

#include "Base/Placement.h"
#include <QDialog>

namespace SketcherGui {

class Ui_SketcherRegularPolygonDialog;
class SketcherRegularPolygonDialog : public QDialog
{
    Q_OBJECT

public:
    SketcherRegularPolygonDialog(void);
    ~SketcherRegularPolygonDialog();

    void accept();

    int sides;

protected:
    void updateValues(void);
private:
    Ui_SketcherRegularPolygonDialog* ui;
};

}

#endif // SKETCHERGUI_SketcherRegularPolygonDialog_H
