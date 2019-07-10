/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef IMPORT_WORKBENCH_H
#define IMPORT_WORKBENCH_H

#include "Gui/Workbench.h"

namespace ImportGui {

/**
 * @author Werner Mayer
 */
class Workbench : public Gui::StdWorkbench
{
    TYPESYSTEM_HEADER();

public:
    Workbench();
    virtual ~Workbench();

protected:
    Gui::ToolBarItem* setupToolBars() const;
    Gui::ToolBarItem* setupCommandBars() const;
};

} // namespace ImportGui


#endif // IMPORT_WORKBENCH_H 
