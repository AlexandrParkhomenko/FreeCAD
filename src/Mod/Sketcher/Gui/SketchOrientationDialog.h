/***************************************************************************
 *   Copyright (c) 2011 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef SKETCHERGUI_SketchOrientationDialog_H
#define SKETCHERGUI_SketchOrientationDialog_H

#include "stdexport.h"
#include "Base/Placement.h"
#include <QDialog>

namespace SketcherGui {

class Ui_SketchOrientationDialog;
class SketcherGuiExport SketchOrientationDialog : public QDialog
{
    Q_OBJECT

public:
    SketchOrientationDialog(void);
    ~SketchOrientationDialog();

    Base::Placement Pos;
    int             DirType;

    void accept();

protected Q_SLOTS:
    void onPreview();

private:
    Ui_SketchOrientationDialog* ui;
};

}

#endif // SKETCHERGUI_SketchOrientationDialog_H
