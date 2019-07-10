/***************************************************************************
 *   Copyright (c) 2012 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


# include <QCoreApplication>
# include <QEvent>

#include "Debugger.h"
#include "Console.h"

using namespace Base;

Debugger::Debugger(QObject* parent)
  : QObject(parent), isAttached(false)
{
}

Debugger::~Debugger()
{
}

void Debugger::attach()
{
    QCoreApplication::instance()->installEventFilter(this);
    isAttached = true;
}

void Debugger::detach()
{
    QCoreApplication::instance()->removeEventFilter(this);
    isAttached = false;
}

bool Debugger::eventFilter(QObject*, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        if (loop.isRunning()) {
            loop.quit();
            return true;
        }
    }

    return false;
}

int Debugger::exec()
{
    if (isAttached)
        Base::Console().Message("TO CONTINUE PRESS ANY KEY...\n");
    return loop.exec();
}

void Debugger::quit()
{
    loop.quit();
}

#include "moc_Debugger.cpp"
