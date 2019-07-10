/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_PROPERTYPYTHONOBJECT_H
#define APP_PROPERTYPYTHONOBJECT_H

#include "stdexport.h"
#include <string>
#include <list>
#include <vector>
#include <CXX/Objects.hxx>

#include "Property.h"


namespace Base {
class Writer;
class XMLReader;
}

namespace App
{

/**
 * PropertyPythonObject is used to manage Py::Object instances as properties.
 * @author Werner Mayer
 */
class AppExport PropertyPythonObject : public Property
{
    TYPESYSTEM_HEADER();

public:
    PropertyPythonObject(void);
    virtual ~PropertyPythonObject();

    void setValue(Py::Object);
    Py::Object getValue() const;

    virtual PyObject *getPyObject(void);
    virtual void setPyObject(PyObject *);

    /** Use Python's pickle module to save the object */
    virtual void Save (Base::Writer &writer) const;
    /** Use Python's pickle module to restore the object */
    virtual void Restore(Base::XMLReader &reader);
    virtual void SaveDocFile (Base::Writer &writer) const;
    virtual void RestoreDocFile(Base::Reader &reader);

    virtual unsigned int getMemSize (void) const;
    virtual Property *Copy(void) const;
    virtual void Paste(const Property &from);

    std::string toString() const;
    void fromString(const std::string&);

private:
    void saveObject(Base::Writer &writer) const;
    void restoreObject(Base::XMLReader &reader);
    std::string encodeValue(const std::string& str) const;
    std::string decodeValue(const std::string& str) const;
    void loadPickle(const std::string& str);
    Py::Object object;
};


} // namespace App

#endif // APP_PROPERTYPYTHONOBJECT_H
