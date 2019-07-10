/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDER_EXTERN_H
#define GUI_VIEWPROVIDER_EXTERN_H

#include "stdexport.h"
#include "ViewProvider.h"


class SoNode;
class SoInput;

namespace Gui {


class GuiExport ViewProviderExtern:public ViewProvider
{
    PROPERTY_HEADER(Gui::ViewProviderExtern);

public:
    /// constructor.
    ViewProviderExtern();

    /// destructor.
    virtual ~ViewProviderExtern();

    void setModeByString(const char* name, const char* ivFragment);
    void setModeByFile(const char* name, const char* ivFileName);
    void setModeBySoInput(const char* name, SoInput &ivFileInput);
    void adjustDocumentName(const char* docname);

    virtual const char* getDefaultDisplayMode() const;
    virtual std::vector<std::string> getDisplayModes(void) const;
    virtual void updateData(const App::Property*){}

private:
    void adjustRecursiveDocumentName(SoNode*, const char* docname);

protected:
    std::vector<std::string> modes;
};

} // namespace Gui

#endif // GUI_VIEWPROVIDER_EXTERN_H

