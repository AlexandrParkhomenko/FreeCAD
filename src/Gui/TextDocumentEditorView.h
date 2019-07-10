/***************************************************************************
 *   Copyright (c) 2017 Markus Hovorka <m.hovorka@live.de>                 *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_TEXTDOCUMENTEDITORVIEW_H
#define GUI_TEXTDOCUMENTEDITORVIEW_H


#include "stdexport.h"
#include <string>
#include <boost/signals2.hpp>
#include <QPlainTextEdit>

#include "App/TextDocument.h"
#include "Gui/MDIView.h"
#include "Gui/Window.h"


namespace Gui {

class GuiExport TextDocumentEditorView : public MDIView {
    Q_OBJECT
public:
    TextDocumentEditorView(
            App::TextDocument* textDocument,
            QPlainTextEdit* editor, QWidget* parent);
    ~TextDocumentEditorView();
    const char *getName() const override { return "TextDocumentEditorView"; }
    bool onMsg(const char* msg, const char**) override;
    bool onHasMsg(const char* msg) const override;
    bool canClose() override;

    bool event(QEvent *event) override;

    QPlainTextEdit* getEditor() const { return editor; }
    App::TextDocument* getTextObject() const { return textDocument; }
private:
    void setupEditor();
    void setupConnection();
    void saveToObject();
    void sourceChanged();
    void refresh();
    bool isEditorModified() const;
    QPlainTextEdit *const editor;
    App::TextDocument *const textDocument;
    boost::signals2::connection textConnection;
    bool sourceModified = false;
};

}

#endif
