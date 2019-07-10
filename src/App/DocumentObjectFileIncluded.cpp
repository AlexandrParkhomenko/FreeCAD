/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2008                        *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "DocumentObjectFileIncluded.h"
#include "Document.h"

using namespace App;

PROPERTY_SOURCE(App::DocumentObjectFileIncluded, App::DocumentObject)


DocumentObjectFileIncluded::DocumentObjectFileIncluded() 
{
    ADD_PROPERTY_TYPE(File,(0),"",(App::PropertyType)(Prop_None),"File to include into Project File");
}

DocumentObjectFileIncluded::~DocumentObjectFileIncluded()
{
}

