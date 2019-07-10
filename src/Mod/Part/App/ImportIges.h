/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PART_IMPORT_IGES_H
#define PART_IMPORT_IGES_H

#include "stdexport.h"
#include <TopoDS_Shape.hxx>

namespace App {
class Document;
}

namespace Part
{

Standard_EXPORT int ImportIgesParts(App::Document *pcDoc, const char* Name);

} //namespace Part

#endif // PART_IMPORT_IGES_H
