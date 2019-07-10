/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2002                        *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 *   Juergen Riegel 2002                                                   *
 ***************************************************************************/



#include "Base/Console.h"
#include "Base/Interpreter.h"
#include "StepShapePy.h"
#include "StepShape.h"

namespace Import {
    extern PyObject* initModule();
}

PyMOD_INIT_FUNC(Import)
{
    PyObject* importModule = Import::initModule();

    try {
        Base::Interpreter().loadModule("Part");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(0);
    }

    // add mesh elements
    Base::Interpreter().addType(&Import::StepShapePy  ::Type, importModule, "StepShape");

        // init Type system
    //Import::StepShape       ::init();

    Base::Console().Log("Loading Import module... done\n");
    PyMOD_Return(importModule);
}
