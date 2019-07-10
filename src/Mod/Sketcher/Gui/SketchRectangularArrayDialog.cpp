/***************************************************************************
 *   Copyright (c) 2015 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QPixmap>
# include <QDialog>

#include "Gui/BitmapFactory.h"
#include "Gui/MainWindow.h"
#include "Base/Tools.h"
#include "Base/UnitsApi.h"

#include "ui_SketchRectangularArrayDialog.h"
#include "SketchRectangularArrayDialog.h"

using namespace SketcherGui;

SketchRectangularArrayDialog::SketchRectangularArrayDialog(void)
  : QDialog(Gui::getMainWindow()), ui(new Ui_SketchRectangularArrayDialog)
{
    ui->setupUi(this);
    
    ui->RowsQuantitySpinBox->onRestore();
    ui->ColsQuantitySpinBox->onRestore();
    ui->ConstraintSeparationCheckBox->onRestore();
    ui->EqualVerticalHorizontalSpacingCheckBox->onRestore();
    ui->CloneCheckBox->onRestore();
    
    updateValues();
}

SketchRectangularArrayDialog::~SketchRectangularArrayDialog()
{
    delete ui;
}

void SketchRectangularArrayDialog::accept()
{
    ui->RowsQuantitySpinBox->onSave();
    ui->ColsQuantitySpinBox->onSave();
    ui->ConstraintSeparationCheckBox->onSave();
    ui->EqualVerticalHorizontalSpacingCheckBox->onSave();
    ui->CloneCheckBox->onSave();
    
    updateValues();
    
    QDialog::accept();
}

void SketchRectangularArrayDialog::updateValues(void)
{
    Rows = ui->RowsQuantitySpinBox->value();
    Cols = ui->ColsQuantitySpinBox->value();
    ConstraintSeparation = ui->ConstraintSeparationCheckBox->isChecked();
    EqualVerticalHorizontalSpacing = ui->EqualVerticalHorizontalSpacingCheckBox->isChecked();
    Clone = ui->CloneCheckBox->isChecked();    
}

#include "moc_SketchRectangularArrayDialog.cpp"
