/***************************************************************************
 *   Copyright (c) 2017 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef PART_PYCXX_H
#define PART_PYCXX_H

#include <CXX/Extensions.hxx>
#include "Mod/Part/App/TopoShapePy.h"

namespace Py {
    typedef ExtensionObject<Part::TopoShapePy> TopoShape;
    template<>
    bool TopoShape::accepts (PyObject *pyob) const;
}

#endif //PART_PYCXX_H
