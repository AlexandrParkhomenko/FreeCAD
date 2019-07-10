/***************************************************************************
 *   Copyright (c) Juergen Riegel          (juergen.riegel@web.de) 2014    *
 *   Copyright (c) Alexander Golubev (Fat-Zer) <fatzer2@gmail.com> 2015    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "App/GeoFeatureGroupExtension.h"

// inclusion of the generated files (generated out of GeoFeatureGroupExtensionPy.xml)
#include "GeoFeatureGroupExtensionPy.h"
#include "GeoFeatureGroupExtensionPy.cpp"

using namespace App;

// returns a string which represents the object e.g. when printed in python
std::string GeoFeatureGroupExtensionPy::representation(void) const
{
    return std::string("<GeoFeatureGroup object>");
}


PyObject *GeoFeatureGroupExtensionPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int GeoFeatureGroupExtensionPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}


