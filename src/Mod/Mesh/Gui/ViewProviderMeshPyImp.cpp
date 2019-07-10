/***************************************************************************
 *   Copyright (c) 2018 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <sstream>

#include "Mod/Mesh/Gui/ViewProvider.h"

// inclusion of the generated files (generated out of ViewProviderMeshPy.xml)
#include "ViewProviderMeshPy.h"
#include "ViewProviderMeshPy.cpp"

using namespace MeshGui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderMeshPy::representation(void) const
{
    std::stringstream str;
    str << "<View provider object at " << getViewProviderDocumentObjectPtr() << ">";

    return str.str();
}

PyObject* ViewProviderMeshPy::setSelection(PyObject *args)
{
    PyObject* obj;
    if (!PyArg_ParseTuple(args, "O", &obj))
        return 0;

    Py::Sequence list(obj);
    std::vector<unsigned long> selection;
    selection.reserve(list.size());
    for (Py::Sequence::iterator it = list.begin(); it != list.end(); ++it) {
        Py::Long index(*it);
        unsigned long value = static_cast<unsigned long>(index);
        selection.push_back(value);
    }

    ViewProviderMesh* vp = getViewProviderMeshPtr();
    vp->setSelection(selection);
    Py_Return;
}

PyObject* ViewProviderMeshPy::addSelection(PyObject *args)
{
    PyObject* obj;
    if (!PyArg_ParseTuple(args, "O", &obj))
        return 0;

    Py::Sequence list(obj);
    std::vector<unsigned long> selection;
    selection.reserve(list.size());
    for (Py::Sequence::iterator it = list.begin(); it != list.end(); ++it) {
        Py::Long index(*it);
        unsigned long value = static_cast<unsigned long>(index);
        selection.push_back(value);
    }

    ViewProviderMesh* vp = getViewProviderMeshPtr();
    vp->addSelection(selection);
    Py_Return;
}

PyObject* ViewProviderMeshPy::removeSelection(PyObject *args)
{
    PyObject* obj;
    if (!PyArg_ParseTuple(args, "O", &obj))
        return 0;

    Py::Sequence list(obj);
    std::vector<unsigned long> selection;
    selection.reserve(list.size());
    for (Py::Sequence::iterator it = list.begin(); it != list.end(); ++it) {
        Py::Long index(*it);
        unsigned long value = static_cast<unsigned long>(index);
        selection.push_back(value);
    }

    ViewProviderMesh* vp = getViewProviderMeshPtr();
    vp->removeSelection(selection);
    Py_Return;
}

PyObject* ViewProviderMeshPy::invertSelection(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return 0;

    ViewProviderMesh* vp = getViewProviderMeshPtr();
    vp->invertSelection();
    Py_Return;
}

PyObject* ViewProviderMeshPy::clearSelection(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return 0;

    ViewProviderMesh* vp = getViewProviderMeshPtr();
    vp->clearSelection();
    Py_Return;
}



PyObject *ViewProviderMeshPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int ViewProviderMeshPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0;
}
