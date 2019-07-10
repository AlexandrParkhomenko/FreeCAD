/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include "View.h"
#include "Document.h"
#include "Application.h"

using namespace Gui;

//**************************************************************************
// BaseView
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE_ABSTRACT(Gui::BaseView,Base::BaseClass);


BaseView::BaseView( Gui::Document* pcDocument)
  :_pcDocument(pcDocument), bIsDetached(false)
{
    if (pcDocument){
        pcDocument->attachView(this);
        bIsPassive = false;
    }
    else{
        Application::Instance->attachView(this);
        bIsPassive = true;
    }
}

BaseView::~BaseView()
{
    onClose();
}

void BaseView::onClose(void)
{
    if (bIsDetached)
        return;

    if (bIsPassive) {
        Application::Instance->detachView(this);
        if (_pcDocument)
            _pcDocument->detachView(this, true);
    }
    else {
        if (_pcDocument)
            _pcDocument->detachView(this);
    }

    _pcDocument = 0;
    bIsDetached = true;
}

void BaseView::deleteSelf()
{
    delete this;
}

void BaseView::setDocument(Gui::Document* pcDocument)
{
    if (_pcDocument == pcDocument)
        return;
    // detaches and attaches the observer
    if (_pcDocument)
        _pcDocument->detachView(this, true);
    if (pcDocument)
        pcDocument->attachView(this,true);	

    // set the new document as the active one
    _pcDocument = pcDocument;
}

/// returns the document the view is attached to
App::Document* BaseView::getAppDocument() const
{
    return _pcDocument ? _pcDocument->getDocument() : 0;
}
