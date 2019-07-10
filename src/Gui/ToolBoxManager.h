/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_TOOLBOXMANAGER_H
#define GUI_TOOLBOXMANAGER_H

#include "stdexport.h"
namespace Gui {

class ToolBarItem;


namespace DockWnd 
{ class ToolBox;}

/**
 * The ToolBoxManager class is responsible for the creation of command bars and appending them
 * to the toolbox window.
 * @see ToolBarManager
 * @see MenuManager 
 * @author Werner Mayer
 */
class GuiExport ToolBoxManager
{
public:
    /// The one and only instance.
    static ToolBoxManager* getInstance();
    static void destruct();
    /** Sets up the command bars of a given workbench. */
    void setup(ToolBarItem*) const;
    void setToolBox(DockWnd::ToolBox*);
    void retranslate() const;

protected:
    ToolBoxManager();
    ~ToolBoxManager();

private:
    DockWnd::ToolBox* _toolBox;
    static ToolBoxManager* _instance;
};

} // namespace Gui


#endif // GUI_TOOLBOXMANAGER_H 
