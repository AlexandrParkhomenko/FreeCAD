/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef IMAGE_WORKBENCH_H
#define IMAGE_WORKBENCH_H

#include "stdexport.h"
#include "Gui/Workbench.h"
#include "Gui/MenuManager.h"
#include "Gui/ToolBarManager.h"

namespace SketcherGui {

/**
 * @author Werner Mayer
 */
class SketcherGuiExport Workbench : public Gui::StdWorkbench
{
    TYPESYSTEM_HEADER();

public:
    Workbench();
    virtual ~Workbench();

protected:
    Gui::MenuItem* setupMenuBar() const;
    Gui::ToolBarItem* setupToolBars() const;
    Gui::ToolBarItem* setupCommandBars() const;
};




SketcherGuiExport void addSketcherWorkbenchConstraints( Gui::MenuItem& cons );
SketcherGuiExport void addSketcherWorkbenchTools( Gui::MenuItem& consaccel );
SketcherGuiExport void addSketcherWorkbenchBSplines( Gui::MenuItem& bspline );
SketcherGuiExport void addSketcherWorkbenchVirtualSpace( Gui::MenuItem& virtualspace );
SketcherGuiExport void addSketcherWorkbenchSketchActions( Gui::MenuItem& sketch );
SketcherGuiExport void addSketcherWorkbenchGeometries( Gui::MenuItem& geom );

SketcherGuiExport void addSketcherWorkbenchConstraints( Gui::ToolBarItem& cons );
SketcherGuiExport void addSketcherWorkbenchTools( Gui::ToolBarItem& consaccel );
SketcherGuiExport void addSketcherWorkbenchBSplines( Gui::ToolBarItem& bspline );
SketcherGuiExport void addSketcherWorkbenchVirtualSpace( Gui::ToolBarItem& virtualspace );
SketcherGuiExport void addSketcherWorkbenchSketchActions( Gui::ToolBarItem& sketch );
SketcherGuiExport void addSketcherWorkbenchGeometries( Gui::ToolBarItem& geom );

} // namespace SketcherGui


#endif // IMAGE_WORKBENCH_H 
