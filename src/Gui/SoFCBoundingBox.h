/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef COIN_SOFCBOUNDINGBOX_H
#define COIN_SOFCBOUNDINGBOX_H

#include "stdexport.h"
#include <Inventor/SbLinear.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoText2.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFBool.h>

namespace Gui {

/**
 * A subclass of SoShape used to create an axis aligned wire frame box based
 * on the minBounds and maxBounds fields.  The class also has a field which
 * can be toggled on or off for displaying text coordinate labels at the
 * vertices of the box. 
 * @note Original source are taken from http://www.wheatchex.com/projects/openinventor/bbox/BoundingBox.h and
 * http://www.wheatchex.com/projects/openinventor/bbox/BoundingBox.cpp
 * @date November 12th, 2001
 * @author Josh Grant
 */
class GuiExport SoFCBoundingBox : public SoShape {
    typedef SoShape inherited;

    SO_NODE_HEADER(Gui::SoFCBoundingBox);

public:
    static void initClass();
    static void finish();

public:
    SoFCBoundingBox();
    SoSFVec3f minBounds; /**< minimum box coordinates */
    SoSFVec3f maxBounds; /**< maximum box coordinates */
    SoSFBool coordsOn; /**< If true, the coordinates are displayed at each vertex */
    SoSFBool dimensionsOn; /**< If true, the dimensions are displayed in x,y and z direction */


protected:
    virtual ~SoFCBoundingBox();
    virtual void GLRender(SoGLRenderAction *action);
    virtual void generatePrimitives (SoAction *action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

private:
    SoSeparator        *root, *textSep, *dimSep;
    SoCoordinate3      *bboxCoords;
    SoIndexedLineSet   *bboxLines;
};

/**
 * This is a special group node which must be defined to ignore bounding box actions.
 * @author Werner Mayer
 */
class GuiExport SoSkipBoundingGroup : public SoGroup {
    typedef SoGroup inherited;

    SO_NODE_HEADER(Gui::SoSkipBoundingGroup);

public:
    static void initClass(void);
    static void finish(void);
    SoSkipBoundingGroup(void);

    enum Modes {
        INCLUDE_BBOX, EXCLUDE_BBOX
    };
    
    SoSFEnum mode;

    virtual void getBoundingBox(SoGetBoundingBoxAction *action);

protected:
    virtual ~SoSkipBoundingGroup();
};

} // namespace Gui


#endif //COIN_SOFCBOUNDINGBOX_H
