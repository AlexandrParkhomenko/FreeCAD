/***************************************************************************
 *   Copyright (c) Stefan Tröger          (stefantroeger@gmx.net) 2016     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <sstream>

#include "Application.h"

// inclution of the generated files (generated out of PropertyContainerPy.xml)
#include "App/ExtensionPy.h"
#include <App/ExtensionPy.cpp>

using namespace App;

// returns a string which represent the object e.g. when printed in python
std::string ExtensionPy::representation(void) const
{
    return std::string("<extension>");
}

PyObject *ExtensionPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int ExtensionPy::setCustomAttributes(const char* /*attr*/, PyObject * /*obj*/)
{
    return 0;
}
