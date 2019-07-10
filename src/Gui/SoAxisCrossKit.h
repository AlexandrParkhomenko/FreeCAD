/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_SOSHAPESCALE_H
#define GUI_SOSHAPESCALE_H

#include "stdexport.h"
#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFVec3f.h>

class SbViewport;
class SoState;
class SbColor;
class SbVec2s;

namespace Gui {
class GuiExport SoShapeScale : public SoBaseKit {
    typedef SoBaseKit inherited;

    SO_KIT_HEADER(SoShapeScale);

    SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
    SO_KIT_CATALOG_ENTRY_HEADER(scale);
    SO_KIT_CATALOG_ENTRY_HEADER(shape);

public:
    SoShapeScale(void);
    static void initClass(void);

    SoSFFloat active;
    SoSFFloat scaleFactor;

protected:
    virtual void GLRender(SoGLRenderAction * action);
    virtual ~SoShapeScale();
};

class GuiExport SoAxisCrossKit : public SoBaseKit {
    typedef SoBaseKit inherited;

    SO_KIT_HEADER(SoAxisCrossKit);

    SO_KIT_CATALOG_ENTRY_HEADER(xAxis);
    SO_KIT_CATALOG_ENTRY_HEADER(xHead);
    SO_KIT_CATALOG_ENTRY_HEADER(yAxis);
    SO_KIT_CATALOG_ENTRY_HEADER(yHead);
    SO_KIT_CATALOG_ENTRY_HEADER(zAxis);
    SO_KIT_CATALOG_ENTRY_HEADER(zHead);

public:
    SoAxisCrossKit();

    // Overrides default method. All the parts are shapeKits,
    // so this node will not affect the state.
    virtual SbBool affectsState() const;
    virtual void addWriteReference(SoOutput * out, SbBool isfromfield = false);
    virtual void getBoundingBox(SoGetBoundingBoxAction * action);

    static void initClass();

private:
    // Constructor calls to build and set up parts.
    void createAxes();
    virtual ~SoAxisCrossKit();
};

class GuiExport SoRegPoint : public SoShape {
    typedef SoShape inherited;

    SO_NODE_HEADER(SoRegPoint);

public:
    static void initClass();
    SoRegPoint();

    void notify(SoNotList * node);

    SoSFVec3f base;
    SoSFVec3f normal;
    SoSFFloat length;
    SoSFColor color;
    SoSFString text;

protected:
    virtual ~SoRegPoint();
    virtual void GLRender(SoGLRenderAction *action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
    virtual void generatePrimitives(SoAction *action);

private:
    SoSeparator* root;
};

} // namespace Gui

#endif // GUI_SOSHAPESCALE_H
