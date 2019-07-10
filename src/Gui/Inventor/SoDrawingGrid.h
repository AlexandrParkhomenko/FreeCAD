/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_INVENTOR_SODRAWINGGRID_H
#define GUI_INVENTOR_SODRAWINGGRID_H

#include "stdexport.h"
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>

namespace Gui { namespace Inventor {

class GuiExport SoDrawingGrid : public SoShape {
    typedef SoShape inherited;

    SO_NODE_HEADER(SoDrawingGrid);

public:
    static void initClass();
    SoDrawingGrid();

public:
    virtual void GLRender(SoGLRenderAction *action);
    virtual void GLRenderBelowPath(SoGLRenderAction *action);
    virtual void GLRenderInPath(SoGLRenderAction *action);
    virtual void GLRenderOffPath(SoGLRenderAction *action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
    virtual void generatePrimitives(SoAction *action);

private:
    void renderGrid(SoGLRenderAction *action);
    // Force using the reference count mechanism.
    virtual ~SoDrawingGrid() {}
};

} // namespace Inventor

} // namespace Gui

#endif // GUI_INVENTOR_SODRAWINGGRID_H
