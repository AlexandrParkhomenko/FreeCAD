/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef PARTGUI_SOBREPEDGESET_H
#define PARTGUI_SOBREPEDGESET_H

#include "stdexport.h"
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <vector>

class SoCoordinateElement;
class SoGLCoordinateElement;
class SoTextureCoordinateBundle;

namespace PartGui {

class PartGuiExport SoBrepEdgeSet : public SoIndexedLineSet {
    typedef SoIndexedLineSet inherited;

    SO_NODE_HEADER(SoBrepEdgeSet);

public:
    static void initClass();
    SoBrepEdgeSet();

    SoSFInt32 highlightIndex;
    SoMFInt32 selectionIndex;

protected:
    virtual ~SoBrepEdgeSet() {};
    virtual void GLRender(SoGLRenderAction *action);
    virtual void GLRenderBelowPath(SoGLRenderAction * action);
    virtual void doAction(SoAction* action); 
    virtual SoDetail * createLineSegmentDetail(
        SoRayPickAction *action,
        const SoPrimitiveVertex *v1,
        const SoPrimitiveVertex *v2,
        SoPickedPoint *pp);
private:
    void renderShape(const SoGLCoordinateElement * const vertexlist,
                     const int32_t *vertexindices,
                     int num_vertexindices);
    void renderHighlight(SoGLRenderAction *action);
    void renderSelection(SoGLRenderAction *action);
    bool validIndexes(const SoCoordinateElement*, const std::vector<int32_t>&) const;

private:
    std::vector<int32_t> hl, sl;
    SbColor selectionColor;
    SbColor highlightColor;
    //#0000834: Minor preselection color bug
    //To solve this we need a separate color packer for highlighting and selection
    SoColorPacker colorpacker1;
    SoColorPacker colorpacker2;
};

} // namespace PartGui


#endif // PARTGUI_SOBREPEDGESET_H

