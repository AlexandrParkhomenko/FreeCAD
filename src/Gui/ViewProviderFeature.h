/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_FEATURE_H
#define GUI_VIEWPROVIDER_FEATURE_H

#include "stdexport.h"
#include <Inventor/lists/SoPickedPointList.h> 
#include "App/PropertyStandard.h"
#include "ViewProviderDocumentObject.h"

class SoPickedPointList;
class SbVec2s;

namespace Gui {

class View3DInventorViewer;

class GuiExport ViewProviderFeature:public ViewProviderDocumentObject
{
    PROPERTY_HEADER(Gui::ViewProviderFeature);

public:
    /// constructor.
    ViewProviderFeature();

    /// destructor.
    virtual ~ViewProviderFeature();

    App::PropertyColorList    ColourList;

    /**
     * Attaches the document object to this view provider.
     */
    virtual void attach(App::DocumentObject *pcObj);
};

} // namespace Gui

#endif // GUI_VIEWPROVIDER_FEATURE_H

