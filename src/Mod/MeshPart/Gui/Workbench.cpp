/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <qobject.h>

#include "Workbench.h"
#include "Gui/ToolBarManager.h"

using namespace MeshPartGui;

#if 0 // needed for Qt's lupdate utility
    qApp->translate("Workbench", "MeshPart");
#endif

/// @namespace MeshPartGui @class Workbench
TYPESYSTEM_SOURCE(MeshPartGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
}

Workbench::~Workbench()
{
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();
    Gui::ToolBarItem* part = new Gui::ToolBarItem(root);
    part->setCommand("MeshPart");
    *part << "MeshPart_Mesher";
     return root;
}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    // Part tools
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    return root;
}

