/***************************************************************************
 *   Copyright (c) 2017 Markus Hovorka <m.hovorka@live.de>                 *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <QMenu>
# include <QPlainTextEdit>
# include <boost/bind.hpp>

#include "Base/Type.h"
#include "Gui/ViewProviderDocumentObject.h"
#include "Gui/TextDocumentEditorView.h"
#include "Gui/MainWindow.h"
#include "Gui/Document.h"
#include "Gui/ActionFunction.h"

#include "ViewProviderTextDocument.h"


using namespace Gui;

PROPERTY_SOURCE(Gui::ViewProviderTextDocument, Gui::ViewProviderDocumentObject)

ViewProviderTextDocument::ViewProviderTextDocument()
{
    sPixmap = "TextDocument";
}

void ViewProviderTextDocument::setupContextMenu(QMenu* menu, QObject* receiver, const char* member)
{
    Gui::ActionFunction* func = new Gui::ActionFunction(menu);
    QAction* act = menu->addAction(QObject::tr("Edit text"));
    func->trigger(act, boost::bind(&ViewProviderTextDocument::doubleClicked, this));

    ViewProviderDocumentObject::setupContextMenu(menu, receiver, member);
}

bool ViewProviderTextDocument::doubleClicked()
{
    if (!activateView()) {
        auto* editorWidget = new QPlainTextEdit {};
        getMainWindow()->addWindow(
            new TextDocumentEditorView {
                static_cast<App::TextDocument*>(getObject()),
                editorWidget, getMainWindow()});
    }
    return true;
}

bool ViewProviderTextDocument::activateView() const
{
    auto views = getDocument()->getMDIViewsOfType(
            TextDocumentEditorView::getClassTypeId());
    for (auto v : views) {
        auto textView = static_cast<TextDocumentEditorView *>(v);
        if (textView->getTextObject() == getObject()) {
            getMainWindow()->setActiveWindow(textView);
            return true;
        }
    }
    return false;
}
