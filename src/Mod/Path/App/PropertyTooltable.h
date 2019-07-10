/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef PROPERTYTOOLTABLE_H
#define PROPERTYTOOLTABLE_H

#include "stdexport.h"
#include "Tooltable.h"
#include "App/Property.h"

namespace Path
{


/** The tooltable property class.  */
class Standard_EXPORT PropertyTooltable : public App::Property
{
    TYPESYSTEM_HEADER();

public:
    PropertyTooltable();
    ~PropertyTooltable();

    /** @name Getter/setter */
    //@{
    /// set the part shape
    void setValue(const Tooltable&);
    /// get the part shape
    const Tooltable &getValue(void) const;
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

    App::Property *Copy(void) const;
    void Paste(const App::Property &from);
    unsigned int getMemSize (void) const;
    //@}

private:
    Tooltable _Tooltable;
};


} //namespace Path


#endif // PROPERTYTOOLTABLE_H
