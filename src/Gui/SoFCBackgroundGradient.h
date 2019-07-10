/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_SOFCBACKGROUNDGRADIENT_H
#define GUI_SOFCBACKGROUNDGRADIENT_H

#include "stdexport.h"

#ifndef __InventorAll__
# include "InventorAll.h"
#endif

class SbColor;
class SoGLRenderAction;

namespace Gui {

class GuiExport SoFCBackgroundGradient : public SoNode {
    typedef SoNode inherited;

    SO_NODE_HEADER(Gui::SoFCBackgroundGradient);

public:
    static void initClass(void);
    static void finish(void);
    SoFCBackgroundGradient(void);

    void GLRender (SoGLRenderAction *action);
    void setColorGradient(const SbColor& fromColor, const SbColor& toColor);
    void setColorGradient(const SbColor& fromColor, const SbColor& toColor, const SbColor& midColor);

protected:
    virtual ~SoFCBackgroundGradient();

    SbColor fCol, tCol, mCol;
};

} // namespace Gui


#endif // GUI_SOFCBACKGROUNDGRADIENT_H

