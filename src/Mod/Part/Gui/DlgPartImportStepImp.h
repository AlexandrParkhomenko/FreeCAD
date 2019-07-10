/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef DlgPartImportStepImp_H
#define DlgPartImportStepImp_H

#include "ui_DlgPartImportStep.h"


namespace PartGui {

class DlgPartImportStepImp : public QDialog, public Ui_DlgPartImportStep
{ 
    Q_OBJECT

public:
  DlgPartImportStepImp( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
  ~DlgPartImportStepImp();

public Q_SLOTS:
  virtual void OnApply();
  virtual void onChooseFileName();

};

} // namespace PartGui

#endif // DlgPartImportStepImp_H
