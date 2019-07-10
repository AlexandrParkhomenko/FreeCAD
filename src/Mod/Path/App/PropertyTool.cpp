/***************************************************************************
 *   Copyright (c) Yorik van Havre (yorik@uncreated.net) 2014              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <sstream>


#include "Base/Console.h"
#include "Base/Writer.h"
#include "Base/Reader.h"
#include "Base/Exception.h"
#include "Base/FileInfo.h"
#include "Base/Stream.h"

#include "PropertyTool.h"
#include "ToolPy.h"

using namespace Path;

TYPESYSTEM_SOURCE(Path::PropertyTool, App::Property);

PropertyTool::PropertyTool()
{
}

PropertyTool::~PropertyTool()
{
}

void PropertyTool::setValue(const Tool& tt)
{
    aboutToSetValue();
    _Tool = tt;
    hasSetValue();
}


const Tool &PropertyTool::getValue(void)const 
{
    return _Tool;
}

PyObject *PropertyTool::getPyObject(void)
{
    return new ToolPy(new Tool(_Tool));
}

void PropertyTool::setPyObject(PyObject *value)
{
    if (PyObject_TypeCheck(value, &(ToolPy::Type))) {
        ToolPy *pcObject = static_cast<ToolPy*>(value);
        setValue(*pcObject->getToolPtr());
    }
    else {
        std::string error = std::string("type must be 'Tool', not ");
        error += value->ob_type->tp_name;
        throw Base::TypeError(error);
    }
}

App::Property *PropertyTool::Copy(void) const
{
    PropertyTool *prop = new PropertyTool();
    prop->_Tool = this->_Tool;
 
    return prop;
}

void PropertyTool::Paste(const App::Property &from)
{
    aboutToSetValue();
    _Tool = dynamic_cast<const PropertyTool&>(from)._Tool;
    hasSetValue();
}

unsigned int PropertyTool::getMemSize (void) const
{
    return _Tool.getMemSize();
}

void PropertyTool::Save (Base::Writer &writer) const
{
    _Tool.Save(writer);
}

void PropertyTool::Restore(Base::XMLReader &reader)
{
    Path::Tool temp;
    temp.Restore(reader);
    setValue(temp);
}


