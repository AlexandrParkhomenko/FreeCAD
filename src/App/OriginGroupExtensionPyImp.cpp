/***************************************************************************
 *   Copyright (c) Alexander Golubev (Fat-Zer) <fatzer2@gmail.com> 2015    *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "App/OriginGroupExtension.h"

// inclusion of the generated files (generated out of OriginGroupPy.xml)
#include "OriginGroupExtensionPy.h"
#include "OriginGroupExtensionPy.cpp"

using namespace App;

// returns a string which represents the object e.g. when printed in python
std::string OriginGroupExtensionPy::representation(void) const
{
    return std::string("<OriginGroup object>");
}







PyObject *OriginGroupExtensionPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int OriginGroupExtensionPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}


