/***************************************************************************
 *   Copyright (c) 2017 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#include "stdexport.h"
#include "PartPyCXX.h"
#include <CXX/Objects.hxx>
#include "Mod/Part/App/TopoShapeFacePy.h"
#include "Mod/Part/App/TopoShapeEdgePy.h"
#include "Mod/Part/App/TopoShapeWirePy.h"
#include "Mod/Part/App/TopoShapeVertexPy.h"
#include "Mod/Part/App/TopoShapeSolidPy.h"
#include "Mod/Part/App/TopoShapeShellPy.h"
#include "Mod/Part/App/TopoShapeCompSolidPy.h"
#include "Mod/Part/App/TopoShapeCompoundPy.h"

namespace Part {
Standard_EXPORT Py::Object shape2pyshape(const TopoDS_Shape &shape)
{
    PyObject* ret = 0;
    if (!shape.IsNull()) {
        TopAbs_ShapeEnum type = shape.ShapeType();
        switch (type)
        {
        case TopAbs_COMPOUND:
            ret = new TopoShapeCompoundPy(new TopoShape(shape));
            break;
        case TopAbs_COMPSOLID:
            ret = new TopoShapeCompSolidPy(new TopoShape(shape));
            break;
        case TopAbs_SOLID:
            ret = new TopoShapeSolidPy(new TopoShape(shape));
            break;
        case TopAbs_SHELL:
            ret = new TopoShapeShellPy(new TopoShape(shape));
            break;
        case TopAbs_FACE:
            ret = new TopoShapeFacePy(new TopoShape(shape));
            break;
        case TopAbs_WIRE:
            ret = new TopoShapeWirePy(new TopoShape(shape));
            break;
        case TopAbs_EDGE:
            ret = new TopoShapeEdgePy(new TopoShape(shape));
            break;
        case TopAbs_VERTEX:
            ret = new TopoShapeVertexPy(new TopoShape(shape));
            break;
        case TopAbs_SHAPE:
            ret = new TopoShapePy(new TopoShape(shape));
            break;
        default:
            //shouldn't happen
            ret = new TopoShapePy(new TopoShape(shape));
            break;
        }
    } else {
        ret = new TopoShapePy(new TopoShape(shape));
    }
    assert(ret);

    return Py::asObject(ret);
}
} //namespace Part


namespace Py {
    template<>
    bool TopoShape::accepts (PyObject *pyob) const
    {
        return (pyob && PyObject_TypeCheck(pyob, &(Part::TopoShapePy::Type)));
    }

    // explicit template instantiation
    template class Standard_EXPORT ExtensionObject<Part::TopoShapePy>;
}

