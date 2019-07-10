/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_EDITORVIEW_H
#define GUI_EDITORVIEW_H

#include "stdexport.h"
#include "MDIView.h"
#include "Window.h"

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
class QPrinter;
QT_END_NAMESPACE

namespace Gui {

class EditorViewP;

/**
 * A special view class which sends the messages from the application to
 * the editor and embeds it in a window.
 * @author Werner Mayer
 */
class GuiExport EditorView : public MDIView, public WindowParameter
{
    Q_OBJECT

public:
    enum DisplayName {
        FullName,
        FileName,
        BaseName
    };

    EditorView(QPlainTextEdit* editor, QWidget* parent);
    ~EditorView();

    QPlainTextEdit* getEditor() const;
    void setDisplayName(DisplayName);
    void OnChange(Base::Subject<const char*> &rCaller,const char* rcReason);

    const char *getName(void) const {return "EditorView";}
    void onUpdate(void){};

    bool onMsg(const char* pMsg,const char** ppReturn);
    bool onHasMsg(const char* pMsg) const;

    bool canClose(void);

    /** @name Standard actions of the editor */
    //@{
    bool open   (const QString &f);
    bool saveAs ();
    void cut    ();
    void copy   ();
    void paste  ();
    void undo   ();
    void redo   ();
    void print  ();
    void printPdf();
    void printPreview();
    void print(QPrinter*);
    //@}

    QStringList undoActions() const;
    QStringList redoActions() const;
    QString fileName() const;

protected:
    void focusInEvent(QFocusEvent* e);

private Q_SLOTS:
    void checkTimestamp();
    void contentsChange(int position, int charsRemoved, int charsAdded);
    void undoAvailable(bool);
    void redoAvailable(bool);

Q_SIGNALS:
    void changeFileName(const QString&);

private:
    void setCurrentFileName(const QString &fileName);
    bool saveFile();

private:
    EditorViewP* d;
};

class PythonEditor;
class GuiExport PythonEditorView : public EditorView
{
    Q_OBJECT

public:
    PythonEditorView(PythonEditor* editor, QWidget* parent);
    ~PythonEditorView();

    bool onMsg(const char* pMsg,const char** ppReturn);
    bool onHasMsg(const char* pMsg) const;

public Q_SLOTS:
    void executeScript();
    void startDebug();
    void toggleBreakpoint();
    void showDebugMarker(int line);
    void hideDebugMarker();

private:
    PythonEditor* _pye;
};

} // namespace Gui

#endif // GUI_EDITORVIEW_H
