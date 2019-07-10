/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef MESHGUI_SOPOLYGON_H
#define MESHGUI_SOPOLYGON_H

#include "stdexport.h"
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/elements/SoReplacedElement.h>

namespace MeshGui {

class MeshGuiExport SoPolygon : public SoShape {
    typedef SoShape inherited;

    SO_NODE_HEADER(SoPolygon);

public:
    static void initClass();
    SoPolygon();

    SoSFInt32 startIndex;
    SoSFInt32 numVertices;
    SoSFBool  highlight;
    SoSFBool  render;

protected:
    virtual ~SoPolygon() {};
    virtual void GLRender(SoGLRenderAction *action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
    virtual void rayPick (SoRayPickAction *action);
    virtual void generatePrimitives(SoAction *action);

private:
    void drawPolygon(const SbVec3f *,int32_t) const;
};

} // namespace MeshGui


#endif // MESHGUI_SOPOLYGON_H

