/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERCOMPOUND_H
#define PARTGUI_VIEWPROVIDERCOMPOUND_H

#include "stdexport.h"
#include "ViewProvider.h"


namespace PartGui {

class PartGuiExport ViewProviderCompound : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderCompound);

public:
    /// constructor
    ViewProviderCompound();
    /// destructor
    virtual ~ViewProviderCompound();
    std::vector<App::DocumentObject*> claimChildren() const;
    bool onDelete(const std::vector<std::string> &);

    /// drag and drop
    bool canDragObjects() const;
    bool canDragObject(App::DocumentObject*) const;
    void dragObject(App::DocumentObject*);
    bool canDropObjects() const;
    bool canDropObject(App::DocumentObject*) const;
    void dropObject(App::DocumentObject*);
    /** Replace an object to the view provider by drag and drop */
    virtual void replaceObject(App::DocumentObject*, App::DocumentObject*);

protected:
    void updateData(const App::Property*);
};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERCOMPOUND_H
