/***************************************************************************
 *   Copyright (c) 2010 Juergen Riegel <FreeCAD@juergen-riegel.net>        *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "Mod/Part/App/BodyBase.h"

// inclusion of the generated files (generated out of ItemPy.xml)
#include "BodyBasePy.h"
#include "BodyBasePy.cpp"

using namespace Part;

// returns a string which represents the object e.g. when printed in python
std::string BodyBasePy::representation(void) const
{
    return std::string("<body object>");
}


PyObject *BodyBasePy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int BodyBasePy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}


