/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <QApplication>
# include <QDir>
# include <QFileInfo>
# include <QLineEdit>

#include "Gui/Application.h"
#include "Gui/Command.h"
#include "Gui/MainWindow.h"

//===========================================================================
// Part_Cylinder
//===========================================================================
DEF_STD_CMD_A(CmdPartCylinder);

CmdPartCylinder::CmdPartCylinder()
  : Command("Part_Cylinder")
{
    sAppModule    = "Part";
    sGroup        = QT_TR_NOOP("Part");
    sMenuText     = QT_TR_NOOP("Cylinder");
    sToolTipText  = QT_TR_NOOP("Create a Cylinder");
    sStatusTip    = sToolTipText;
    sPixmap       = "Part_Cylinder";
}

void CmdPartCylinder::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    QString cmd;
    cmd = qApp->translate("CmdPartCylinder","Cylinder");
    openCommand((const char*)cmd.toUtf8());

    runCommand(Doc,"App.ActiveDocument.addObject(\"Part::Cylinder\",\"Cylinder\")");
    cmd = QString("App.ActiveDocument.ActiveObject.Label = \"%1\"")
        .arg(qApp->translate("CmdPartCylinder","Cylinder"));
    runCommand(Doc,cmd.toUtf8());
    commitCommand();
    updateActive();
    runCommand(Gui, "Gui.SendMsgToActiveView(\"ViewFit\")");
}

bool CmdPartCylinder::isActive(void)
{
    if (getActiveGuiDocument())
        return true;
    else
        return false;
}

//===========================================================================
// Part_Box
//===========================================================================
DEF_STD_CMD_A(CmdPartBox);

CmdPartBox::CmdPartBox()
  : Command("Part_Box")
{
    sAppModule    = "Part";
    sGroup        = QT_TR_NOOP("Part");
    sMenuText     = QT_TR_NOOP("Cube");
    sToolTipText  = QT_TR_NOOP("Create a cube solid");
    sStatusTip    = sToolTipText;
    sPixmap       = "Part_Box";
}

void CmdPartBox::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    QString cmd;
    cmd = qApp->translate("CmdPartBox","Cube");
    openCommand((const char*)cmd.toUtf8());

    runCommand(Doc,"App.ActiveDocument.addObject(\"Part::Box\",\"Box\")");
    cmd = QString("App.ActiveDocument.ActiveObject.Label = \"%1\"")
        .arg(qApp->translate("CmdPartBox","Cube"));
    runCommand(Doc,cmd.toUtf8());
    commitCommand();
    updateActive();
    runCommand(Gui, "Gui.SendMsgToActiveView(\"ViewFit\")");
}

bool CmdPartBox::isActive(void)
{
    if (getActiveGuiDocument())
        return true;
    else
        return false;
}

//===========================================================================
// Part_Sphere
//===========================================================================
DEF_STD_CMD_A(CmdPartSphere);

CmdPartSphere::CmdPartSphere()
  : Command("Part_Sphere")
{
    sAppModule    = "Part";
    sGroup        = QT_TR_NOOP("Part");
    sMenuText     = QT_TR_NOOP("Sphere");
    sToolTipText  = QT_TR_NOOP("Create a sphere solid");
    sStatusTip    = sToolTipText;
    sPixmap       = "Part_Sphere";
}

void CmdPartSphere::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    QString cmd;
    cmd = qApp->translate("CmdPartSphere","Sphere");
    openCommand((const char*)cmd.toUtf8());

    runCommand(Doc,"App.ActiveDocument.addObject(\"Part::Sphere\",\"Sphere\")");
    cmd = QString("App.ActiveDocument.ActiveObject.Label = \"%1\"")
        .arg(qApp->translate("CmdPartSphere","Sphere"));
    runCommand(Doc,cmd.toUtf8());
    commitCommand();
    updateActive();
    runCommand(Gui, "Gui.SendMsgToActiveView(\"ViewFit\")");
}

bool CmdPartSphere::isActive(void)
{
    if (getActiveGuiDocument())
        return true;
    else
        return false;
}

//===========================================================================
// Part_Cone
//===========================================================================
DEF_STD_CMD_A(CmdPartCone);

CmdPartCone::CmdPartCone()
  : Command("Part_Cone")
{
    sAppModule    = "Part";
    sGroup        = QT_TR_NOOP("Part");
    sMenuText     = QT_TR_NOOP("Cone");
    sToolTipText  = QT_TR_NOOP("Create a cone solid");
    sStatusTip    = sToolTipText;
    sPixmap       = "Part_Cone";
}

void CmdPartCone::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    QString cmd;
    cmd = qApp->translate("CmdPartCone","Cone");
    openCommand((const char*)cmd.toUtf8());

    runCommand(Doc,"App.ActiveDocument.addObject(\"Part::Cone\",\"Cone\")");
    cmd = QString("App.ActiveDocument.ActiveObject.Label = \"%1\"")
        .arg(qApp->translate("CmdPartCone","Cone"));
    runCommand(Doc,cmd.toUtf8());
    commitCommand();
    updateActive();
    runCommand(Gui, "Gui.SendMsgToActiveView(\"ViewFit\")");
}

bool CmdPartCone::isActive(void)
{
    if (getActiveGuiDocument())
        return true;
    else
        return false;
}

//===========================================================================
// Part_Torus
//===========================================================================
DEF_STD_CMD_A(CmdPartTorus);

CmdPartTorus::CmdPartTorus()
  : Command("Part_Torus")
{
    sAppModule    = "Part";
    sGroup        = QT_TR_NOOP("Part");
    sMenuText     = QT_TR_NOOP("Torus");
    sToolTipText  = QT_TR_NOOP("Create a torus solid");
    sStatusTip    = sToolTipText;
    sPixmap       = "Part_Torus";
}

void CmdPartTorus::activated(int iMsg)
{
    Q_UNUSED(iMsg);
    QString cmd;
    cmd = qApp->translate("CmdPartTorus","Torus");
    openCommand((const char*)cmd.toUtf8());

    runCommand(Doc,"App.ActiveDocument.addObject(\"Part::Torus\",\"Torus\")");
    cmd = QString("App.ActiveDocument.ActiveObject.Label = \"%1\"")
        .arg(qApp->translate("CmdPartTorus","Torus"));
    runCommand(Doc,cmd.toUtf8());
    commitCommand();
    updateActive();
    runCommand(Gui, "Gui.SendMsgToActiveView(\"ViewFit\")");
}

bool CmdPartTorus::isActive(void)
{
    if (getActiveGuiDocument())
        return true;
    else
        return false;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CreateParamPartCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdPartCylinder());
    rcCmdMgr.addCommand(new CmdPartBox());
    rcCmdMgr.addCommand(new CmdPartSphere());
    rcCmdMgr.addCommand(new CmdPartCone());
    rcCmdMgr.addCommand(new CmdPartTorus());
}
