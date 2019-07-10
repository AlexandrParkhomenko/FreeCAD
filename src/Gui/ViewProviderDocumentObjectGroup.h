/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_DOCUMENTOBJECTGROUP_H
#define GUI_VIEWPROVIDER_DOCUMENTOBJECTGROUP_H


#include "stdexport.h"
#include "ViewProviderDocumentObject.h"
#include "ViewProviderPythonFeature.h"
#include "ViewProviderGroupExtension.h"

namespace Gui {

class GuiExport ViewProviderDocumentObjectGroup : public ViewProviderDocumentObject, 
                                                  public ViewProviderGroupExtension
{
    PROPERTY_HEADER_WITH_EXTENSIONS(Gui::ViewProviderDocumentObjectGroup);

public:
    /// constructor.
    ViewProviderDocumentObjectGroup();
    /// destructor.
    virtual ~ViewProviderDocumentObjectGroup();

    /// returns a list of all possible modes
    std::vector<std::string> getDisplayModes(void) const;
    bool isShow(void) const;


protected:
    void getViewProviders(std::vector<ViewProviderDocumentObject*>&) const;

private:
    std::vector<ViewProvider*> nodes;
};

typedef ViewProviderPythonFeatureT<ViewProviderDocumentObjectGroup> ViewProviderDocumentObjectGroupPython;

} // namespace Gui

#endif // GUI_VIEWPROVIDER_DOCUMENTOBJECTGROUP_H

