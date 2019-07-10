/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESH_WORKBENCH_H
#define MESH_WORKBENCH_H

#include "stdexport.h"
#include "Gui/Workbench.h"

namespace MeshGui {

/**
 * @author Werner Mayer
 */
class MeshGuiExport Workbench : public Gui::StdWorkbench
{
    TYPESYSTEM_HEADER();

public:
  Workbench();
  virtual ~Workbench();

  void activated();
  void deactivated();
  void setupContextMenu(const char* recipient, Gui::MenuItem*) const;

protected:
  Gui::MenuItem* setupMenuBar() const;
  Gui::ToolBarItem* setupToolBars() const;
  Gui::ToolBarItem* setupCommandBars() const;
};

} // namespace MeshGui


#endif // MESH_WORKBENCH_H 
