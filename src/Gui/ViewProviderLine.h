/***************************************************************************
 *   Copyright (c) Juergen Riegel          (juergen.riegel@web.de) 2012    *
 *   Copyright (c) Alexander Golubev (Fat-Zer) <fatzer2@gmail.com> 2015    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_ViewProviderLine_H
#define GUI_ViewProviderLine_H

#include "stdexport.h"
#include "ViewProviderOriginFeature.h"

namespace Gui
{

class GuiExport ViewProviderLine : public ViewProviderOriginFeature {
    PROPERTY_HEADER(Gui::ViewProviderLine);
public:
    /// Constructor
    ViewProviderLine(void);
    virtual ~ViewProviderLine();

    virtual void attach ( App::DocumentObject * );
};

} //namespace Gui


#endif // GUI_ViewProviderLine_H
