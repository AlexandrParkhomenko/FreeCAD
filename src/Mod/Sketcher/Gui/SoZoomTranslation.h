/***************************************************************************
 *                                                                         *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef SKETCHERGUI_SOZOOMTRANSLATION_H
#define SKETCHERGUI_SOZOOMTRANSLATION_H

#include "stdexport.h"
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoTransformation.h>

namespace SketcherGui {

class SketcherGuiExport SoZoomTranslation : public SoTranslation {
    typedef SoTranslation inherited;

    SO_NODE_HEADER(SoZoomTranslation);

public:
    static void initClass();
    SoZoomTranslation();
    SoSFVec3f abPos;

protected:
    virtual ~SoZoomTranslation() {};
    virtual void doAction(SoAction * action);
    virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);
    virtual void getMatrix(SoGetMatrixAction * action);
    virtual void GLRender(SoGLRenderAction *action);
    virtual void getBoundingBox(SoGetBoundingBoxAction * action);
    virtual void callback(SoCallbackAction * action);
    virtual void pick(SoPickAction * action);
    float getScaleFactor(SoAction * action) const;
};

}
#endif // SKETCHERGUI_SOZOOMTRANSLATION_H
