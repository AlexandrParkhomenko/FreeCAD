/***************************************************************************
 *   Copyright (c) 2012 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_DEBUGGER_H
#define BASE_DEBUGGER_H

#include "stdexport.h"
#include <QObject>
#include <QEventLoop>

namespace Base {
/**
  This is a utility class to break the application at a point to inspect e.g. the result of
  an algorithm.
  You usually use it like this
  \code
    ...
    Base::Debugger dbg;
    dbg.attach();
    dbg.exec();
    ...
  \endcode
  Or you can connect it with a button and let the user click it in order to continue.
  \code
    QPushButton* btn = new QPushButton();
    btn->setText("Continue");
    btn->show();
    Base::Debugger dbg;
    connect(btn, SIGNAL(clicked()), &dbg, SLOT(quit()));
    dbg.exec();
  \endcode
 \author Werner Mayer
 */
class BaseExport Debugger : public QObject
{
    Q_OBJECT

public:
    Debugger(QObject* parent=0);
    ~Debugger();

    void attach();
    void detach();
    bool eventFilter(QObject*, QEvent*);
    int exec();

public Q_SLOTS:
    void quit();

private:
    bool isAttached;
    QEventLoop loop;
};

}

#endif // BASE_DEBUGGER_H
