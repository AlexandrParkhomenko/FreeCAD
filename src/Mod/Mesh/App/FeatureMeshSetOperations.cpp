/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Sequencer.h"

#include "Core/MeshKernel.h"
#include "Core/Algorithm.h"
#include "Core/Evaluation.h"
#include "Core/Iterator.h"
#include "Core/Visitor.h"

#include "Core/SetOperations.h"

#include "FeatureMeshSetOperations.h"


using namespace Mesh;
using namespace std;

PROPERTY_SOURCE(Mesh::SetOperations, Mesh::Feature)


SetOperations::SetOperations(void)
{
    ADD_PROPERTY(Source1  ,(0));
    ADD_PROPERTY(Source2  ,(0));
    ADD_PROPERTY(OperationType, ("union"));
}

short SetOperations::mustExecute() const
{
    if (Source1.getValue() && Source2.getValue()) {
        if (Source1.isTouched())
            return 1;
        if (Source2.isTouched())
            return 1;
        if (OperationType.isTouched())
            return 1;
    }

    return 0;
}

App::DocumentObjectExecReturn *SetOperations::execute(void)
{
    Mesh::Feature *mesh1  = dynamic_cast<Mesh::Feature*>(Source1.getValue());
    Mesh::Feature *mesh2  = dynamic_cast<Mesh::Feature*>(Source2.getValue());

    if ((mesh1 != NULL) && (mesh2 != NULL)) {
        const MeshObject& meshKernel1 = mesh1->Mesh.getValue();
        const MeshObject& meshKernel2 = mesh2->Mesh.getValue();

        std::unique_ptr<MeshObject> pcKernel(new MeshObject()); // Result Meshkernel

        MeshCore::SetOperations::OperationType type;
        string ot(OperationType.getValue());
        if (ot == "union")
            type = MeshCore::SetOperations::Union;
        else if (ot == "intersection")
            type = MeshCore::SetOperations::Intersect;
        else if (ot == "difference")
            type = MeshCore::SetOperations::Difference;
        else if (ot == "inner")
            type = MeshCore::SetOperations::Inner;
        else if (ot == "outer")
            type = MeshCore::SetOperations::Outer;
        else
            throw Base::ValueError("Operation type must either be 'union' or 'intersection'"
                                   " or 'difference' or 'inner' or 'outer'");

        MeshCore::SetOperations setOp(meshKernel1.getKernel(), meshKernel2.getKernel(), 
            pcKernel->getKernel(), type, 1.0e-5f);
        setOp.Do();
        Mesh.setValuePtr(pcKernel.release());
    }
    else {
        // Error mesh property
        if (!mesh1)
            throw Base::ValueError("First input mesh not set");
        if (!mesh2)
            throw Base::ValueError("Second input mesh not set");
    }

    return App::DocumentObject::StdReturn;
}

