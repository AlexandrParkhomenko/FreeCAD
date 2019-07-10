/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include <BRepAlgoAPI_Section.hxx>
# include <Standard_Version.hxx>

#include "FeaturePartSection.h"

#include "Base/Exception.h"

using namespace Part;

PROPERTY_SOURCE(Part::Section, Part::Boolean)


Section::Section(void)
{
    ADD_PROPERTY_TYPE(Approximation,(false),"Section",App::Prop_None,"Approximate the output edges");
}

short Section::mustExecute() const
{
    if (Approximation.isTouched())
        return 1;
    return 0;
}

BRepAlgoAPI_BooleanOperation* Section::makeOperation(const TopoDS_Shape& base, const TopoDS_Shape& tool) const
{
    // Let's call algorithm computing a section operation:
    bool approx = Approximation.getValue();
    BRepAlgoAPI_Section* mkSection = new BRepAlgoAPI_Section();
    mkSection->Init1(base);
    mkSection->Init2(tool);
    mkSection->Approximation(approx);
    mkSection->Build();
    if (!mkSection->IsDone())
        throw Base::RuntimeError("Section failed");
    return mkSection;
}
