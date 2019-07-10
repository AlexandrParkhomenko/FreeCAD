/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_CALLTIPS_H
#define GUI_CALLTIPS_H

#include <QListWidget>

class QPlainTextEdit;

namespace Py {
class Object;
class List;
}
namespace Gui {

class CallTip
{
public:
    enum Type {Unknown, Module, Class, Method, Member, Property};
    CallTip():type(Unknown) {}
    QString name;
    QString description;
    QString parameter;
    Type type;
};

/**
 * @author Werner Mayer
 */
class CallTipsList : public QListWidget
{
    Q_OBJECT

public:
    /// Construction
    CallTipsList(QPlainTextEdit* parent);
    /// Destruction
    ~CallTipsList();

    void keyboardSearch (const QString&);
    void showTips(const QString&);
    void validateCursor();

protected:
    bool eventFilter(QObject *, QEvent *);
    void showEvent(QShowEvent*);
    void hideEvent(QHideEvent*);

private Q_SLOTS:
    void callTipItemActivated(QListWidgetItem *item);

private:
    QString extractContext(const QString&) const;
    QMap<QString, CallTip> extractTips(const QString&) const;
    void extractTipsFromObject(Py::Object&, Py::List&, QMap<QString, CallTip>&) const;
    void extractTipsFromProperties(Py::Object&, QMap<QString, CallTip>&) const;
    QString stripWhiteSpace(const QString&) const;

private:
    QPlainTextEdit* textEdit;
    int cursorPos;
    bool validObject;
    bool doCallCompletion;
    QList<int> hideKeys;
    QList<int> compKeys;
};

} // namespace Gui

#endif // GUI_CALLTIPS_H
