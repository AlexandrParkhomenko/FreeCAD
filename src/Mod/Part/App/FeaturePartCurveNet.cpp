/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2005     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

 

#include "Base/Console.h"
#include "Base/Exception.h"
#include "Base/Sequencer.h"
#include "FeaturePartCurveNet.h"


using namespace Part;

PROPERTY_SOURCE(Part::CurveNet, Part::Feature)

CurveNet::CurveNet()
{
    ADD_PROPERTY(FileName,(""));
}

short CurveNet::mustExecute() const
{
    if (FileName.isTouched())
        return 1;
    return 0;
}

App::DocumentObjectExecReturn *CurveNet::execute(void)
{
    Base::FileInfo fi(FileName.getValue());
    if (!fi.isReadable()) {
        Base::Console().Log("CurveNet::execute() not able to open %s!\n",FileName.getValue());
        std::string error = std::string("Cannot open file ") + FileName.getValue();
        return new App::DocumentObjectExecReturn(error);
    }

    TopoShape aShape;
    aShape.read(FileName.getValue());
    this->Shape.setValue(aShape);

    return App::DocumentObject::StdReturn;
}
