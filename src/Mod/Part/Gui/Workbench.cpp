/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <qobject.h>

#include "Workbench.h"
#include "Gui/MenuManager.h"
#include "Gui/ToolBarManager.h"

using namespace PartGui;

#if 0 // needed for Qt's lupdate utility
    qApp->translate("Workbench", "&Part");
    qApp->translate("Workbench", "&Simple");
    qApp->translate("Workbench", "&Parametric");
    qApp->translate("Workbench", "Solids");
    qApp->translate("Workbench", "Part tools");
    qApp->translate("Workbench", "Boolean");
    qApp->translate("Workbench", "Primitives");
    qApp->translate("Workbench", "Join");
    qApp->translate("Workbench", "Split");
    qApp->translate("Workbench", "Compound");
#endif

/// @namespace PartGui @class Workbench
TYPESYSTEM_SOURCE(PartGui::Workbench, Gui::StdWorkbench)

Workbench::Workbench()
{
}

Workbench::~Workbench()
{
}

Gui::MenuItem* Workbench::setupMenuBar() const
{
    Gui::MenuItem* root = StdWorkbench::setupMenuBar();
    Gui::MenuItem* item = root->findItem("&Windows");

    Gui::MenuItem* prim = new Gui::MenuItem;
    prim->setCommand("Primitives");
    *prim << "Part_Box"
          << "Part_Cylinder"
          << "Part_Sphere"
          << "Part_Cone"
          << "Part_Torus"
          << "Separator"
          << "Part_MakeTube";

    Gui::MenuItem* bop = new Gui::MenuItem;
    bop->setCommand("Boolean");
    *bop << "Part_Boolean"
         << "Part_Cut"
         << "Part_Fuse"
         << "Part_Common";

    Gui::MenuItem* join = new Gui::MenuItem;
    join->setCommand("Join");
    *join << "Part_JoinConnect"
          << "Part_JoinEmbed"
          << "Part_JoinCutout";

    Gui::MenuItem* split = new Gui::MenuItem;
    split->setCommand("Split");
    *split << "Part_BooleanFragments"
           << "Part_SliceApart"
           << "Part_Slice"
           << "Part_XOR";

    Gui::MenuItem* compound = new Gui::MenuItem;
    compound->setCommand("Compound");
    *compound << "Part_Compound"
              << "Part_ExplodeCompound"
              << "Part_CompoundFilter";

    Gui::MenuItem* part = new Gui::MenuItem;
    root->insertItem(item, part);
    part->setCommand("&Part");
    *part << "Part_Import"
          << "Part_Export"
          << "Separator"
          << "Part_BoxSelection"
          << "Separator";
    *part << prim
          << "Part_Primitives"
          << "Part_Builder"
          << "Separator"
          << "Part_ShapeFromMesh"
          << "Part_MakeSolid"
          << "Part_ReverseShape"
          << "Part_SimpleCopy"
          << "Part_RefineShape"
          << "Part_CheckGeometry"
          << "Part_Defeaturing"
          << "Separator"
          << bop << join << split << compound
          << "Separator"
          << "Part_Section"
          << "Part_CrossSections"
          << "Part_MakeFace"
          << "Part_Extrude"
          << "Part_Revolve"
          << "Part_Mirror"
          << "Part_Fillet"
          << "Part_Chamfer"
          << "Part_RuledSurface"
          << "Part_Loft"
          << "Part_Sweep"
          << "Part_Offset"
          << "Part_Offset2D"
          << "Part_Thickness"
          << "Separator"
          << "Part_EditAttachment";

    Gui::MenuItem* measure = new Gui::MenuItem;
    root->insertItem(item,measure);
    measure->setCommand("Measure");
    *measure << "Part_Measure_Linear"
             << "Part_Measure_Angular"
             << "Separator"
             << "Part_Measure_Clear_All"
             << "Part_Measure_Toggle_All"
             << "Part_Measure_Toggle_3d"
             << "Part_Measure_Toggle_Delta";

    // leave this for 0.14 until #0000477 is fixed
#if 0
    Gui::MenuItem* view = root->findItem("&View");
    if (view) {
        Gui::MenuItem* appr = view->findItem("Std_RandomColor");
        appr = view->afterItem(appr);
        Gui::MenuItem* face = new Gui::MenuItem();
        face->setCommand("Part_ColorPerFace");
        view->insertItem(appr, face);
    }
#endif

    return root;
}

Gui::ToolBarItem* Workbench::setupToolBars() const
{
    Gui::ToolBarItem* root = StdWorkbench::setupToolBars();

    Gui::ToolBarItem* solids = new Gui::ToolBarItem(root);
    solids->setCommand("Solids");
    *solids << "Part_Box"
            << "Part_Cylinder"
            << "Part_Sphere"
            << "Part_Cone"
            << "Part_Torus"
            << "Part_Primitives"
            << "Part_Builder";

    Gui::ToolBarItem* tool = new Gui::ToolBarItem(root);
    tool->setCommand("Part tools");
    *tool << "Part_Extrude"
          << "Part_Revolve"
          << "Part_Mirror"
          << "Part_Fillet"
          << "Part_Chamfer"
          << "Part_RuledSurface"
          << "Part_Loft"
          << "Part_Sweep"
          << "Part_CompOffset"
          << "Part_Thickness";

    Gui::ToolBarItem* boolop = new Gui::ToolBarItem(root);
    boolop->setCommand("Boolean");
    *boolop << "Part_CompCompoundTools"
            << "Part_Boolean"
            << "Part_Cut"
            << "Part_Fuse"
            << "Part_Common"
            << "Part_CompJoinFeatures"
            << "Part_CompSplitFeatures"
            << "Part_CheckGeometry"
            << "Part_Defeaturing"
            << "Part_Section"
            << "Part_CrossSections";

    Gui::ToolBarItem* measure = new Gui::ToolBarItem(root);
    measure->setCommand("Measure");
    *measure << "Part_Measure_Linear"
             << "Part_Measure_Angular"
             << "Separator"
             << "Part_Measure_Clear_All"
             << "Part_Measure_Toggle_All"
             << "Part_Measure_Toggle_3d"
             << "Part_Measure_Toggle_Delta";

    return root;
}

Gui::ToolBarItem* Workbench::setupCommandBars() const
{
    // Part tools
    Gui::ToolBarItem* root = new Gui::ToolBarItem;
    return root;
}
