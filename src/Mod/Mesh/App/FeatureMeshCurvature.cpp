/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Matrix.h"
#include "Base/Sequencer.h"
#include "FeatureMeshCurvature.h"
#include "MeshFeature.h"

#include "Core/Curvature.h"
#include "Core/Elements.h"
#include "Core/Iterator.h"



using namespace Mesh;

PROPERTY_SOURCE(Mesh::Curvature, App::DocumentObject)


Curvature::Curvature(void)
{
    ADD_PROPERTY(Source,(0));
    ADD_PROPERTY(CurvInfo, (CurvatureInfo()));
}

short Curvature::mustExecute() const
{
    if (Source.isTouched())
        return 1;
    if (Source.getValue() && Source.getValue()->isTouched())
        return 1;
    return 0;
}

App::DocumentObjectExecReturn *Curvature::execute(void)
{
    Mesh::Feature *pcFeat  = dynamic_cast<Mesh::Feature*>(Source.getValue());
    if(!pcFeat || pcFeat->isError()) {
        return new App::DocumentObjectExecReturn("No mesh object attached.");
    }
 
    // get all points
    const MeshCore::MeshKernel& rMesh = pcFeat->Mesh.getValue().getKernel();
    MeshCore::MeshCurvature meshCurv(rMesh);
    meshCurv.ComputePerVertex();
    const std::vector<MeshCore::CurvatureInfo>& curv = meshCurv.GetCurvature();

    std::vector<CurvatureInfo> values;
    values.reserve(curv.size());
    for (std::vector<MeshCore::CurvatureInfo>::const_iterator it = curv.begin(); it != curv.end(); ++it) {
        CurvatureInfo ci;
        ci.cMaxCurvDir = it->cMaxCurvDir;
        ci.cMinCurvDir = it->cMinCurvDir;
        ci.fMaxCurvature = it->fMaxCurvature;
        ci.fMinCurvature = it->fMinCurvature;
        values.push_back(ci);
    }

    CurvInfo.setValues(values);

    return App::DocumentObject::StdReturn;
}
