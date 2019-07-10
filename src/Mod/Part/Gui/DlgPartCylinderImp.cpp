/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "DlgPartCylinderImp.h"

using namespace PartGui;

/* 
 *  Constructs a DlgPartCylinder which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgPartCylinderImp::DlgPartCylinderImp(QWidget* parent, Qt::WindowFlags fl)
  : Gui::LocationInterface<Ui_DlgPartCylinder>(parent, fl)
{
}

/*  
 *  Destroys the object and frees any allocated resources
 */
DlgPartCylinderImp::~DlgPartCylinderImp()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "moc_DlgPartCylinderImp.cpp"
