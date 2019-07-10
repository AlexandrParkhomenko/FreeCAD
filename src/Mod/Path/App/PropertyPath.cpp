/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <sstream>


#include "App/DocumentObject.h"
#include "App/PropertyContainer.h"
#include "Base/Console.h"
#include "Base/Writer.h"
#include "Base/Reader.h"
#include "Base/Exception.h"
#include "Base/FileInfo.h"
#include "Base/Stream.h"

#include "PropertyPath.h"
#include "PathPy.h"

using namespace Path;

TYPESYSTEM_SOURCE(Path::PropertyPath, App::Property);

PropertyPath::PropertyPath()
{
}

PropertyPath::~PropertyPath()
{
}

void PropertyPath::setValue(const Toolpath& pa)
{
    aboutToSetValue();
    _Path = pa;
    hasSetValue();
}


const Toolpath &PropertyPath::getValue(void)const 
{
    return _Path;
}

PyObject *PropertyPath::getPyObject(void)
{
    return new PathPy(new Toolpath(_Path));
}

void PropertyPath::setPyObject(PyObject *value)
{
    if (PyObject_TypeCheck(value, &(PathPy::Type))) {
        PathPy *pcObject = static_cast<PathPy*>(value);
        setValue(*pcObject->getToolpathPtr());
    }
    else {
        std::string error = std::string("type must be 'Path', not ");
        error += value->ob_type->tp_name;
        throw Base::TypeError(error);
    }
}

App::Property *PropertyPath::Copy(void) const
{
    PropertyPath *prop = new PropertyPath();
    prop->_Path = this->_Path;
 
    return prop;
}

void PropertyPath::Paste(const App::Property &from)
{
    aboutToSetValue();
    _Path = dynamic_cast<const PropertyPath&>(from)._Path;
    hasSetValue();
}

unsigned int PropertyPath::getMemSize (void) const
{
    return _Path.getMemSize();
}

void PropertyPath::Save (Base::Writer &writer) const
{
    _Path.Save(writer);
}

void PropertyPath::Restore(Base::XMLReader &reader)
{
    reader.readElement("Path");

    std::string file (reader.getAttribute("file") );
    if (!file.empty()) {
        // initiate a file read
        reader.addFile(file.c_str(),this);
    }

    if (reader.hasAttribute("version")) {
        int version = reader.getAttributeAsInteger("version");
        if (version >= Toolpath::SchemaVersion) {
            reader.readElement("Center");
            double x = reader.getAttributeAsFloat("x");
            double y = reader.getAttributeAsFloat("y");
            double z = reader.getAttributeAsFloat("z");
            Base::Vector3d center(x, y, z);
            _Path.setCenter(center);
        }
    }
}

void PropertyPath::SaveDocFile (Base::Writer &) const
{
    // does nothing
}

void PropertyPath::RestoreDocFile(Base::Reader &reader)
{
    App::PropertyContainer *container = getContainer();
    App::DocumentObject *obj = 0;
    if (container->isDerivedFrom(App::DocumentObject::getClassTypeId())) {
        obj = static_cast<App::DocumentObject*>(container);
    }

    if (obj) {
        obj->setStatus(App::ObjectStatus::Restore, true);
    }

    aboutToSetValue();
    _Path.RestoreDocFile(reader);
    hasSetValue();

    if (obj) {
        obj->setStatus(App::ObjectStatus::Restore, false);
    }
}



