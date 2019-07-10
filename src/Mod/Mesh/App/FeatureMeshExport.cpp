/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Sequencer.h"
#include "FeatureMeshExport.h"
#include "MeshFeature.h"

#include "Core/MeshIO.h"


using namespace Mesh;
using namespace MeshCore;

PROPERTY_SOURCE(Mesh::Export, App::DocumentObject)

Export::Export(void)
{
    ADD_PROPERTY(Source  ,(0));
    ADD_PROPERTY(FileName,(""));
    ADD_PROPERTY(Format  ,(""));
}

short Export::mustExecute() const
{
    if (Source.getValue()) {
        if (Source.isTouched())
            return 1;
        if (FileName.isTouched())
            return 1;
        if (Format.isTouched())
            return 1;
    }
    return 0;
}

App::DocumentObjectExecReturn *Export::execute(void)
{
    Mesh::Feature *pcFeat  = dynamic_cast<Mesh::Feature*>(Source.getValue());
    if(!pcFeat || pcFeat->isError()) {
        return new App::DocumentObjectExecReturn("Cannot export invalid mesh feature");
    }

    pcFeat->Mesh.getValue().save(FileName.getValue());
    return App::DocumentObject::StdReturn;
}
