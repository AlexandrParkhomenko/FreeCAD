/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2010     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef APP_PropertyGeometryList_H
#define APP_PropertyGeometryList_H


#include "stdexport.h"
#include <vector>
#include <string>
#include "App/Property.h"
#include "Geometry.h"

namespace Base {
class Writer;
}

namespace Part
{
class Geometry;

class Standard_EXPORT PropertyGeometryList: public App::PropertyLists
{
    TYPESYSTEM_HEADER();

public:
    /**
     * A constructor.
     * A more elaborate description of the constructor.
     */
    PropertyGeometryList();

    /**
     * A destructor.
     * A more elaborate description of the destructor.
     */
    virtual ~PropertyGeometryList();

    virtual void setSize(int newSize);
    virtual int getSize(void) const;

    /** Sets the property
     */
    void setValue(const Geometry*);
    void setValues(const std::vector<Geometry*>&);

    /// index operator
    const Geometry *operator[] (const int idx) const {
        return _lValueList[idx];
    }

    const std::vector<Geometry*> &getValues(void) const {
        return _lValueList;
    }

    virtual PyObject *getPyObject(void);
    virtual void setPyObject(PyObject *);

    virtual void Save(Base::Writer &writer) const;
    virtual void Restore(Base::XMLReader &reader);

    virtual App::Property *Copy(void) const;
    virtual void Paste(const App::Property &from);

    virtual unsigned int getMemSize(void) const;

private:
    std::vector<Geometry*> _lValueList;
};

} // namespace Part


#endif // APP_PropertyGeometryList_H
