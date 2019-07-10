/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_VRMLOROBJECT_H
#define GUI_VIEWPROVIDER_VRMLOROBJECT_H

#include "stdexport.h"
#include "ViewProviderDocumentObject.h"

class SbString;

namespace Gui
{

class SoFCSelection;
class GuiExport ViewProviderVRMLObject : public ViewProviderDocumentObject
{
    PROPERTY_HEADER(Gui::ViewProviderVRMLObject);

public:
    /// constructor.
    ViewProviderVRMLObject();

    /// destructor.
    ~ViewProviderVRMLObject();

    void attach(App::DocumentObject *pcObject);
    void setDisplayMode(const char* ModeName);
    std::vector<std::string> getDisplayModes() const;
    void updateData(const App::Property*);
    void getLocalResources(SoNode*, std::list<std::string>&);
    void addResource(const SbString&, std::list<std::string>&);
    template<typename T> void getResourceFile(SoNode*, std::list<std::string>&);

protected:
    SoFCSelection    * pcVRML;
};

} //namespace Gui


#endif // GUI_VIEWPROVIDER_INVENTOROBJECT_H
