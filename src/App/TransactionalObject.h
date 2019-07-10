/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_TRANSACTIONALOBJECT_H
#define APP_TRANSACTIONALOBJECT_H

#include "stdexport.h"
#include "App/ExtensionContainer.h"

namespace App
{

class Document;
class TransactionObject;

/** Base class of transactional objects
 */
class AppExport TransactionalObject : public App::ExtensionContainer
{
    PROPERTY_HEADER(App::TransactionalObject);

public:
    /// Constructor
    TransactionalObject(void);
    virtual ~TransactionalObject();
    virtual bool isAttachedToDocument() const;
    virtual const char* detachFromDocument();

    virtual App::Property* addDynamicProperty(
          const char*, const char* = 0,
          const char* = 0, const char* = 0,
          short = 0, bool = false, bool = false);
    virtual bool removeDynamicProperty(const char*);

protected:
    void onBeforeChangeProperty(Document *doc, const Property *prop);
};

} //namespace App


#endif // APP_TRANSACTIONALOBJECT_H
