/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2008     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

 



#include "SketchObjectSF.h"
#include "Base/Console.h"


using namespace Sketcher;


PROPERTY_SOURCE(Sketcher::SketchObjectSF, Part::Part2DObject)


SketchObjectSF::SketchObjectSF()
{
    ADD_PROPERTY_TYPE(SketchFlatFile,(0),"",(App::PropertyType)(App::Prop_None),
        "SketchFlat file (*.skf) which defines this sketch");
}

short SketchObjectSF::mustExecute() const
{
    if (SketchFlatFile.isTouched())
        return 1;
    return 0;
}

App::DocumentObjectExecReturn *SketchObjectSF::execute(void)
{
    Base::Console().Warning("%s: This feature is deprecated and won't be longer supported in future FreeCAD versions\n",this->getNameInDocument());
    // do nothing 
    return App::DocumentObject::StdReturn;
}
