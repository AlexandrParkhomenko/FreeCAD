/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2008     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

 


#ifndef _ImportStep_h_
#define _ImportStep_h_

#include "stdexport.h"
#include <TopoDS_Shape.hxx>
#include "App/ComplexGeoData.h"

namespace App {
class Document;
}

namespace Part
{


/** The part shape property
 */
Standard_EXPORT int ImportStepParts(App::Document *pcDoc, const char* Name);



} //namespace Part



#endif
