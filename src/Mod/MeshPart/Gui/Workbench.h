/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef MESHPARTGUI_WORKBENCH_H
#define MESHPARTGUI_WORKBENCH_H

#include "stdexport.h"
#include "Gui/Workbench.h"

namespace MeshPartGui {

/**
 * @author Werner Mayer
 */
class MeshPartGuiExport Workbench : public Gui::StdWorkbench
{
    TYPESYSTEM_HEADER();

public:
  Workbench();
  virtual ~Workbench();

protected:
  Gui::ToolBarItem* setupToolBars() const;
  Gui::ToolBarItem* setupCommandBars() const;
};

} // namespace MeshPartGui


#endif // MESHPARTGUI_WORKBENCH_H 
