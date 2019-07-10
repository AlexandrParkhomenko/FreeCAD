/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <sstream>


#include "Base/Console.h"
#include "Base/Writer.h"
#include "Base/Reader.h"
#include "Base/Exception.h"
#include "Base/FileInfo.h"
#include "Base/Stream.h"

#include "PropertyTooltable.h"
#include "TooltablePy.h"

using namespace Path;

TYPESYSTEM_SOURCE(Path::PropertyTooltable, App::Property);

PropertyTooltable::PropertyTooltable()
{
}

PropertyTooltable::~PropertyTooltable()
{
}

void PropertyTooltable::setValue(const Tooltable& tt)
{
    aboutToSetValue();
    _Tooltable = tt;
    hasSetValue();
}


const Tooltable &PropertyTooltable::getValue(void)const 
{
    return _Tooltable;
}

PyObject *PropertyTooltable::getPyObject(void)
{
    return new TooltablePy(new Tooltable(_Tooltable));
}

void PropertyTooltable::setPyObject(PyObject *value)
{
    if (PyObject_TypeCheck(value, &(TooltablePy::Type))) {
        TooltablePy *pcObject = static_cast<TooltablePy*>(value);
        setValue(*pcObject->getTooltablePtr());
    }
    else {
        std::string error = std::string("type must be 'Tooltable', not ");
        error += value->ob_type->tp_name;
        throw Base::TypeError(error);
    }
}

App::Property *PropertyTooltable::Copy(void) const
{
    PropertyTooltable *prop = new PropertyTooltable();
    prop->_Tooltable = this->_Tooltable;
 
    return prop;
}

void PropertyTooltable::Paste(const App::Property &from)
{
    aboutToSetValue();
    _Tooltable = dynamic_cast<const PropertyTooltable&>(from)._Tooltable;
    hasSetValue();
}

unsigned int PropertyTooltable::getMemSize (void) const
{
    return _Tooltable.getMemSize();
}

void PropertyTooltable::Save (Base::Writer &writer) const
{
    _Tooltable.Save(writer);
}

void PropertyTooltable::Restore(Base::XMLReader &reader)
{
    Path::Tooltable temp;
    temp.Restore(reader);
    setValue(temp);
}


