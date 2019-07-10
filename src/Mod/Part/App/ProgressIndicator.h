/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef PART_PROGRESSINDICATOR_H
#define PART_PROGRESSINDICATOR_H

#include "stdexport.h"
#include <Message_ProgressIndicator.hxx>
#include "Base/Sequencer.h"
#include <memory>

namespace Part {

class Standard_EXPORT ProgressIndicator : public Message_ProgressIndicator
{
public:
    ProgressIndicator (int theMaxVal = 100);
    virtual ~ProgressIndicator ();

    virtual Standard_Boolean Show (const Standard_Boolean theForce = Standard_True);
    virtual Standard_Boolean UserBreak();

private:
    std::unique_ptr<Base::SequencerLauncher> myProgress;
};

}

#endif // PART_PROGRESSINDICATOR_H
