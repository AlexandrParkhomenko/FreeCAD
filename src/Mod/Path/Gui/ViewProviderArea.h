/****************************************************************************
 *   Copyright (c) 2017 Zheng, Lei (realthunder) <realthunder.dev@gmail.com>*
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ****************************************************************************/


#ifndef PATH_ViewProviderArea_H
#define PATH_ViewProviderArea_H

#include "stdexport.h"
#include "Gui/ViewProviderPythonFeature.h"
#include "Mod/Part/Gui/ViewProviderPlaneParametric.h"

namespace PathGui
{

class PathGuiExport ViewProviderArea : public PartGui::ViewProviderPlaneParametric
{
    PROPERTY_HEADER(PathGui::ViewProviderArea);

public:
    ViewProviderArea();
    virtual ~ViewProviderArea();

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
};

typedef Gui::ViewProviderPythonFeatureT<ViewProviderArea> ViewProviderAreaPython;


class PathGuiExport ViewProviderAreaView : public PartGui::ViewProviderPlaneParametric
{
    PROPERTY_HEADER(PathGui::ViewProviderAreaView);

public:
    ViewProviderAreaView();
    virtual ~ViewProviderAreaView();
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
};

typedef Gui::ViewProviderPythonFeatureT<ViewProviderAreaView> ViewProviderAreaViewPython;

} //namespace PathGui


#endif // PATH_ViewProviderArea_H
