/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Interpreter.h"
#include "App/Document.h"

#include "FeatureMeshSolid.h"
#include "Mesh.h"


namespace Mesh {
    const App::PropertyIntegerConstraint::Constraints intSampling = {0,1000,1};
    const App::PropertyFloatConstraint::Constraints floatRange = {0.0,1000.0,1.0};
}

using namespace Mesh;
using namespace MeshCore;

PROPERTY_SOURCE(Mesh::Sphere, Mesh::Feature)

Sphere::Sphere(void)
{
    ADD_PROPERTY(Radius  ,(5.0));
    ADD_PROPERTY(Sampling  ,(50));
    Radius.setConstraints(&floatRange);
    Sampling.setConstraints(&intSampling);
}

short Sphere::mustExecute() const
{
    if (Radius.isTouched() || Sampling.isTouched())
        return 1;
    return Feature::mustExecute();
}

App::DocumentObjectExecReturn *Sphere::execute(void)
{
    std::unique_ptr<MeshObject> mesh(MeshObject::createSphere((float)Radius.getValue(),Sampling.getValue()));
    if (mesh.get()) {
        mesh->setPlacement(this->Placement.getValue());
        Mesh.setValue(mesh->getKernel());
        return App::DocumentObject::StdReturn;
    }
    else {
        return new App::DocumentObjectExecReturn("Cannot create sphere", this);
    }
}

// -------------------------------------------------------------

PROPERTY_SOURCE(Mesh::Ellipsoid, Mesh::Feature)

Ellipsoid::Ellipsoid(void)
{
    ADD_PROPERTY(Radius1  ,(2.0));
    ADD_PROPERTY(Radius2  ,(4.0));
    ADD_PROPERTY(Sampling  ,(50));
    Radius1.setConstraints(&floatRange);
    Radius2.setConstraints(&floatRange);
    Sampling.setConstraints(&intSampling);
}

short Ellipsoid::mustExecute() const
{
    if (Radius1.isTouched() || 
        Radius2.isTouched() || 
        Sampling.isTouched())
        return 1;
    return Feature::mustExecute();
}

App::DocumentObjectExecReturn *Ellipsoid::execute(void)
{
    std::unique_ptr<MeshObject> mesh(MeshObject::createEllipsoid((float)Radius1.getValue(),(float)Radius2.getValue(),Sampling.getValue()));
    if (mesh.get()) {
        mesh->setPlacement(this->Placement.getValue());
        Mesh.setValue(mesh->getKernel());
        return App::DocumentObject::StdReturn;
    }
    else {
        return new App::DocumentObjectExecReturn("Cannot create ellipsoid", this);
    }
}

// -------------------------------------------------------------

PROPERTY_SOURCE(Mesh::Cylinder, Mesh::Feature)

Cylinder::Cylinder(void)
{
    ADD_PROPERTY(Radius  ,(2.0));
    ADD_PROPERTY(Length  ,(10.0));
    ADD_PROPERTY(EdgeLength,(1.0));
    ADD_PROPERTY(Closed  ,(true));
    ADD_PROPERTY(Sampling  ,(50));
    Radius.setConstraints(&floatRange);
    Length.setConstraints(&floatRange);
    EdgeLength.setConstraints(&floatRange);
    Sampling.setConstraints(&intSampling);
}

short Cylinder::mustExecute() const
{
    if (Radius.isTouched() || 
        Length.isTouched() ||
        EdgeLength.isTouched() ||
        Closed.isTouched() ||
        Sampling.isTouched())
        return 1;
    return Feature::mustExecute();
}

App::DocumentObjectExecReturn *Cylinder::execute(void)
{
    std::unique_ptr<MeshObject> mesh(MeshObject::createCylinder((float)Radius.getValue(),(float)Length.getValue(),
                                   Closed.getValue(),(float)EdgeLength.getValue(),Sampling.getValue()));
    if (mesh.get()) {
        mesh->setPlacement(this->Placement.getValue());
        Mesh.setValue(mesh->getKernel());
        return App::DocumentObject::StdReturn;
    }
    else {
        return new App::DocumentObjectExecReturn("Cannot create cylinder", this);
    }
}

// -------------------------------------------------------------

PROPERTY_SOURCE(Mesh::Cone, Mesh::Feature)

Cone::Cone(void)
{
    ADD_PROPERTY(Radius1  ,(2.0));
    ADD_PROPERTY(Radius2  ,(4.0));
    ADD_PROPERTY(Length  ,(10.0));
    ADD_PROPERTY(EdgeLength,(1.0));
    ADD_PROPERTY(Closed  ,(true));
    ADD_PROPERTY(Sampling  ,(50));
    Radius1.setConstraints(&floatRange);
    Radius2.setConstraints(&floatRange);
    Length.setConstraints(&floatRange);
    EdgeLength.setConstraints(&floatRange);
    Sampling.setConstraints(&intSampling);
}

short Cone::mustExecute() const
{
    if (Radius1.isTouched() || 
        Radius2.isTouched() || 
        Length.isTouched()  ||
        EdgeLength.isTouched() ||
        Closed.isTouched()  ||
        Sampling.isTouched())
        return 1;
    return Feature::mustExecute();
}

App::DocumentObjectExecReturn *Cone::execute(void)
{
    std::unique_ptr<MeshObject> mesh(MeshObject::createCone((float)Radius1.getValue(),(float)Radius2.getValue(),(float)Length.getValue(),
                                   Closed.getValue(),(float)EdgeLength.getValue(),Sampling.getValue()));
    if (mesh.get()) {
        mesh->setPlacement(this->Placement.getValue());
        Mesh.setValue(mesh->getKernel());
        return App::DocumentObject::StdReturn;
    }
    else {
        return new App::DocumentObjectExecReturn("Cannot create cone", this);
    }
}

// -------------------------------------------------------------

PROPERTY_SOURCE(Mesh::Torus, Mesh::Feature)

Torus::Torus(void)
{
    ADD_PROPERTY(Radius1  ,(10.0));
    ADD_PROPERTY(Radius2  ,(2.0));
    ADD_PROPERTY(Sampling  ,(50));
    Radius1.setConstraints(&floatRange);
    Radius2.setConstraints(&floatRange);
    Sampling.setConstraints(&intSampling);
}

short Torus::mustExecute() const
{
    if (Radius1.isTouched() || 
        Radius2.isTouched() || 
        Sampling.isTouched())
        return 1;
    return Feature::mustExecute();
}

App::DocumentObjectExecReturn *Torus::execute(void)
{
    std::unique_ptr<MeshObject> mesh(MeshObject::createTorus((float)Radius1.getValue(),(float)Radius2.getValue(),Sampling.getValue()));
    if (mesh.get()) {
        mesh->setPlacement(this->Placement.getValue());
        Mesh.setValue(mesh->getKernel());
        return App::DocumentObject::StdReturn;
    }
    else {
        return new App::DocumentObjectExecReturn("Cannot create torus", this);
    }
}

// -------------------------------------------------------------

PROPERTY_SOURCE(Mesh::Cube, Mesh::Feature)

Cube::Cube(void)
{
    ADD_PROPERTY_TYPE(Length,(10.0f),"Cube",App::Prop_None,"The length of the cube");
    ADD_PROPERTY_TYPE(Width ,(10.0f),"Cube",App::Prop_None,"The width of the cube");
    ADD_PROPERTY_TYPE(Height,(10.0f),"Cube",App::Prop_None,"The height of the cube");
    Length.setConstraints(&floatRange);
    Width.setConstraints(&floatRange);
    Height.setConstraints(&floatRange);
}

short Cube::mustExecute() const
{
    if (Length.isTouched() || 
        Width.isTouched() || 
        Height.isTouched())
        return 1;
    return Feature::mustExecute();
}

App::DocumentObjectExecReturn *Cube::execute(void)
{
    std::unique_ptr<MeshObject> mesh(MeshObject::createCube((float)Length.getValue(),(float)Width.getValue(),(float)Height.getValue()));
    if (mesh.get()) {
        mesh->setPlacement(this->Placement.getValue());
        Mesh.setValue(mesh->getKernel());
        return App::DocumentObject::StdReturn;
    }
    else {
        return new App::DocumentObjectExecReturn("Cannot create cube", this);
    }
}
