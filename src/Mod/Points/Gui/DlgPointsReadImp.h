/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef POINTSGUI_DLGREADPOINTS_H
#define POINTSGUI_DLGREADPOINTS_H

#include <string>
#include "ui_DlgPointsRead.h"

namespace PointsGui {

/** The points read dialog
 */
class DlgPointsReadImp : public QDialog, public Ui_DlgPointsRead
{ 
  Q_OBJECT

public:
  DlgPointsReadImp(const char *FileName, QWidget* parent = 0, Qt::WindowFlags fl = 0 );
  ~DlgPointsReadImp();

private:
  std::string _FileName;
};

} // namespace PointsGui

#endif // POINTSGUI_DLGREADPOINTS_H
