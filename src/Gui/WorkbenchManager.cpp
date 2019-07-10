/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <sstream>

#include "Base/Console.h"
#include "Base/Exception.h"
#include "WorkbenchManager.h"
#include "Workbench.h"
#include "MenuManager.h"
#include "ToolBarManager.h"
#include "ToolBoxManager.h"
#include "DockWindowManager.h"
#include "MainWindow.h"

using namespace Gui;

WorkbenchManager* WorkbenchManager::_instance = 0;

WorkbenchManager* WorkbenchManager::instance()
{
    if (_instance == 0)
        _instance = new WorkbenchManager;
    return _instance;
}

void WorkbenchManager::destruct()
{
    delete _instance;
    _instance = 0;
}

WorkbenchManager::WorkbenchManager() : _activeWorkbench(0)
{
}

WorkbenchManager::~WorkbenchManager()
{
    for (std::map<std::string, Workbench*>::iterator it = _workbenches.begin(); it != _workbenches.end(); ++it) {
        Workbench* wb = it->second;
        delete wb;
    }

    MenuManager::destruct();
    ToolBarManager::destruct();
    //ToolBoxManager::destruct();
    DockWindowManager::destruct();
}

Workbench* WorkbenchManager::createWorkbench (const std::string& name, const std::string& className)
{
    Workbench* wb = getWorkbench(name);

    if (!wb) {
        // try to create an instance now
        Base::BaseClass* base = static_cast<Base::BaseClass*>
            (Base::Type::createInstanceByName(className.c_str(),false));
        if (base) {
            if (!base->getTypeId().isDerivedFrom(Gui::Workbench::getClassTypeId())) {
                delete base;
                std::stringstream str;
                str << "'" << className << "' not a workbench type" << std::ends;
                throw Base::TypeError(str.str());
            }

            wb = static_cast<Workbench*>(base);
            wb->setName(name);
            _workbenches[name] = wb;
        }
        else
            Base::Console().Log("WorkbenchManager::createWorkbench(): Can not create "
                "Workbench instance with type: %s\n",className.c_str());
    }

    return wb;
}

void WorkbenchManager::removeWorkbench(const std::string& name)
{
    std::map<std::string, Workbench*>::iterator it = _workbenches.find(name);
    if (it != _workbenches.end()) {
        Workbench* wb = it->second;
        _workbenches.erase(it);
        if (_activeWorkbench == wb)
            _activeWorkbench = 0;
        delete wb;
    }
}

Workbench* WorkbenchManager::getWorkbench (const std::string& name) const
{
    Workbench* wb=0;

    std::map<std::string, Workbench*>::const_iterator it = _workbenches.find(name);
    if (it != _workbenches.end()) {
        // returns the already created object
        wb = it->second;
    }

    return wb;
}

bool WorkbenchManager::activate(const std::string& name, const std::string& className)
{
    Workbench* wb = createWorkbench(name, className);
    if (wb) {
        _activeWorkbench = wb;
        wb->activate();
        return true;
    }
  
    return false;
}

Workbench* WorkbenchManager::active() const
{
    return _activeWorkbench;
}

std::list<std::string> WorkbenchManager::workbenches() const
{
    std::list<std::string> wb;
    for (std::map<std::string, Workbench*>::const_iterator it = _workbenches.begin(); it != _workbenches.end(); ++it)
        wb.push_back(it->first);
    return wb;
}
