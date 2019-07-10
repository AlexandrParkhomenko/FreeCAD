/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_PYTHONCONSOLE_H
#define GUI_PYTHONCONSOLE_H

#include "stdexport.h"
#include "PythonEditor.h"
#include "Base/PyObjectBase.h"

class QPlainTextEdit;
class QPushButton;

namespace Gui {

/**
 * This class implements an interactive Python interpreter.
 * @author Werner Mayer
 */
class GuiExport InteractiveInterpreter
{
public:
    InteractiveInterpreter();
    ~InteractiveInterpreter();

    bool push(const char*);
    int compileCommand(const char*) const;
    bool hasPendingInput( void ) const;
    void setBuffer(const QStringList&);
    QStringList getBuffer() const;
    void clearBuffer();

private:
    bool runSource(const char*) const;
    PyObject* compile(const char*) const;
    void runCode(PyCodeObject*) const;
    void setPrompt();

private:
    struct InteractiveInterpreterP* d;
};

/**
 * This class implements the history for the Python console.
 * @author Werner Mayer
 */
class GuiExport ConsoleHistory
{
public:
    ConsoleHistory();
    ~ConsoleHistory();

    void first();
    bool more();
    bool next();
    bool prev(const QString &prefix = QString());
    bool isEmpty() const;
    const QString& value() const;
    void append(const QString &inputLine);
    const QStringList& values() const;
    void restart();
		void markScratch( void );
		void doScratch( void );

private:
    QStringList                _history;
    QStringList::ConstIterator _it;
		int                        _scratchBegin;
    QString                    _prefix;
};

/**
 * Python text console with syntax highlighting.
 * @author Werner Mayer
 */
class PythonConsoleHighlighter;
class GuiExport PythonConsole : public TextEdit, public WindowParameter
{
    Q_OBJECT

public:
    enum Prompt {
        Complete   = 0,
        Incomplete = 1,
        Flush      = 2,
        Special    = 3
    };

    PythonConsole(QWidget *parent = 0);
    ~PythonConsole();

    void OnChange( Base::Subject<const char*> &rCaller,const char* rcReason );
    void printStatement( const QString& cmd );
    QString readline( void );

public Q_SLOTS:
    void onSaveHistoryAs();
    void onInsertFileName();
    void onCopyHistory();
    void onCopyCommand();
    void onClearConsole();
    void onFlush();

private Q_SLOTS:
    void visibilityChanged (bool visible);

protected:
    void keyPressEvent  ( QKeyEvent         * e );
    void showEvent      ( QShowEvent        * e );
    void dropEvent      ( QDropEvent        * e );
    void dragEnterEvent ( QDragEnterEvent   * e );
    void dragMoveEvent  ( QDragMoveEvent    * e );
    void changeEvent    ( QEvent            * e );
    void mouseReleaseEvent( QMouseEvent     * e );

    void overrideCursor(const QString& txt);

    /** Pops up the context menu with some extensions */
    void contextMenuEvent ( QContextMenuEvent* e );
    bool canInsertFromMimeData ( const QMimeData * source ) const;
    QMimeData * createMimeDataFromSelection () const;
    void insertFromMimeData ( const QMimeData * source );
    QTextCursor inputBegin( void ) const;

private:
    void runSource(const QString&);
    bool isComment(const QString&) const;
    void printPrompt(Prompt);
    void insertPythonOutput(const QString&);
    void insertPythonError (const QString&);
    void runSourceFromMimeData(const QString&);
    void appendOutput(const QString&, int);

Q_SIGNALS:
    void pendingSource( void );

private:
    struct PythonConsoleP* d;

    friend class PythonStdout;
    friend class PythonStderr;

private:
    PythonConsoleHighlighter* pythonSyntax;
    QString                 *_sourceDrain;
};

/**
 * Syntax highlighter for Python console.
 * @author Werner Mayer
 */
class GuiExport PythonConsoleHighlighter : public PythonSyntaxHighlighter
{
public:
    PythonConsoleHighlighter(QObject* parent);
    ~PythonConsoleHighlighter();

    void highlightBlock (const QString & text);

protected:
    void colorChanged(const QString& type, const QColor& col);
};

} // namespace Gui

#endif // GUI_PYTHONCONSOLE_H
