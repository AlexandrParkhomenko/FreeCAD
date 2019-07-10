/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2012     *
 *   Copyright (c) Alexander Golubev (Fat-Zer) <fatzer2@gmail.com> 2015    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_ViewProviderPlane_H
#define GUI_ViewProviderPlane_H

#include "stdexport.h"
#include "ViewProviderOriginFeature.h"

namespace Gui
{

class GuiExport ViewProviderPlane : public ViewProviderOriginFeature
{
    PROPERTY_HEADER(Gui::ViewProviderPlane);
public:
    /// Constructor
    ViewProviderPlane(void);
    virtual ~ViewProviderPlane();

    virtual void attach ( App::DocumentObject * );
};

} //namespace Gui


#endif // GUI_ViewProviderPlane_H
