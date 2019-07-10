/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


# include "FCConfig.h"

#include "Base/Console.h"
#include "Base/PyObjectBase.h"
#include "Base/Interpreter.h"

#include "Command.h"
#include "CommandPy.h"
#include "Path.h"
#include "PathPy.h"
#include "Tooltable.h"
#include "ToolPy.h"
#include "TooltablePy.h"
#include "PropertyPath.h"
#include "FeaturePath.h"
#include "PropertyTool.h"
#include "PropertyTooltable.h"
#include "FeaturePathCompound.h"
#include "FeaturePathShape.h"
#include "AreaPy.h"
#include "FeatureArea.h"

namespace Path {
extern PyObject* initModule();
}

/* Python entry */
PyMOD_INIT_FUNC(Path)
{
    // load dependent module
    try {
        Base::Interpreter().runString("import Part");
    }
    catch(const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(NULL);
    }

    PyObject* pathModule = Path::initModule();
    Base::Console().Log("Loading Path module... done\n");

    // Add Types to module
    Base::Interpreter().addType(&Path::CommandPy    ::Type, pathModule, "Command");
    Base::Interpreter().addType(&Path::PathPy       ::Type, pathModule, "Path");
    Base::Interpreter().addType(&Path::ToolPy       ::Type, pathModule, "Tool");
    Base::Interpreter().addType(&Path::TooltablePy  ::Type, pathModule, "Tooltable");
    Base::Interpreter().addType(&Path::AreaPy       ::Type, pathModule, "Area");

    // NOTE: To finish the initialization of our own type objects we must
    // call PyType_Ready, otherwise we run into a segmentation fault, later on.
    // This function is responsible for adding inherited slots from a type's base class.
    Path::Command                ::init();
    Path::Toolpath               ::init();
    Path::Tool                   ::init();
    Path::Tooltable              ::init();
    Path::PropertyPath           ::init();
    Path::Feature                ::init();
    Path::FeaturePython          ::init();
    Path::PropertyTool           ::init();
    Path::PropertyTooltable      ::init();
    Path::FeatureCompound        ::init();
    Path::FeatureCompoundPython  ::init();
    Path::FeatureShape           ::init();
    Path::FeatureShapePython     ::init();
    Path::Area                   ::init();
    Path::FeatureArea            ::init();
    Path::FeatureAreaPython      ::init();
    Path::FeatureAreaView        ::init();
    Path::FeatureAreaViewPython  ::init();

    PyMOD_Return(pathModule);
}
