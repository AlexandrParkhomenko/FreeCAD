/***************************************************************************
 *   Copyright (c) 2017 Markus Hovorka <m.hovorka@live.de>                 *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



#include <iostream>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <QString>
#include <QMessageBox>
#include <QPushButton>

#include "App/TextDocument.h"
#include "Gui/Document.h"
#include "Gui/Application.h"
#include "Gui/MainWindow.h"

#include "TextDocumentEditorView.h"


using namespace Gui;

TextDocumentEditorView::TextDocumentEditorView(
        App::TextDocument* txtDoc, QPlainTextEdit* e,
        QWidget* parent)
    : MDIView(
            Application::Instance->getDocument(txtDoc->getDocument()),
            parent),
    editor {e}, textDocument {txtDoc}
{
    setupEditor();
    setupConnection();
    setCentralWidget(editor);
}

TextDocumentEditorView::~TextDocumentEditorView()
{
    textConnection.disconnect();
}

bool TextDocumentEditorView::event(QEvent *event)
{
    if (event->type() == QEvent::Show && sourceModified) {
        refresh();
        sourceModified = false;
    }
    return MDIView::event(event);
}

void TextDocumentEditorView::setupEditor()
{
    connect(getEditor()->document(), SIGNAL(modificationChanged(bool)),
            this, SLOT(setWindowModified(bool)));
    getEditor()->setReadOnly(textDocument->ReadOnly.getValue());
    setWindowTitle(QString::fromUtf8(textDocument->Label.getValue())
            + QString::fromLatin1("[*]"));
    getEditor()->setPlainText(
            QString::fromUtf8(textDocument->Text.getValue()));
}

void TextDocumentEditorView::setupConnection()
{
    textConnection = textDocument->connect(
            boost::bind(&TextDocumentEditorView::sourceChanged, this));
}

void TextDocumentEditorView::sourceChanged()
{
    if (getMainWindow()->activeWindow() == this) {
        refresh();
        sourceModified = false;
    } else {
        sourceModified = true;
    }
}

void TextDocumentEditorView::refresh()
{
    QString text = QString::fromUtf8(
            textDocument->Text.getValue());
    if (isEditorModified()) {
        QMessageBox msgBox {this};
        msgBox.setWindowTitle(tr("Text updated"));
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText(tr(
                    "The text of the underlying object has changed. "
                    "Discard changes and reload the text from the object?"));
        msgBox.addButton(
                tr("Yes, reload."), QMessageBox::YesRole);
        QPushButton* noBtt = msgBox.addButton(QMessageBox::No);
        msgBox.exec();
        if (msgBox.clickedButton() == noBtt)
            return;
    }
    getEditor()->setPlainText(text);
}

bool TextDocumentEditorView::onMsg(const char* msg, const char**)
{
    if (strcmp(msg,"Save") == 0) {
        saveToObject();
        return true;
    }
    return false;
}

bool TextDocumentEditorView::isEditorModified() const
{
    return getEditor()->document()->isModified();
}

bool TextDocumentEditorView::onHasMsg(const char* msg) const
{
    if (strcmp(msg,"Save") == 0)
        return isEditorModified();
    return false;
}

bool TextDocumentEditorView::canClose()
{
    if (getEditor()->document()->isModified()) {
        this->setFocus();

        QMessageBox box(this);
        box.setIcon(QMessageBox::Question);
        box.setWindowTitle(tr("Unsaved document"));
        box.setText(tr("Do you want to save your changes before closing?"));
        box.setInformativeText(tr("If you don't save, your changes will be lost."));
        box.setStandardButtons(QMessageBox::Discard | QMessageBox::Cancel | QMessageBox::Save);
        box.setDefaultButton(QMessageBox::Save);
        box.setEscapeButton(QMessageBox::Cancel);

        // add shortcuts
        QAbstractButton* saveBtn = box.button(QMessageBox::Save);
        if (saveBtn->shortcut().isEmpty()) {
            QString text = saveBtn->text();
            text.prepend(QLatin1Char('&'));
            saveBtn->setShortcut(QKeySequence::mnemonic(text));
        }

        QAbstractButton* discardBtn = box.button(QMessageBox::Discard);
        if (discardBtn->shortcut().isEmpty()) {
            QString text = discardBtn->text();
            text.prepend(QLatin1Char('&'));
            discardBtn->setShortcut(QKeySequence::mnemonic(text));
        }

        switch (box.exec())
        {
        case QMessageBox::Save:
            saveToObject();
            if (getGuiDocument()->isLastView())
                return getGuiDocument()->save();
            return true;
        case QMessageBox::Discard:
            return true;
        case QMessageBox::Cancel:
        default:
            return false;
        }
    }
    else {
        // this view belongs to the document so we have to ask the user
        // how to continue if this is the last view
        return MDIView::canClose();
    }
}

void TextDocumentEditorView::saveToObject()
{
    boost::signals2::shared_connection_block textBlock {textConnection};
    textDocument->Text.setValue(
            getEditor()->document()->toPlainText().toUtf8());
    getEditor()->document()->setModified(false);
}


#include "moc_TextDocumentEditorView.cpp"
