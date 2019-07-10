/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PROPERTYTOOL_H
#define PROPERTYTOOL_H

#include "stdexport.h"
#include "Tooltable.h"
#include "App/Property.h"

namespace Path
{


/** The tool property class.  */
class Standard_EXPORT PropertyTool : public App::Property
{
    TYPESYSTEM_HEADER();

public:
    PropertyTool();
    ~PropertyTool();

    /** @name Getter/setter */
    //@{
    /// set the part shape
    void setValue(const Tool&);
    /// get the part shape
    const Tool &getValue(void) const;
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
    Tool _Tool;
};


} //namespace Path


#endif // PROPERTYTOOL_H
