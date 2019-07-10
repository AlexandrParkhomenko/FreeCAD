/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_PYTHONEDITOR_H
#define GUI_PYTHONEDITOR_H

#include "stdexport.h"
#include "Window.h"
#include "TextEdit.h"
#include "SyntaxHighlighter.h"

namespace Gui {

class PythonSyntaxHighlighter;
class PythonSyntaxHighlighterP;

/**
 * Python text editor with syntax highlighting.
 * \author Werner Mayer
 */
class GuiExport PythonEditor : public TextEditor
{
    Q_OBJECT

public:
    PythonEditor(QWidget *parent = 0);
    ~PythonEditor();

    void toggleBreakpoint();
    void showDebugMarker(int line);
    void hideDebugMarker();

public Q_SLOTS:
    /** Inserts a '#' at the beginning of each selected line or the current line if 
     * nothing is selected
     */
    void onComment();
    /**
     * Removes the leading '#' from each selected line or the current line if
     * nothing is selected. In case a line hasn't a leading '#' then
     * this line is skipped.
     */
    void onUncomment();
    void setFileName(const QString&);
    void startDebug();

protected:
    /** Pops up the context menu with some extensions */
    void contextMenuEvent ( QContextMenuEvent* e );
    void drawMarker(int line, int x, int y, QPainter*);

private:
    //PythonSyntaxHighlighter* pythonSyntax;
    struct PythonEditorP* d;
};

/**
 * Syntax highlighter for Python.
 * \author Werner Mayer
 */
class GuiExport PythonSyntaxHighlighter : public SyntaxHighlighter
{
public:
    PythonSyntaxHighlighter(QObject* parent);
    virtual ~PythonSyntaxHighlighter();

    void highlightBlock (const QString & text);

private:
    PythonSyntaxHighlighterP* d;
};

} // namespace Gui

#endif // GUI_PYTHONEDITOR_H
