/***************************************************************************
 *   Copyright (c) 2013 Jürgen Riegel (FreeCAD@juergen-riegel.net)         *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/




#include "stdexport.h"
#include "MaterialObject.h"
#include "DocumentObjectPy.h"

using namespace App;

PROPERTY_SOURCE(App::MaterialObject, App::DocumentObject)


MaterialObject::MaterialObject() 
{
    ADD_PROPERTY_TYPE(Material,(),"Material",Prop_None,"Material key/value map");

}

MaterialObject::~MaterialObject()
{
}

// Python feature ---------------------------------------------------------

namespace App {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(App::MaterialObjectPython, App::MaterialObject)
template<> const char* App::MaterialObjectPython::getViewProviderName(void) const {
    return "Gui::ViewProviderMaterialObjectPython";
}
/// @endcond

// explicit template instantiation
template class AppExport FeaturePythonT<App::MaterialObject>;
}
