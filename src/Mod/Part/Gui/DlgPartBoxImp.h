/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PARTGUI_DLGPARTBOXIMP_H
#define PARTGUI_DLGPARTBOXIMP_H

#include "ui_DlgPartBox.h"
#include "Gui/InputVector.h"

namespace PartGui {

class DlgPartBoxImp : public Gui::LocationInterface<Ui_DlgPartBox>
{
    Q_OBJECT

public:
    DlgPartBoxImp(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~DlgPartBoxImp();
};

} // namespace PartGui

#endif // PARTGUI_DLGPARTBOXIMP_H
