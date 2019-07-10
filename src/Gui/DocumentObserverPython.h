/***************************************************************************
 *   Copyright (c) 2018 Stefan Tröger <stefantroeger@gmx.net>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_DOCUMENTOBSERVERPYTHON_H
#define GUI_DOCUMENTOBSERVERPYTHON_H

#include "stdexport.h"
#include <CXX/Objects.hxx>

#include <boost/signals2.hpp>
#include <boost/bind.hpp>

namespace Gui
{

/**
 * The DocumentObserverPython class is used to notify registered Python instances
 * whenever something happens to a document, like creation, destruction, adding or
 * removing viewproviders or when viewprovider property changes. This is the equivalent to the app 
 * python document observer
*/
class GuiExport DocumentObserverPython
{

public:
    /// Constructor
    DocumentObserverPython(const Py::Object& obj);
    virtual ~DocumentObserverPython();

    static void addObserver(const Py::Object& obj);
    static void removeObserver(const Py::Object& obj);

private:   
    /** Checks if a new document was created */
    void slotCreatedDocument(const Gui::Document& Doc);
    /** Checks if the given document is about to be closed */
    void slotDeletedDocument(const Gui::Document& Doc);
    /** Checks if the given document is relabeled */
    void slotRelabelDocument(const Gui::Document& Doc);
    /** Checks if the given document is renamed */
    void slotRenameDocument(const Gui::Document& Doc);
    /** Checks if the given document is activated */
    void slotActivateDocument(const Gui::Document& Doc);
    /** Checks if a new object was added. */
    void slotCreatedObject(const Gui::ViewProvider& Obj);
    /** Checks if the given object is about to be removed. */
    void slotDeletedObject(const Gui::ViewProvider& Obj);
    /** The property of an observed object has changed */
    void slotChangedObject(const Gui::ViewProvider& Obj, const App::Property& Prop);
    /** The object was set into edit mode */
    void slotInEdit(const Gui::ViewProviderDocumentObject& Obj);
    /** The has left edit mode */
    void slotResetEdit(const Gui::ViewProviderDocumentObject& Obj);

private:
    Py::Object inst;
    static std::vector<DocumentObserverPython*> _instances;

    typedef boost::signals2::connection Connection;
    Connection connectApplicationCreatedDocument;
    Connection connectApplicationDeletedDocument;
    Connection connectApplicationRelabelDocument;
    Connection connectApplicationRenameDocument;
    Connection connectApplicationActivateDocument;
    Connection connectDocumentCreatedObject;
    Connection connectDocumentDeletedObject;
    Connection connectDocumentChangedObject;
    Connection connectDocumentObjectInEdit;
    Connection connectDocumentObjectResetEdit;
};

} //namespace Gui

#endif // GUI_DOCUMENTOBSERVERPYTHON_H
