
/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "DlgPointsReadImp.h"

using namespace PointsGui;



DlgPointsReadImp::DlgPointsReadImp(const char *FileName, QWidget* parent,  Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
  _FileName = FileName;
}

/*  
 *  Destroys the object and frees any allocated resources
 */
DlgPointsReadImp::~DlgPointsReadImp()
{
    // no need to delete child widgets, Qt does it all for us
}



#include "moc_DlgPointsReadImp.cpp"
