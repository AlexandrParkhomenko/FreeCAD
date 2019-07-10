/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Sequencer.h"
#include "FeatureMeshImport.h"

#include "Core/MeshIO.h"


using namespace Mesh;
using namespace MeshCore;

PROPERTY_SOURCE(Mesh::Import, Mesh::Feature)


Mesh::Import::Import(void)
{
    ADD_PROPERTY(FileName,(""));
}

short Mesh::Import::mustExecute(void) const
{
    if (FileName.isTouched())
        return 1;
    return 0;
}

App::DocumentObjectExecReturn *Mesh::Import::execute(void)
{
    std::unique_ptr<MeshObject> apcKernel(new MeshObject());
    apcKernel->load(FileName.getValue());
    Mesh.setValuePtr(apcKernel.release());

    return App::DocumentObject::StdReturn;
}

