/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_TOOLBARMANAGER_H
#define GUI_TOOLBARMANAGER_H

#include "stdexport.h"
#include <string>
#include <QStringList>

class QAction;
class QToolBar;

namespace Gui {

class GuiExport ToolBarItem
{
public:
    ToolBarItem();
    ToolBarItem(ToolBarItem* item);
    ~ToolBarItem();

    void setCommand(const std::string&);
    std::string command() const;

    bool hasItems() const;
    ToolBarItem* findItem(const std::string&);
    ToolBarItem* copy() const;
    uint count() const;

    void appendItem(ToolBarItem* item);
    bool insertItem(ToolBarItem*, ToolBarItem* item);
    void removeItem(ToolBarItem* item);
    void clear();

    ToolBarItem& operator << (ToolBarItem* item);
    ToolBarItem& operator << (const std::string& command);
    QList<ToolBarItem*> getItems() const;

private:
    std::string _name;
    QList<ToolBarItem*> _items;
};

/**
 * The ToolBarManager class is responsible for the creation of toolbars and appending them
 * to the main window.
 * @see ToolBoxManager
 * @see MenuManager 
 * @author Werner Mayer
 */
class GuiExport ToolBarManager
{
public:
    /// The one and only instance.
    static ToolBarManager* getInstance();
    static void destruct();
    /** Sets up the toolbars of a given workbench. */
    void setup(ToolBarItem*);
    void saveState() const;
    void restoreState() const;
    void retranslate() const;

protected:
    void setup(ToolBarItem*, QToolBar*) const;
    /** Returns a list of all currently existing toolbars. */
    QList<QToolBar*> toolBars() const;
    QToolBar* findToolBar(const QList<QToolBar*>&, const QString&) const;
    QAction* findAction(const QList<QAction*>&, const QString&) const;
    ToolBarManager();
    ~ToolBarManager();

private:
    QStringList toolbarNames;
    static ToolBarManager* _instance;
};

} // namespace Gui


#endif // GUI_TOOLBARMANAGER_H 
