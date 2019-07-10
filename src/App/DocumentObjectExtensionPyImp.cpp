/***************************************************************************
 *   Copyright (c) Stefan Tröger          (stefantroeger@gmx.net) 2016     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <sstream>

// inclution of the generated files (generated out of PropertyContainerPy.xml)
#include "DocumentObjectExtensionPy.h"
#include "DocumentObjectExtensionPy.cpp"

using namespace App;

// returns a string which represent the object e.g. when printed in python
std::string DocumentObjectExtensionPy::representation(void) const
{
    return std::string("<document object extension>");
}

PyObject *DocumentObjectExtensionPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int DocumentObjectExtensionPy::setCustomAttributes(const char* /*attr*/, PyObject * /*obj*/)
{
    return 0;
}
