/***************************************************************************
 *   (c) 2011 Luke Parry                                                   *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#include "stdexport.h"
#ifndef GUI_SOAUTOZOOMTRANSLATION_H
#define GUI_SOAUTOZOOMTRANSLATION_H

#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoTransformation.h>

namespace Gui {

class GuiExport SoAutoZoomTranslation : public SoTransformation  {
    typedef SoTransformation  inherited;

    SO_NODE_HEADER(SoAutoZoomTranslation);

public:
    static void initClass();
    SoAutoZoomTranslation();
    //SoSFVec3f abPos;

protected:
    virtual ~SoAutoZoomTranslation() {};
    virtual void doAction(SoAction * action);
    virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);
    virtual void getMatrix(SoGetMatrixAction * action);
    virtual void GLRender(SoGLRenderAction *action);
    virtual void getBoundingBox(SoGetBoundingBoxAction * action);
    virtual void callback(SoCallbackAction * action);
    virtual void pick(SoPickAction * action);
    float getScaleFactor(SoAction*) const;

private:
    //void setAutoScale(void);
};

}
#endif // GUI_SOAUTOZOOMTRANSLATION_H
