/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PATH_ViewProviderPathShape_H
#define PATH_ViewProviderPathShape_H

#include "stdexport.h"
#include "ViewProviderPath.h"

namespace PathGui
{

class PathGuiExport ViewProviderPathShape: public ViewProviderPath
{
    PROPERTY_HEADER(PathGui::ViewProviderPathShape);

public:

    /// grouping handling 
    virtual std::vector<App::DocumentObject*> claimChildren(void) const;
    virtual void updateData(const App::Property*);
    virtual bool onDelete(const std::vector<std::string> &);

    /// drag and drop
    virtual bool canDragObjects() const;
    virtual bool canDragObject(App::DocumentObject*) const;
    virtual void dragObject(App::DocumentObject*);
    virtual bool canDropObjects() const;
    virtual bool canDropObject(App::DocumentObject*) const;
    virtual void dropObject(App::DocumentObject*);
        
    QIcon getIcon(void) const;
};

} //namespace PathGui


#endif // PATH_ViewProviderPathShape_H
