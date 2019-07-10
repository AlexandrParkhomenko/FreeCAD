/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <qobject.h>

#include "Workbench.h"
#include "Gui/ToolBarManager.h"
#include "Gui/MenuManager.h"

using namespace PointsGui;

#if 0 // needed for Qt's lupdate utility
    qApp->translate("Workbench", "Points tools");
    qApp->translate("Workbench", "&Points");
#endif

/// @namespace PointsGui @class Workbench
TYPESYSTEM_SOURCE(PointsGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
}

Workbench::~Workbench()
{
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();
    Gui::ToolBarItem* pnt = new Gui::ToolBarItem( root );
    pnt->setCommand("Points tools");
    *pnt << "Points_Import" << "Points_Export" << "Separator" << "Points_PolyCut";
    return root;
}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    // point tools
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    Gui::ToolBarItem* pnt = new Gui::ToolBarItem( root );
    pnt->setCommand("Points tools");
    *pnt << "Points_Import" << "Points_Export";
    return root;
}

Gui::MenuItem* Workbench::setupMenuBar() const
{
    Gui::MenuItem* root = StdWorkbench::setupMenuBar();
    Gui::MenuItem* item = root->findItem("&Windows");
    Gui::MenuItem* pnts = new Gui::MenuItem;
    root->insertItem(item, pnts);
 
    pnts->setCommand("&Points");
    *pnts << "Points_Convert" << "Separator" << "Points_Import"
          << "Points_Export" << "Separator" << "Points_PolyCut"
          << "Points_Merge";
    return root;
}

