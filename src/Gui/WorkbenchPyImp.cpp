/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "Workbench.h"
#include "WorkbenchManager.h"

// inclusion of the generated files (generated out of WorkbenchPy.xml)
#include "WorkbenchPy.h"
#include "WorkbenchPy.cpp"

using namespace Gui;

/** @class WorkbenchPy
 * The workbench Python base class doesn't allow you to manipulate the C++ workbench class behind.
 * You're only allowed either to activate the workbench class or get its name.
 * The WorkbenchPy class is associated to all C++ workbench classes except of PythonWorkbench.
 * @see Workbench
 * @see PythonWorkbench
 * @see PythonWorkbenchPy
 * @author Werner Mayer
 */

// returns a string which represent the object e.g. when printed in python
std::string WorkbenchPy::representation(void) const
{
    return std::string("<Workbench object>");
}

/** Retrieves the workbench name */
PyObject*  WorkbenchPy::name(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception

    PY_TRY {
        std::string name = getWorkbenchPtr()->name(); 
        PyObject* pyName = PyUnicode_FromString(name.c_str());

        return pyName;
    }PY_CATCH;
}

/** Activates the workbench object */
PyObject*  WorkbenchPy::activate(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                    // NULL triggers exception

    PY_TRY {
        std::string name = getWorkbenchPtr()->name(); 
        WorkbenchManager::instance()->activate( name, getWorkbenchPtr()->getTypeId().getName() );
        Py_Return; 
    }PY_CATCH;
}

PyObject *WorkbenchPy::getCustomAttributes(const char*) const
{
    return 0;
}

int WorkbenchPy::setCustomAttributes(const char*, PyObject *)
{
    return 0; 
}


