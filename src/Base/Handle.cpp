/***************************************************************************
 *   (c) Jürgen Riegel (juergen.riegel@web.de) 2002                        *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 *   Juergen Riegel 2002                                                   *
 ***************************************************************************/



# include <iostream>
# include <assert.h>

#include <QAtomicInt>

#include "Handle.h"
#include "Exception.h"

using namespace Base;

//**************************************************************************
// Construction/Destruction

Handled::Handled()
  : _lRefCount(new QAtomicInt(0))
{
}

Handled::~Handled()
{
    if ((int)(*_lRefCount) != 0)
        std::cerr << "Reference counter of deleted object is not zero!!!!!" << std::endl;
    delete _lRefCount;
}

void Handled::ref() const
{
    _lRefCount->ref();
}

void Handled::unref() const
{
    assert(*_lRefCount > 0);
    if (!_lRefCount->deref()) {
        delete this;
    }
}

int Handled::getRefCount(void) const
{
    return (int)(*_lRefCount);
}

const Handled& Handled::operator = (const Handled&)
{
    // we must not assign _lRefCount
    return *this;
}
