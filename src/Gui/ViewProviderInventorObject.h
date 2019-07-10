/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_INVENTOROBJECT_H
#define GUI_VIEWPROVIDER_INVENTOROBJECT_H

#include "stdexport.h"
#include "ViewProviderDocumentObject.h"


namespace Gui
{

class GuiExport ViewProviderInventorObject : public ViewProviderDocumentObject
{
    PROPERTY_HEADER(Gui::ViewProviderInventorObject);

public:
    ViewProviderInventorObject();
    ~ViewProviderInventorObject();

    void attach(App::DocumentObject *pcObject);
    void setDisplayMode(const char* ModeName);
    std::vector<std::string> getDisplayModes() const;
    void updateData(const App::Property*);
    bool useNewSelectionModel(void) const {return true;}

private:
    void adjustSelectionNodes(SoNode* child, const char* docname, const char* objname);

protected:
    SoSeparator  *pcBuffer;
    SoSeparator  *pcFile;
};

} //namespace Gui


#endif // GUI_VIEWPROVIDER_INVENTOROBJECT_H
