/***************************************************************************
 *   Copyright (c) 2008 Jürgen Riegel (juergen.riegel@web.de)              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include "FCConfig.h"

#include "Base/Console.h"
#include "Base/Interpreter.h"

#include "SketchObjectSF.h"
#include "SketchObject.h"
#include "Constraint.h"
#include "Sketch.h"
#include "ConstraintPy.h"
#include "SketchPy.h"
#include "PropertyConstraintList.h"


namespace Sketcher {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(Sketcher)
{
    // load dependent module
    try {
        Base::Interpreter().runString("import Part");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(0);
    }

    PyObject* sketcherModule = Sketcher::initModule();

    // Add Types to module
    Base::Interpreter().addType(&Sketcher::ConstraintPy  ::Type,sketcherModule,"Constraint");
    Base::Interpreter().addType(&Sketcher::SketchPy      ::Type,sketcherModule,"Sketch");


    // NOTE: To finish the initialization of our own type objects we must
    // call PyType_Ready, otherwise we run into a segmentation fault, later on.
    // This function is responsible for adding inherited slots from a type's base class.
 
    Sketcher::SketchObjectSF        ::init();
    Sketcher::SketchObject          ::init();
    Sketcher::SketchObjectPython    ::init();
    Sketcher::Sketch                ::init();
    Sketcher::Constraint            ::init();
    Sketcher::PropertyConstraintList::init();

    Base::Console().Log("Loading Sketcher module... done\n");

    PyMOD_Return(sketcherModule);
}
