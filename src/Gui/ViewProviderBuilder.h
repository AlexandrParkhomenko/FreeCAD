/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_VIEWPROVIDERBUILDER_H
#define GUI_VIEWPROVIDERBUILDER_H

#include "stdexport.h"
#include <vector>
#include <map>
#include <memory>
#include "Base/Type.h"
#include "Base/Factory.h"

class SoNode;

namespace App {
    class Property;
}

namespace Gui
{

class ViewProvider;
class SoFCSelection;
class GuiExport ViewProviderBuilder
{
public:
    /// Constructor
    ViewProviderBuilder(void);
    virtual ~ViewProviderBuilder();
    virtual void buildNodes(const App::Property*, std::vector<SoNode*>&) const = 0;

    static void add(const Base::Type&, const Base::Type&);
    static ViewProvider* create(const Base::Type&);
    static SoFCSelection* createSelection();

private:
    static std::map<Base::Type, Base::Type> _prop_to_view;
};

class GuiExport ViewProviderColorBuilder : public ViewProviderBuilder
{
public:
    /// Constructor
    ViewProviderColorBuilder(void);
    virtual ~ViewProviderColorBuilder();
    virtual void buildNodes(const App::Property*, std::vector<SoNode*>&) const;
};

} //namespace Gui


#endif // GUI_VIEWPROVIDERBUILDER_H
