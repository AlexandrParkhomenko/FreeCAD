/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "DocumentObjectGroup.h"
#include "Document.h"
#include <CXX/Objects.hxx>

// inclusion of the generated files (generated out of DocumentObjectGroupPy.xml)
#include "DocumentObjectGroupPy.h"
#include "DocumentObjectGroupPy.cpp"

using namespace App;

// returns a string which represent the object e.g. when printed in python
std::string DocumentObjectGroupPy::representation(void) const
{
    return std::string("<group object>");
}

PyObject *DocumentObjectGroupPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int DocumentObjectGroupPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}

