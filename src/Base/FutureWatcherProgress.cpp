/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/



#include "FutureWatcherProgress.h"

using namespace Base;

FutureWatcherProgress::FutureWatcherProgress(const char* text, unsigned int steps)
  : seq(text, 100), steps(steps), current(0)
{
}

FutureWatcherProgress::~FutureWatcherProgress()
{
}

void FutureWatcherProgress::progressValueChanged(int v)
{
    if (steps == 0)
        return;
    unsigned int step = (100 * v) / steps;
    if (step > current) {
        current = step;
        seq.next();
    }
}

#include "moc_FutureWatcherProgress.cpp"
