/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PATH_ViewProviderPathCompound_H
#define PATH_ViewProviderPathCompound_H

#include "stdexport.h"
#include "ViewProviderPath.h"

namespace PathGui
{

class PathGuiExport ViewProviderPathCompound: public ViewProviderPath
{
    PROPERTY_HEADER(PathGui::ViewProviderPathCompound);

public:
        
    std::vector<App::DocumentObject*> claimChildren(void)const;
    virtual bool canDragObjects() const;
    virtual void dragObject(App::DocumentObject*);
    virtual bool canDropObjects() const;
    virtual void dropObject(App::DocumentObject*);
    QIcon getIcon(void) const;

protected:
    virtual bool setEdit(int ModNum);
    virtual void unsetEdit(int ModNum);

};

typedef Gui::ViewProviderPythonFeatureT<ViewProviderPathCompound> ViewProviderPathCompoundPython;

} //namespace PathGui


#endif // PATH_ViewProviderPathCompound_H
