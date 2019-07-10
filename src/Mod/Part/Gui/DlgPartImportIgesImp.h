/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef DlgPartImportIgesImp_H
#define DlgPartImportIgesImp_H

#include "ui_DlgPartImportIges.h"


namespace PartGui {

class DlgPartImportIgesImp : public QDialog, public Ui_DlgPartImportIges
{ 
    Q_OBJECT

public:
  DlgPartImportIgesImp( QWidget* parent = 0, Qt::WindowFlags fl = 0 );
  ~DlgPartImportIgesImp();

public Q_SLOTS:
  virtual void OnApply();
  virtual void onChooseFileName();

};

} // namespace PartGui

#endif // DlgPartImportIgesImp_H
