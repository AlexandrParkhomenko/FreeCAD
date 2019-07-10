/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_ViewProviderBoolean_H
#define PARTGUI_ViewProviderBoolean_H

#include "stdexport.h"
#include "ViewProvider.h"


namespace PartGui {

class PartGuiExport ViewProviderBoolean : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderBoolean);

public:
    /// constructor
    ViewProviderBoolean();
    /// destructor
    virtual ~ViewProviderBoolean();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void) const;
    QIcon getIcon(void) const;
    void updateData(const App::Property*);
    bool onDelete(const std::vector<std::string> &);
    virtual void replaceObject(App::DocumentObject*, App::DocumentObject*);
};

/// ViewProvider for the MultiFuse feature
class PartGuiExport ViewProviderMultiFuse : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderMultiFuse);

public:
    /// constructor
    ViewProviderMultiFuse();
    /// destructor
    virtual ~ViewProviderMultiFuse();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void) const;
    QIcon getIcon(void) const;
    void updateData(const App::Property*);
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
};

/// ViewProvider for the MultiFuse feature
class PartGuiExport ViewProviderMultiCommon : public ViewProviderPart
{
    PROPERTY_HEADER(PartGui::ViewProviderMultiCommon);

public:
    /// constructor
    ViewProviderMultiCommon();
    /// destructor
    virtual ~ViewProviderMultiCommon();

    /// grouping handling 
    std::vector<App::DocumentObject*> claimChildren(void) const;
    QIcon getIcon(void) const;
    void updateData(const App::Property*);
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
};


} // namespace PartGui


#endif // PARTGUI_ViewProviderBoolean_H
