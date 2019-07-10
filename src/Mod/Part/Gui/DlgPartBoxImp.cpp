/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "DlgPartBoxImp.h"

using namespace PartGui;

/* 
 *  Constructs a DlgPartBox which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
DlgPartBoxImp::DlgPartBoxImp(QWidget* parent, Qt::WindowFlags fl)
  : Gui::LocationInterface<Ui_DlgPartBox>(parent, fl)
{
}

/*  
 *  Destroys the object and frees any allocated resources
 */
DlgPartBoxImp::~DlgPartBoxImp()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "moc_DlgPartBoxImp.cpp"
