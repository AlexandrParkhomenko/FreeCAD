/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PARTGUI_VIEWPROVIDERPART_H
#define PARTGUI_VIEWPROVIDERPART_H

#include "stdexport.h"
#include "Gui/ViewProviderBuilder.h"
#include "Mod/Part/Gui/ViewProviderExt.h"

class SoSeparator;

namespace Part { struct ShapeHistory; }

namespace PartGui {

class ViewProviderShapeBuilder : public Gui::ViewProviderBuilder
{
public:
    ViewProviderShapeBuilder(){}
    ~ViewProviderShapeBuilder(){}
    virtual void buildNodes(const App::Property*, std::vector<SoNode*>&) const;
    void createShape(const App::Property*, SoSeparator*) const;
};

class PartGuiExport ViewProviderPart : public ViewProviderPartExt
{
    PROPERTY_HEADER(PartGui::ViewProviderPart);

public:
    /// constructor
    ViewProviderPart();
    /// destructor
    virtual ~ViewProviderPart();
    virtual bool doubleClicked(void);

protected:
    void applyColor(const Part::ShapeHistory& hist,
                    const std::vector<App::Color>& colBase,
                    std::vector<App::Color>& colBool);
    void applyTransparency(const float& transparency,
                    std::vector<App::Color>& colors);
};

} // namespace PartGui


#endif // PARTGUI_VIEWPROVIDERPART_H

