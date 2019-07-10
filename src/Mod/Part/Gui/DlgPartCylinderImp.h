/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef PARTGUI_DLGPARTCYLINDERIMP_H
#define PARTGUI_DLGPARTCYLINDERIMP_H

#include "ui_DlgPartCylinder.h"
#include "Gui/InputVector.h"

namespace PartGui {

class DlgPartCylinderImp : public Gui::LocationInterface<Ui_DlgPartCylinder>
{
    Q_OBJECT

public:
    DlgPartCylinderImp(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgPartCylinderImp();
};

} // namespace PartGui

#endif // PARTGUI_DLGPARTCYLINDERIMP_H
