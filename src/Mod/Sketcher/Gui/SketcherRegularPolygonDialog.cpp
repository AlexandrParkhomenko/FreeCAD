/***************************************************************************
 *   Copyright (c) 2017 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QPixmap>
# include <QDialog>

#include "Gui/BitmapFactory.h"
#include "Gui/MainWindow.h"
#include "Base/Tools.h"
#include "Base/UnitsApi.h"

#include "ui_SketcherRegularPolygonDialog.h"
#include "SketcherRegularPolygonDialog.h"

using namespace SketcherGui;

SketcherRegularPolygonDialog::SketcherRegularPolygonDialog(void)
: QDialog(Gui::getMainWindow()), ui(new Ui_SketcherRegularPolygonDialog)
{
    ui->setupUi(this);

    ui->sidesQuantitySpinBox->onRestore();

    updateValues();
}

SketcherRegularPolygonDialog::~SketcherRegularPolygonDialog()
{
    delete ui;
}

void SketcherRegularPolygonDialog::accept()
{
    ui->sidesQuantitySpinBox->onSave();

    updateValues();

    QDialog::accept();
}

void SketcherRegularPolygonDialog::updateValues(void)
{
    sides = ui->sidesQuantitySpinBox->value();
}

#include "moc_SketcherRegularPolygonDialog.cpp"
