/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef PARTGUI_SOFCSHAPEOBJECT_H
#define PARTGUI_SOFCSHAPEOBJECT_H

#include "stdexport.h"
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/elements/SoReplacedElement.h>

namespace PartGui {

class PartGuiExport SoFCControlPoints : public SoShape {
    typedef SoShape inherited;

    SO_NODE_HEADER(SoFCControlPoints);

public:
    static void initClass();
    SoFCControlPoints();

    SoSFUInt32 numPolesU;
    SoSFUInt32 numPolesV;
    SoSFUInt32 numKnotsU;
    SoSFUInt32 numKnotsV;
    SoSFColor  lineColor;

protected:
    virtual ~SoFCControlPoints() {};
    virtual void GLRender(SoGLRenderAction *action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
    virtual void generatePrimitives(SoAction *action);

private:
    void drawControlPoints(const SbVec3f *,int32_t) const;
};

} // namespace PartGui


#endif // PARTGUI_SOFCSHAPEOBJECT_H

