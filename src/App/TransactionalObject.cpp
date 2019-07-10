/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <sstream>

#include "Base/Writer.h"
#include "Base/Exception.h"

#include "Document.h"
#include "TransactionalObject.h"

using namespace App;


PROPERTY_SOURCE_ABSTRACT(App::TransactionalObject, App::ExtensionContainer)

TransactionalObject::TransactionalObject(void)
{
}

TransactionalObject::~TransactionalObject(void)
{
}

bool TransactionalObject::isAttachedToDocument() const
{
    return false;
}

const char* TransactionalObject::detachFromDocument()
{
    return "";
}

void TransactionalObject::onBeforeChangeProperty(Document *doc, const Property *prop)
{
    doc->onBeforeChangeProperty(this, prop);
}

App::Property* TransactionalObject::addDynamicProperty(const char*, const char*,
                                                       const char*, const char*,
                                                       short, bool, bool)
{
    std::stringstream str;
    str << "Type " << this->getTypeId().getName() << " cannot dynamically add properties";
    throw Base::RuntimeError(str.str());
}

bool TransactionalObject::removeDynamicProperty(const char*)
{
    std::stringstream str;
    str << "Type " << this->getTypeId().getName() << " cannot dynamically remove properties";
    throw Base::RuntimeError(str.str());
}
