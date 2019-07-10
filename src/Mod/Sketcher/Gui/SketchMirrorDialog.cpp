/***************************************************************************
 *   Copyright (c) 2015 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com      *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <QPixmap>
# include <QDialog>

#include "Gui/BitmapFactory.h"
#include "Gui/MainWindow.h"
#include "Base/Tools.h"
#include "Base/UnitsApi.h"

#include "ui_SketchMirrorDialog.h"
#include "SketchMirrorDialog.h"
#include "Mod/Sketcher/App/SketchObject.h"

using namespace SketcherGui;

SketchMirrorDialog::SketchMirrorDialog(void)
  : QDialog(Gui::getMainWindow())
  , RefGeoid(-1)
  , RefPosid(Sketcher::none)
  , ui(new Ui_SketchMirrorDialog)
{
    ui->setupUi(this);
}

SketchMirrorDialog::~SketchMirrorDialog()
{
    delete ui;
}

void SketchMirrorDialog::accept()
{
    if (ui->XAxisRadioButton->isChecked()) {
        RefGeoid=Sketcher::GeoEnum::HAxis;
        RefPosid=Sketcher::none;
    }
    else if (ui->YAxisRadioButton->isChecked()) {
        RefGeoid=Sketcher::GeoEnum::VAxis;
        RefPosid=Sketcher::none; 
    }
    else if (ui->OriginRadioButton->isChecked()) {
        RefGeoid=Sketcher::GeoEnum::RtPnt;
        RefPosid=Sketcher::start; 
    }

    QDialog::accept();
}

#include "moc_SketchMirrorDialog.cpp"
