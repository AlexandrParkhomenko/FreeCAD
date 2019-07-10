/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/




#include "Application.h"
#include "Document.h"
#include "TransactionObject.h"
#include "ViewProviderDocumentObject.h"
#include "App/Document.h"

using namespace Gui;


TYPESYSTEM_SOURCE_ABSTRACT(Gui::TransactionViewProvider, App::TransactionObject)

TransactionViewProvider::TransactionViewProvider()
{
}

TransactionViewProvider::~TransactionViewProvider()
{
}

void TransactionViewProvider::applyNew(App::Document& Doc, App::TransactionalObject* pcObj)
{
    if (status == New) {
        Gui::Document* doc = Application::Instance->getDocument(&Doc);
        if (doc) {
            doc->addViewProvider(static_cast<ViewProviderDocumentObject*>(pcObj));
        }
    }
}

void TransactionViewProvider::applyDel(App::Document& Doc, App::TransactionalObject* pcObj)
{
    // nothing to do here
    Q_UNUSED(Doc); 
    Q_UNUSED(pcObj); 
}
