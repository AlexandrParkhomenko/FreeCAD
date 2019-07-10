/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "PartFeature.h"

// inclusion of the generated files (generated out of PartFeaturePy.xml)
#include "PartFeaturePy.h"
#include "PartFeaturePy.cpp"

using namespace Part;

// returns a string which represent the object e.g. when printed in python
std::string PartFeaturePy::representation(void) const
{
    return std::string("<Part::PartFeature>");
}

PyObject *PartFeaturePy::getCustomAttributes(const char* ) const
{
    return 0;
}

int PartFeaturePy::setCustomAttributes(const char* , PyObject *)
{
    return 0; 
}
