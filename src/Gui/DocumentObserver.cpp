/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

# include <sstream>

#include <boost/bind/bind.hpp>

#include "Application.h"
#include "Document.h"
#include "ViewProviderDocumentObject.h"
#include "DocumentObserver.h"
#include "App/Document.h"

using namespace Gui;
namespace bp = boost::placeholders;


DocumentT::DocumentT()
{
}

DocumentT::DocumentT(Document* doc)
{
    document = doc->getDocument()->getName();
}

DocumentT::DocumentT(const std::string& name)
{
    document = name;
}

DocumentT::~DocumentT()
{
}

void DocumentT::operator=(const DocumentT& doc)
{
    if (this == &doc)
        return;
    document = doc.document;
}

void DocumentT::operator=(const Document* doc)
{
    document = doc->getDocument()->getName();
}

void DocumentT::operator=(const std::string& name)
{
    document = name;
}

Document* DocumentT::getDocument() const
{
    return Application::Instance->getDocument(document.c_str());
}

std::string DocumentT::getDocumentName() const
{
    return document;
}

std::string DocumentT::getGuiDocumentPython() const
{
    std::stringstream str;
    Document* doc = Application::Instance->activeDocument();
    if (doc && document == doc->getDocument()->getName()) {
        str << "Gui.ActiveDocument";
    }
    else {
        str << "Gui.getDocument(\""
            << document
            << "\")";
    }
    return str.str();
}

std::string DocumentT::getAppDocumentPython() const
{
    std::stringstream str;
    Document* doc = Application::Instance->activeDocument();
    if (doc && document == doc->getDocument()->getName()) {
        str << "App.ActiveDocument";
    }
    else {
        str << "App.getDocument(\""
            << document
            << "\")";
    }
    return str.str();
}

// -----------------------------------------------------------------------------

ViewProviderT::ViewProviderT()
{
}

ViewProviderT::ViewProviderT(ViewProviderDocumentObject* obj)
{
    object = obj->getObject()->getNameInDocument();
    document = obj->getObject()->getDocument()->getName();
}

ViewProviderT::~ViewProviderT()
{
}

void ViewProviderT::operator=(const ViewProviderT& obj)
{
    if (this == &obj)
        return;
    object = obj.object;
    document = obj.document;
}

void ViewProviderT::operator=(const ViewProviderDocumentObject* obj)
{
    object = obj->getObject()->getNameInDocument();
    document = obj->getObject()->getDocument()->getName();
}

Document* ViewProviderT::getDocument() const
{
    return Application::Instance->getDocument(document.c_str());
}

std::string ViewProviderT::getDocumentName() const
{
    return document;
}

std::string ViewProviderT::getGuiDocumentPython() const
{
    DocumentT doct(document);
    return doct.getGuiDocumentPython();
}

std::string ViewProviderT::getAppDocumentPython() const
{
    DocumentT doct(document);
    return doct.getAppDocumentPython();
}

ViewProviderDocumentObject* ViewProviderT::getViewProvider() const
{
    ViewProviderDocumentObject* obj = 0;
    Document* doc = getDocument();
    if (doc) {
        obj = dynamic_cast<ViewProviderDocumentObject*>(doc->getViewProviderByName(object.c_str()));
    }
    return obj;
}

std::string ViewProviderT::getObjectName() const
{
    return object;
}

std::string ViewProviderT::getObjectPython() const
{
    std::stringstream str;
    Document* doc = Application::Instance->activeDocument();
    if (doc && document == doc->getDocument()->getName()) {
        str << "Gui.ActiveDocument.";
    }
    else {
        str << "Gui.getDocument(\""
            << document
            << "\").";
    }

    str << object;
    return str.str();
}

// -----------------------------------------------------------------------------

DocumentObserver::DocumentObserver()
{
}

DocumentObserver::~DocumentObserver()
{
}

void DocumentObserver::attachDocument(Document* doc)
{
    detachDocument();

    if (doc == nullptr)
        return;

    this->connectDocumentCreatedObject = doc->signalNewObject.connect(boost::bind
        (&DocumentObserver::slotCreatedObject, this, bp::_1));
    this->connectDocumentDeletedObject = doc->signalDeletedObject.connect(boost::bind
        (&DocumentObserver::slotDeletedObject, this, bp::_1));
    this->connectDocumentChangedObject = doc->signalChangedObject.connect(boost::bind
        (&DocumentObserver::slotChangedObject, this, bp::_1, bp::_2));
    this->connectDocumentRelabelObject = doc->signalRelabelObject.connect(boost::bind
        (&DocumentObserver::slotRelabelObject, this, bp::_1));
    this->connectDocumentActivateObject = doc->signalActivatedObject.connect(boost::bind
        (&DocumentObserver::slotActivatedObject, this, bp::_1));
    this->connectDocumentEditObject = doc->signalInEdit.connect(boost::bind
        (&DocumentObserver::slotEnterEditObject, this, bp::_1));
    this->connectDocumentResetObject = doc->signalResetEdit.connect(boost::bind
        (&DocumentObserver::slotResetEditObject, this, bp::_1));
    this->connectDocumentUndo = doc->signalUndoDocument.connect(boost::bind
        (&DocumentObserver::slotUndoDocument, this, bp::_1));
    this->connectDocumentRedo = doc->signalRedoDocument.connect(boost::bind
        (&DocumentObserver::slotRedoDocument, this, bp::_1));
    this->connectDocumentDelete = doc->signalDeleteDocument.connect(boost::bind
        (&DocumentObserver::slotDeleteDocument, this, bp::_1));
}

void DocumentObserver::detachDocument()
{
    this->connectDocumentCreatedObject.disconnect();
    this->connectDocumentDeletedObject.disconnect();
    this->connectDocumentChangedObject.disconnect();
    this->connectDocumentRelabelObject.disconnect();
    this->connectDocumentActivateObject.disconnect();
    this->connectDocumentEditObject.disconnect();
    this->connectDocumentResetObject.disconnect();
    this->connectDocumentUndo.disconnect();
    this->connectDocumentRedo.disconnect();
    this->connectDocumentDelete.disconnect();
}

void DocumentObserver::slotUndoDocument(const Document& /*Doc*/)
{
}

void DocumentObserver::slotRedoDocument(const Document& /*Doc*/)
{
}

void DocumentObserver::slotDeleteDocument(const Document& /*Doc*/)
{
}

void DocumentObserver::slotCreatedObject(const ViewProviderDocumentObject& /*Obj*/)
{
}

void DocumentObserver::slotDeletedObject(const ViewProviderDocumentObject& /*Obj*/)
{
}

void DocumentObserver::slotChangedObject(const ViewProviderDocumentObject& /*Obj*/,
                                         const App::Property& /*Prop*/)
{
}

void DocumentObserver::slotRelabelObject(const ViewProviderDocumentObject& /*Obj*/)
{
}

void DocumentObserver::slotActivatedObject(const ViewProviderDocumentObject& /*Obj*/)
{
}

void DocumentObserver::slotEnterEditObject(const ViewProviderDocumentObject& /*Obj*/)
{
}

void DocumentObserver::slotResetEditObject(const ViewProviderDocumentObject& /*Obj*/)
{
}
