/***************************************************************************
 *   Copyright (c) Stefan Tröger          (stefantroeger@gmx.net) 2015     *
 *   Copyright (c) 2015 Alexander Golubev (Fat-Zer) <fatzer2@gmail.com>    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_ViewProviderOrigin_H
#define GUI_VIEWPROVIDER_ViewProviderOrigin_H

#include "stdexport.h"
#include "App/PropertyGeo.h"
#include "ViewProviderDocumentObject.h"

namespace Gui {

class Document;

class GuiExport ViewProviderOrigin : public ViewProviderDocumentObject
{
    PROPERTY_HEADER(Gui::ViewProviderOrigin);

public:
    /// Size of the origin as set by the part.
    App::PropertyVector Size;

    /// constructor.
    ViewProviderOrigin();
    /// destructor.
    virtual ~ViewProviderOrigin();

    /// @name Override methods
    ///@{
    virtual std::vector<App::DocumentObject*> claimChildren(void) const;
    virtual std::vector<App::DocumentObject*> claimChildren3D(void) const;

    virtual SoGroup* getChildRoot(void) const {return pcGroupChildren;};

    virtual void attach(App::DocumentObject* pcObject);
    virtual std::vector<std::string> getDisplayModes(void) const;
    virtual void setDisplayMode(const char* ModeName);
    ///@}

    /** @name Temporary visibility mode
     * Control the visibility of origin and associated objects when needed
     */
    ///@{
    /// Set temporary visibility of some of origin's objects e.g. while rotating or mirroring
    void setTemporaryVisibility (bool axis, bool planes);
    /// Returns true if the origin in temporary visibility mode
    bool isTemporaryVisibility ();
    /// Reset the visibility
    void resetTemporaryVisibility ();
    ///@}
    
    virtual bool canDragObjects() const {
        return false;
    }

    /// Returns default size. Use this if it is not possible to determine appropriate size by other means
    static double defaultSize() {return 10.;}
protected:
    virtual void onChanged(const App::Property* prop);
    virtual bool onDelete(const std::vector<std::string> &);

private:
    SoGroup *pcGroupChildren;

    std::map<Gui::ViewProvider*, bool> tempVisMap;
};

} // namespace Gui

#endif // GUI_VIEWPROVIDER_ViewProviderOrigin_H

