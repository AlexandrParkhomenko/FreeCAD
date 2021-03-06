/***************************************************************************
 *   Copyright (c) 2017 Stefan Tröger <stefantroeger@gmx.net>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include <QApplication>
#include <QMessageBox>

#include "App/Part.h"
#include "App/Document.h"
#include "Command.h"
#include "Application.h"
#include "Document.h"
#include "MDIView.h"
#include "ViewProviderDocumentObject.h"


using namespace Gui;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// Std_Part
//===========================================================================
DEF_STD_CMD_A(StdCmdPart);

StdCmdPart::StdCmdPart()
  : Command("Std_Part")
{
    sGroup        = QT_TR_NOOP("Structure");
    sMenuText     = QT_TR_NOOP("Create part");
    sToolTipText  = QT_TR_NOOP("Create a new part and make it active");
    sStatusTip    = sToolTipText;
    sPixmap       = "Geofeaturegroup";
}

void StdCmdPart::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    openCommand("Add a part");
    std::string FeatName = getUniqueObjectName("Part");

    std::string PartName;
    PartName = getUniqueObjectName("Part");
    doCommand(Doc,"App.activeDocument().Tip = App.activeDocument().addObject('App::Part','%s')",PartName.c_str());
    // TODO We really must set label ourselves? (2015-08-17, Fat-Zer)
    doCommand(Doc,"App.activeDocument().%s.Label = '%s'", PartName.c_str(),
            QObject::tr(PartName.c_str()).toUtf8().data());
    doCommand(Gui::Command::Gui, "Gui.activeView().setActiveObject('%s', App.activeDocument().%s)",
            PARTKEY, PartName.c_str());

    updateActive();
}

bool StdCmdPart::isActive(void)
{
    return hasActiveDocument();
}

//===========================================================================
// Std_Group
//===========================================================================
DEF_STD_CMD_A(StdCmdGroup);

StdCmdGroup::StdCmdGroup()
  : Command("Std_Group")
{
    sGroup        = QT_TR_NOOP("Structure");
    sMenuText     = QT_TR_NOOP("Create group");
    sToolTipText  = QT_TR_NOOP("Create a new group for ordering objects");
    sStatusTip    = sToolTipText;
    sPixmap       = "Group";
}

void StdCmdGroup::activated(int iMsg)
{
    Q_UNUSED(iMsg);

    openCommand("Add a group");

    std::string GroupName;
    GroupName = getUniqueObjectName("Group");
    QString label = QApplication::translate("Std_Group", "Group");
    doCommand(Doc,"App.activeDocument().Tip = App.activeDocument().addObject('App::DocumentObjectGroup','%s')",GroupName.c_str());
    doCommand(Doc,"App.activeDocument().%s.Label = '%s'", GroupName.c_str(),
              label.toUtf8().data());
    commitCommand();

    Gui::Document* gui = Application::Instance->activeDocument();
    App::Document* app = gui->getDocument();
    ViewProvider* vp = gui->getViewProvider(app->getActiveObject());
    if (vp && vp->getTypeId().isDerivedFrom(ViewProviderDocumentObject::getClassTypeId()))
        gui->signalScrollToObject(*static_cast<ViewProviderDocumentObject*>(vp));
}

bool StdCmdGroup::isActive(void)
{
    return hasActiveDocument();
}

namespace Gui {

void CreateStructureCommands(void)
{
    CommandManager &rcCmdMgr = Application::Instance->commandManager();

    rcCmdMgr.addCommand(new StdCmdPart());
    rcCmdMgr.addCommand(new StdCmdGroup());
}

} // namespace Gui
