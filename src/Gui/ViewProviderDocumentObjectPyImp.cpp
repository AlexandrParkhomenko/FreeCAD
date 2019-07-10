/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <sstream>

#include "Gui/ViewProviderDocumentObject.h"
#include "Gui/Document.h"
#include "App/DocumentObject.h"

// inclusion of the generated files (generated out of ViewProviderDocumentObjectPy.xml)
#include "ViewProviderDocumentObjectPy.h"
#include "ViewProviderDocumentObjectPy.cpp"

using namespace Gui;

// returns a string which represents the object e.g. when printed in python
std::string ViewProviderDocumentObjectPy::representation(void) const
{
    std::stringstream str;
    str << "<View provider object at " << getViewProviderDocumentObjectPtr() << ">";

    return str.str();
}

PyObject* ViewProviderDocumentObjectPy::update(PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))     // convert args: Python->C 
        return NULL;                       // NULL triggers exception 
    PY_TRY {
        getViewProviderDocumentObjectPtr()->updateView();
        Py_Return;
    } PY_CATCH;
}

Py::Object ViewProviderDocumentObjectPy::getObject(void) const
{
    App::DocumentObject* obj = getViewProviderDocumentObjectPtr()->getObject();
    return Py::Object(obj->getPyObject(), true); // do not inc'ref twice
}

Py::Object ViewProviderDocumentObjectPy::getDocument(void) const
{
    Document* doc = getViewProviderDocumentObjectPtr()->getDocument();
    return Py::asObject(doc->getPyObject()); // do not inc'ref twice
}

PyObject *ViewProviderDocumentObjectPy::getCustomAttributes(const char* /*attr*/) const
{
    return 0;
}

int ViewProviderDocumentObjectPy::setCustomAttributes(const char* /*attr*/, PyObject* /*obj*/)
{
    return 0; 
}
