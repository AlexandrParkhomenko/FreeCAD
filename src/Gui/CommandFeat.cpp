/***************************************************************************
 *   Copyright (c) 2002 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "App/DocumentObject.h"

#include "Application.h"
#include "Command.h"
#include "Document.h"
#include "Selection.h"
#include "ViewProvider.h"
#include "ViewProviderDocumentObject.h"

using namespace Gui;



//===========================================================================
// Std_Recompute
//===========================================================================

DEF_STD_CMD(StdCmdFeatRecompute);

StdCmdFeatRecompute::StdCmdFeatRecompute()
  :Command("Std_Recompute")
{
    // setting the
    sGroup        = QT_TR_NOOP("File");
    sMenuText     = QT_TR_NOOP("&Recompute");
    sToolTipText  = QT_TR_NOOP("Recompute feature or document");
    sStatusTip    = QT_TR_NOOP("Recompute feature or document");
    sPixmap       = "view-refresh";
    sAccel        = "Ctrl+R";
}

void StdCmdFeatRecompute::activated(int iMsg)
{
    Q_UNUSED(iMsg); 
}

//===========================================================================
// Std_RandomColor
//===========================================================================

DEF_STD_CMD_A(StdCmdRandomColor);

StdCmdRandomColor::StdCmdRandomColor()
  :Command("Std_RandomColor")
{
    sGroup        = QT_TR_NOOP("File");
    sMenuText     = QT_TR_NOOP("Random color");
    sToolTipText  = QT_TR_NOOP("Random color");
    sStatusTip    = QT_TR_NOOP("Random color");
}

void StdCmdRandomColor::activated(int iMsg)
{
    Q_UNUSED(iMsg); 

    // get the complete selection
    std::vector<SelectionSingleton::SelObj> sel = Selection().getCompleteSelection();
    for (std::vector<SelectionSingleton::SelObj>::iterator it = sel.begin(); it != sel.end(); ++it) {
        float fMax = (float)RAND_MAX;
        float fRed = (float)rand()/fMax;
        float fGrn = (float)rand()/fMax;
        float fBlu = (float)rand()/fMax;

        ViewProvider* view = Application::Instance->getDocument(it->pDoc)->getViewProvider(it->pObject);
        App::Property* color = view->getPropertyByName("ShapeColor");
        if (color && color->getTypeId() == App::PropertyColor::getClassTypeId()) {
            // get the view provider of the selected object and set the shape color
            doCommand(Gui, "Gui.getDocument(\"%s\").getObject(\"%s\").ShapeColor=(%.2f,%.2f,%.2f)"
                         , it->DocName, it->FeatName, fRed, fGrn, fBlu);
        }
    }
}

bool StdCmdRandomColor::isActive(void)
{
    return (Gui::Selection().size() != 0);
}


namespace Gui {

void CreateFeatCommands(void)
{
    CommandManager &rcCmdMgr = Application::Instance->commandManager();

    rcCmdMgr.addCommand(new StdCmdFeatRecompute());
    rcCmdMgr.addCommand(new StdCmdRandomColor());
}

} // namespace Gui
