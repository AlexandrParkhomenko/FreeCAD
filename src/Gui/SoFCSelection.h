/***************************************************************************
 *   Copyright (c) 2005 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef GUI_SOFCSELECTION_H
#define GUI_SOFCSELECTION_H


#include "stdexport.h"
# include <GL/gl.h>

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoLightModel.h>

class SoFullPath;
class SoPickedPoint;


namespace Gui {


/** Selection node
 *  This node does the complete highlighting and selection together with the viewer
 *  \author Jürgen Riegel
 */
class GuiExport SoFCSelection : public SoGroup {
    typedef SoGroup inherited;

    SO_NODE_HEADER(Gui::SoFCSelection);

public:
    static void initClass(void);
    static void finish(void);
    SoFCSelection(void);

    /// Load highlight settings from the configuration
    void applySettings ();

    enum HighlightModes {
        AUTO, ON, OFF
    };

    enum SelectionModes {
        SEL_ON, SEL_OFF
    };

    enum Selected {
        NOTSELECTED, SELECTED
    };

    enum Styles {
        EMISSIVE, EMISSIVE_DIFFUSE, BOX
    };

    SbBool isHighlighted(void) const {return highlighted;}

    SoSFColor colorHighlight;
    SoSFColor colorSelection;
    SoSFEnum style;
    SoSFEnum selected;
    SoSFEnum highlightMode;
    SoSFEnum selectionMode;

    SoSFString documentName;
    SoSFString objectName;
    SoSFString subElementName;

    virtual void doAction(SoAction *action);
    virtual void GLRender(SoGLRenderAction * action);

    virtual void handleEvent(SoHandleEventAction * action);
    virtual void GLRenderBelowPath(SoGLRenderAction * action);
    virtual void GLRenderInPath(SoGLRenderAction * action);
    static  void turnOffCurrentHighlight(SoGLRenderAction * action);

protected:
    virtual ~SoFCSelection();
    virtual void redrawHighlighted(SoAction * act, SbBool flag);
    virtual SbBool readInstance(SoInput *  in, unsigned short  flags); 

private:
    static int getPriority(const SoPickedPoint*);
    static void turnoffcurrent(SoAction * action);
    void setOverride(SoGLRenderAction * action);
    SbBool isHighlighted(SoAction *action);
    SbBool preRender(SoGLRenderAction *act, GLint &oldDepthFunc);
    const SoPickedPoint* getPickedPoint(SoHandleEventAction*) const;

    static SoFullPath * currenthighlight;

    SbBool highlighted;
    SoColorPacker colorpacker;

    SbBool bShift;
    SbBool bCtrl;
};


} // namespace Gui

#endif // !GUI_SOFCSELECTION_H
