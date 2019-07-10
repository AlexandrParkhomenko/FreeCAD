/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef PARTGUI_SOBREPPOINTSET_H
#define PARTGUI_SOBREPPOINTSET_H

#include "stdexport.h"
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <vector>

class SoCoordinateElement;
class SoGLCoordinateElement;
class SoTextureCoordinateBundle;

namespace PartGui {

class PartGuiExport SoBrepPointSet : public SoPointSet {
    typedef SoPointSet inherited;

    SO_NODE_HEADER(SoBrepPointSet);

public:
    static void initClass();
    SoBrepPointSet();

    SoSFInt32 highlightIndex;
    SoMFInt32 selectionIndex;

protected:
    virtual ~SoBrepPointSet() {};
    virtual void GLRender(SoGLRenderAction *action);
    virtual void GLRenderBelowPath(SoGLRenderAction * action);
    virtual void doAction(SoAction* action); 

private:
    void renderShape(const SoGLCoordinateElement * const vertexlist,
                     const int32_t *vertexindices,
                     int num_vertexindices);
    void renderHighlight(SoGLRenderAction *action);
    void renderSelection(SoGLRenderAction *action);
    bool validIndexes(const SoCoordinateElement*, int32_t, const int32_t *, int) const;

private:
    SbColor selectionColor;
    SbColor highlightColor;
    SoColorPacker colorpacker;
};

} // namespace PartGui


#endif // PARTGUI_SOBREPPOINTSET_H

