/***************************************************************************
 *   Copyright (c) 2016 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_TRANSACTIONOBJECT_H
#define GUI_TRANSACTIONOBJECT_H

#include "App/Transactions.h"

namespace Gui
{
class TransactionViewProvider : public App::TransactionObject
{
    TYPESYSTEM_HEADER();

public:
    TransactionViewProvider();
    virtual ~TransactionViewProvider();

    void applyNew(App::Document& Doc, App::TransactionalObject* pcObj);
    void applyDel(App::Document& Doc, App::TransactionalObject* pcObj);
};

} //namespace Gui


#endif // GUI_TRANSACTIONOBJECT_H
