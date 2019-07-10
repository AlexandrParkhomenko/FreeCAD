/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_WORKBENCH_H
#define PART_WORKBENCH_H

#include "stdexport.h"
#include "Gui/Workbench.h"

namespace PartGui {

/**
 * @author Werner Mayer
 */
class PartGuiExport Workbench : public Gui::StdWorkbench
{
    TYPESYSTEM_HEADER();

public:
  Workbench();
  virtual ~Workbench();

protected:
  Gui::MenuItem* setupMenuBar() const;
  Gui::ToolBarItem* setupToolBars() const;
  Gui::ToolBarItem* setupCommandBars() const;
};

} // namespace PartGui


#endif // PART_WORKBENCH_H 
