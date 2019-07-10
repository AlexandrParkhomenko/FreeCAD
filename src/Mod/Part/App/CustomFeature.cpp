/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "stdexport.h"
# include <gp_Trsf.hxx>
# include <gp_Ax1.hxx>


#include "CustomFeature.h"

using namespace Part;


PROPERTY_SOURCE(Part::CustomFeature, Part::Feature)


CustomFeature::CustomFeature(void)
{
}

CustomFeature::~CustomFeature()
{
}

short CustomFeature::mustExecute(void) const
{
    return Part::Feature::mustExecute();
}

App::DocumentObjectExecReturn *CustomFeature::execute(void)
{
    return App::DocumentObject::StdReturn;
}

// ---------------------------------------------------------

namespace App {
/// @cond DOXERR
PROPERTY_SOURCE_TEMPLATE(Part::CustomFeaturePython, Part::CustomFeature)
template<> const char* Part::CustomFeaturePython::getViewProviderName(void) const {
    return "PartGui::ViewProviderCustomPython";
}
/// @endcond

// explicit template instantiation
template class Standard_EXPORT FeaturePythonT<Part::CustomFeature>;
}

