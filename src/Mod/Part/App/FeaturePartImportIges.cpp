/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

 
# include <fcntl.h>

#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/FileInfo.h"
#include "FeaturePartImportIges.h"


using namespace Part;

PROPERTY_SOURCE(Part::ImportIges, Part::Feature)


ImportIges::ImportIges(void)
{
    ADD_PROPERTY(FileName,(""));
}

short ImportIges::mustExecute() const
{
    if (FileName.isTouched())
        return 1;
    return 0;
}

App::DocumentObjectExecReturn *ImportIges::execute(void)
{
    Base::FileInfo fi(FileName.getValue());
    if (!fi.isReadable()) {
        Base::Console().Log("ImportIges::execute() not able to open %s!\n",FileName.getValue());
        std::string error = std::string("Cannot open file ") + FileName.getValue();
        return new App::DocumentObjectExecReturn(error);
    }

    TopoShape aShape;
    aShape.importIges(FileName.getValue());
    this->Shape.setValue(aShape);

    return App::DocumentObject::StdReturn;
}


