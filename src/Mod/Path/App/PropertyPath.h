/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PROPERTYPATH_H
#define PROPERTYPATH_H

#include "stdexport.h"
#include "Path.h"
#include "App/Property.h"

namespace Path
{


/** The path property class.  */
class Standard_EXPORT PropertyPath : public App::Property
{
    TYPESYSTEM_HEADER();

public:
    PropertyPath();
    ~PropertyPath();

    /** @name Getter/setter */
    //@{
    /// set the part shape
    void setValue(const Toolpath&);
    /// get the part shape
    const Toolpath &getValue(void) const;
    //@}

    /** @name Python interface */
    //@{
    PyObject* getPyObject(void);
    void setPyObject(PyObject *value);
    //@}

    /** @name Save/restore */
    //@{
    void Save (Base::Writer &writer) const;
    void Restore(Base::XMLReader &reader);
    void SaveDocFile (Base::Writer &writer) const;
    void RestoreDocFile(Base::Reader &reader);

    App::Property *Copy(void) const;
    void Paste(const App::Property &from);
    unsigned int getMemSize (void) const;
    //@}

private:
    Toolpath _Path;
};


} //namespace Path


#endif // PROPERTYPATH_H
