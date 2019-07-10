/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef POINTS_WORKBENCH_H
#define POINTS_WORKBENCH_H

#include "stdexport.h"
#include "Gui/Workbench.h"

namespace PointsGui {

/**
 * @author Werner Mayer
 */
class PointsGuiExport Workbench : public Gui::StdWorkbench
{
    TYPESYSTEM_HEADER();

public:
  Workbench();
  virtual ~Workbench();

protected:
  Gui::ToolBarItem* setupToolBars() const;
  Gui::ToolBarItem* setupCommandBars() const;
  Gui::MenuItem* setupMenuBar() const;
};

} // namespace PointsGui


#endif // POINTS_WORKBENCH_H 
