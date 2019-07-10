/***************************************************************************
 *   Copyright (c) 2011 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_FUTUREWATCHER_H
#define BASE_FUTUREWATCHER_H

#include "stdexport.h"
#include <QObject>
#include "Base/Sequencer.h"

namespace Base
{

class BaseExport FutureWatcherProgress : public QObject
{
    Q_OBJECT

public:
    FutureWatcherProgress(const char* text, unsigned int steps);
    ~FutureWatcherProgress();

private Q_SLOTS:
    void progressValueChanged(int v);

private:
    Base::SequencerLauncher seq;
    unsigned int steps, current;
};
}

#endif // BASE_FUTUREWATCHER_H 
