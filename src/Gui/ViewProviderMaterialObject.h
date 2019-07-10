/***************************************************************************
 *   Copyright (c) 2013 Jürgen Riegel (FreeCAD@juergen-riegel.net)         *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_ViewProviderMaterialObject_H
#define GUI_ViewProviderMaterialObject_H


#include "stdexport.h"
#include "ViewProviderDocumentObject.h"
#include "ViewProviderPythonFeature.h"

namespace Gui {

class GuiExport ViewProviderMaterialObject : public ViewProviderDocumentObject
{
    PROPERTY_HEADER(Gui::ViewProviderMaterialObject);

public:
    /// constructor.
    ViewProviderMaterialObject();
    /// destructor.
    virtual ~ViewProviderMaterialObject();

    QIcon getIcon(void) const;

    bool doubleClicked(void);

    // shows solid in the tree
    virtual bool isShow(void) const{return true;}

};

typedef ViewProviderPythonFeatureT<ViewProviderMaterialObject> ViewProviderMaterialObjectPython;

} // namespace Gui

#endif // GUI_ViewProviderMaterialObject_H

