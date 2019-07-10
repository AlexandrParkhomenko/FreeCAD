/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel (juergen.riegel@web.de)              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include "FCConfig.h"

#include "Base/Console.h"
#include "Base/PyObjectBase.h"
#include "Base/Interpreter.h"
 

namespace MeshPart {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(MeshPart)
{
    // load dependent module
    try {
        Base::Interpreter().loadModule("Part");
        //Base::Interpreter().loadModule("Mesh");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(0);
    }
    PyObject* mod = MeshPart::initModule();
    Base::Console().Log("Loading MeshPart module... done\n");
    PyMOD_Return(mod);
}
