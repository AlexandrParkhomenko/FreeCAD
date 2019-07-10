/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2010     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

 

#include "Geometry.h"

#include "FeatureGeometrySet.h"


using namespace Part;


PROPERTY_SOURCE(Part::FeatureGeometrySet, Part::Feature)


FeatureGeometrySet::FeatureGeometrySet()
{
    ADD_PROPERTY(GeometrySet,(0));
}


App::DocumentObjectExecReturn *FeatureGeometrySet::execute(void)
{
    TopoShape result;

    const std::vector<Geometry*> &Geoms = GeometrySet.getValues();

    bool first = true;
    for(std::vector<Geometry*>::const_iterator it=Geoms.begin();it!=Geoms.end();++it){
        TopoDS_Shape sh = (*it)->toShape();
        if (first) {
            first = false;
            result.setShape(sh);
        }
        else {
            result.setShape(result.fuse(sh));
        }
    }
    
    Shape.setValue(result);

    return App::DocumentObject::StdReturn;
}
