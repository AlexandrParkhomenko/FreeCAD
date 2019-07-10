/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_SYNTAXHIGHLIGHTER_H
#define GUI_SYNTAXHIGHLIGHTER_H

#include "stdexport.h"
#include <QSyntaxHighlighter>

namespace Gui {
class SyntaxHighlighterP;
class TextEditor;

/**
 * Abstract Syntax highlighter.
 * @author Werner Mayer
 */
class GuiExport SyntaxHighlighter : public QSyntaxHighlighter
{
public:
    SyntaxHighlighter(QObject* parent);
    virtual ~SyntaxHighlighter();

    int maximumUserState() const;

    void setColor(const QString& type, const QColor& col);
    QColor color(const QString& type);

protected:
    virtual void colorChanged(const QString& type, const QColor& col);

protected:
    enum TColor
    {
        Text = 0, Comment = 1, BlockComment = 2, Number = 3, String = 4, Keyword = 5,
        Classname = 6, Defname = 7, Operator = 8, Output = 9, Error = 10
    };

    QColor colorByType(TColor type);


private:
    SyntaxHighlighterP* d;
};

} // namespace Gui

#endif // GUI_SYNTAXHIGHLIGHTER_H
