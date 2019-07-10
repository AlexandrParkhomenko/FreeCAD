/***************************************************************************
 *   Copyright (c) 2015 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



# include <QAction>
# include <QMap>

#include "ActionFunction.h"

using namespace Gui;


namespace Gui {
class ActionFunctionPrivate
{
public:
    QMap<QAction*, boost::function<void()> > triggerMap;
    QMap<QAction*, boost::function<void(bool)> > toggleMap;
    QMap<QAction*, boost::function<void()> > hoverMap;
};
}

ActionFunction::ActionFunction(QObject* parent)
  : QObject(parent), d_ptr(new ActionFunctionPrivate())
{
}

ActionFunction::~ActionFunction()
{
}

void ActionFunction::trigger(QAction* action, boost::function<void()> func)
{
    Q_D(ActionFunction);

    d->triggerMap[action] = func;
    connect(action, SIGNAL(triggered()), this, SLOT(triggered()));
}

void ActionFunction::triggered()
{
    Q_D(ActionFunction);

    QAction* a = qobject_cast<QAction*>(sender());
    QMap<QAction*, boost::function<void()> >::iterator it = d->triggerMap.find(a);
    if (it != d->triggerMap.end()) {
        // invoke the class function here
        it.value()();
    }
}

void ActionFunction::toggle(QAction* action, boost::function<void(bool)> func)
{
    Q_D(ActionFunction);

    d->toggleMap[action] = func;
    connect(action, SIGNAL(toggled(bool)), this, SLOT(toggled(bool)));
}

void ActionFunction::toggled(bool on)
{
    Q_D(ActionFunction);

    QAction* a = qobject_cast<QAction*>(sender());
    QMap<QAction*, boost::function<void(bool)> >::iterator it = d->toggleMap.find(a);
    if (it != d->toggleMap.end()) {
        // invoke the class function here
        it.value()(on);
    }
}

void ActionFunction::hover(QAction* action, boost::function<void()> func)
{
    Q_D(ActionFunction);

    d->hoverMap[action] = func;
    connect(action, SIGNAL(hovered()), this, SLOT(hovered()));
}

void ActionFunction::hovered()
{
    Q_D(ActionFunction);

    QAction* a = qobject_cast<QAction*>(sender());
    QMap<QAction*, boost::function<void()> >::iterator it = d->hoverMap.find(a);
    if (it != d->hoverMap.end()) {
        // invoke the class function here
        it.value()();
    }
}

// ----------------------------------------------------------------------------

namespace Gui {
class TimerFunctionPrivate
{
public:
    boost::function<void()> timeoutFunc;
    boost::function<void(QObject*)> timeoutFuncQObject;
    boost::function<void(QVariant)> timeoutFuncQVariant;
    bool autoDelete;
    QPointer<QObject> argQObject;
    QVariant argQVariant;
};
}

TimerFunction::TimerFunction(QObject* parent)
  : QObject(parent), d_ptr(new TimerFunctionPrivate())
{
    d_ptr->autoDelete = false;
}

TimerFunction::~TimerFunction()
{
}

void TimerFunction::setFunction(boost::function<void()> func)
{
    Q_D(TimerFunction);
    d->timeoutFunc = func;
}

void TimerFunction::setFunction(boost::function<void(QObject*)> func, QObject* args)
{
    Q_D(TimerFunction);
    d->timeoutFuncQObject = func;
    d->argQObject = args;
}

void TimerFunction::setFunction(boost::function<void(QVariant)> func, QVariant args)
{
    Q_D(TimerFunction);
    d->timeoutFuncQVariant = func;
    d->argQVariant = args;
}

void TimerFunction::setAutoDelete(bool on)
{
    Q_D(TimerFunction);
    d->autoDelete = on;
}

void TimerFunction::timeout()
{
    Q_D(TimerFunction);
    if (d->timeoutFunc)
        d->timeoutFunc();
    else if (d->timeoutFuncQObject)
        d->timeoutFuncQObject(d->argQObject);
    else if (d->timeoutFuncQVariant)
        d->timeoutFuncQVariant(d->argQVariant);
    if (d->autoDelete)
        deleteLater();
}

#include "moc_ActionFunction.cpp"
