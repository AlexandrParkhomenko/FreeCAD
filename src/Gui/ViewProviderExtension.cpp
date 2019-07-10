/***************************************************************************
 *   Copyright (c) Stefan Tröger          (stefantroeger@gmx.net) 2016     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "stdexport.h"
# include <cassert>
# include <algorithm>

#include "ViewProviderExtension.h"
//#include "ViewProviderExtensionPy.h"

using namespace Gui;

EXTENSION_PROPERTY_SOURCE(Gui::ViewProviderExtension, App::Extension)

ViewProviderExtension::ViewProviderExtension() 
{
    initExtensionType(Gui::ViewProviderExtension::getExtensionClassTypeId());
}

ViewProviderExtension::~ViewProviderExtension()
{

}

const ViewProviderDocumentObject* ViewProviderExtension::getExtendedViewProvider() const{

    assert(getExtendedContainer()->isDerivedFrom(ViewProviderDocumentObject::getClassTypeId())); 
    return static_cast<const ViewProviderDocumentObject*>(getExtendedContainer());
}

ViewProviderDocumentObject* ViewProviderExtension::getExtendedViewProvider() {

    assert(getExtendedContainer()->isDerivedFrom(ViewProviderDocumentObject::getClassTypeId())); 
    return static_cast<ViewProviderDocumentObject*>(getExtendedContainer());
}

void ViewProviderExtension::extensionUpdateData(const App::Property*) {

}

namespace Gui {
EXTENSION_PROPERTY_SOURCE_TEMPLATE(Gui::ViewProviderExtensionPython, Gui::ViewProviderExtension)

// explicit template instantiation
template class GuiExport ViewProviderExtensionPythonT<ViewProviderExtension>;
}
