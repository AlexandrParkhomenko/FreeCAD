/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef APP_DOCUMENTOBSERVERPYTHON_H
#define APP_DOCUMENTOBSERVERPYTHON_H

#include "stdexport.h"
#include <CXX/Objects.hxx>

#include <boost/signals2.hpp>
#include <boost/bind.hpp>

namespace App
{

/**
 * The DocumentObserverPython class is used to notify registered Python instances
 * whenever something happens to a document, like creation, destruction, adding or
 * removing objects or when property changes.
 *
 * @author Werner Mayer
 */
class AppExport DocumentObserverPython
{

public:
    /// Constructor
    DocumentObserverPython(const Py::Object& obj);
    virtual ~DocumentObserverPython();

    static void addObserver(const Py::Object& obj);
    static void removeObserver(const Py::Object& obj);

private:
    /** Checks if a new document was created */
    void slotCreatedDocument(const App::Document& Doc);
    /** Checks if the given document is about to be closed */
    void slotDeletedDocument(const App::Document& Doc);
    /** Checks if the given document is relabeled */
    void slotRelabelDocument(const App::Document& Doc);
    /** Checks if the given document is activated */
    void slotActivateDocument(const App::Document& Doc);
    /** The property of an observed document has changed */
    void slotBeforeChangeDocument(const App::Document& Obj, const App::Property& Prop);
    /** The property of an observed document has changed */
    void slotChangedDocument(const App::Document& Obj, const App::Property& Prop);
    /** Checks if a new object was added. */
    void slotCreatedObject(const App::DocumentObject& Obj);
    /** Checks if the given object is about to be removed. */
    void slotDeletedObject(const App::DocumentObject& Obj);
    /** The property of an observed object has changed */
    void slotBeforeChangeObject(const App::DocumentObject& Obj, const App::Property& Prop);
    /** The property of an observed object has changed */
    void slotChangedObject(const App::DocumentObject& Obj, const App::Property& Prop);
    /** Undoes the last transaction of the document */
    void slotUndoDocument(const App::Document& Doc);
    /** Redoes the last undone transaction of the document */
    void slotRedoDocument(const App::Document& Doc);
    /** Called when a given object is recomputed */
    void slotRecomputedObject(const App::DocumentObject& Obj);
    /** Called when an observed document is recomputed */
    void slotRecomputedDocument(const App::Document& Doc);
    /** Called when an observed document opens a transaction */
    void slotOpenTransaction(const App::Document& Doc, std::string str);
    /** Called when an observed document commits a transaction */
    void slotCommitTransaction(const App::Document& Doc);
    /** Called when an observed document aborts a transaction */
    void slotAbortTransaction(const App::Document& Doc);
    /** Called when an object gets a new dynamic property added*/
    void slotAppendDynamicProperty(const App::Property& Prop);
    /** Called when an object gets a dynamic property removed*/
    void slotRemoveDynamicProperty(const App::Property& Prop);
    /** Called when an object property gets a new editor relevant status like hidden or read only*/
    void slotChangePropertyEditor(const App::Property& Prop);
    /** Called when a document is about to be saved*/
    void slotStartSaveDocument(const App::Document&, const std::string&);
    /** Called when an document has been saved*/
    void slotFinishSaveDocument(const App::Document&, const std::string&);

private:
    Py::Object inst;
    static std::vector<DocumentObserverPython*> _instances;

    typedef boost::signals2::connection Connection;
    Connection connectApplicationCreatedDocument;
    Connection connectApplicationDeletedDocument;
    Connection connectApplicationRelabelDocument;
    Connection connectApplicationActivateDocument;
    Connection connectApplicationUndoDocument;
    Connection connectApplicationRedoDocument;
    Connection connectDocumentBeforeChange;
    Connection connectDocumentChanged;
    Connection connectDocumentCreatedObject;
    Connection connectDocumentDeletedObject;
    Connection connectDocumentBeforeChangeObject;
    Connection connectDocumentChangedObject;
    Connection connectDocumentObjectRecomputed;
    Connection connectDocumentRecomputed;
    Connection connectDocumentOpenTransaction;
    Connection connectDocumentCommitTransaction;
    Connection connectDocumentAbortTransaction;
    Connection connectDocumentStartSave;
    Connection connectDocumentFinishSave;
    Connection connectObjectAppendDynamicProperty;
    Connection connectObjectRemoveDynamicProperty;
    Connection connectObjectChangePropertyEditor;
};

} //namespace App

#endif // APP_DOCUMENTOBSERVERPYTHON_H
