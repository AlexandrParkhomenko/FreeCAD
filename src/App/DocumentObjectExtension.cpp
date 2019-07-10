/***************************************************************************
 *   Copyright (c) Stefan Tröger          (stefantroeger@gmx.net) 2016     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <cassert>
# include <algorithm>

#include "DocumentObjectExtension.h"
#include "DocumentObjectExtensionPy.h"

using namespace App;

EXTENSION_PROPERTY_SOURCE(App::DocumentObjectExtension, App::Extension)

DocumentObjectExtension::DocumentObjectExtension() 
{
    initExtensionType(App::DocumentObjectExtension::getExtensionClassTypeId());
}

DocumentObjectExtension::~DocumentObjectExtension()
{

}

short int DocumentObjectExtension::extensionMustExecute(void) {
    
    return 0;
}

App::DocumentObjectExecReturn* DocumentObjectExtension::extensionExecute(void) {

    return App::DocumentObject::StdReturn;
}

void DocumentObjectExtension::onExtendedSettingDocument() {

}

void DocumentObjectExtension::onExtendedDocumentRestored() {

}

void DocumentObjectExtension::onExtendedSetupObject() {
    
}

void DocumentObjectExtension::onExtendedUnsetupObject() {
    
}

PyObject* DocumentObjectExtension::getExtensionPyObject(void) {
    
    if (ExtensionPythonObject.is(Py::_None())){
        // ref counter is set to 1
        ExtensionPythonObject = Py::Object(new DocumentObjectExtensionPy(this),true);
    }
    return Py::new_reference_to(ExtensionPythonObject);
}

const DocumentObject* DocumentObjectExtension::getExtendedObject() const {

    assert(getExtendedContainer()->isDerivedFrom(DocumentObject::getClassTypeId())); 
    return static_cast<const DocumentObject*>(getExtendedContainer());
}

DocumentObject* DocumentObjectExtension::getExtendedObject() {

    assert(getExtendedContainer()->isDerivedFrom(DocumentObject::getClassTypeId())); 
    return static_cast<DocumentObject*>(getExtendedContainer());
}
