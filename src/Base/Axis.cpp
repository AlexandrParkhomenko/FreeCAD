/***************************************************************************
 *   Copyright (c) 2011 Juergen Riegel                                     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#include "Axis.h"

using namespace Base;

Axis::Axis()
{

}

Axis::Axis(const Axis& that)
{
    this->_base = that._base;
    this->_dir = that._dir;
}

Axis::Axis(const Vector3d& Orig, const Vector3d& Dir)
{
    this->_base = Orig;
    this->_dir = Dir;
}

void Axis::reverse()
{
    this->_dir = -this->_dir;
}

Axis Axis::reversed() const
{
    Axis a(*this);
    a.reverse();
    return a;
}

void Axis::move(const Vector3d& MovVec)
{
    _base += MovVec;
}

bool Axis::operator ==(const Axis& that) const
{
    return (this->_base == that._base) && (this->_dir == that._dir);
}

bool Axis::operator !=(const Axis& that) const
{
    return !(*this == that);
}

Axis& Axis::operator *=(const Placement &p)
{
    p.multVec(this->_base, this->_base);
    p.getRotation().multVec(this->_dir, this->_dir);
    return *this;
}

Axis Axis::operator *(const Placement &p) const
{
    Axis a(*this);
    a *= p;
    return a;
}

Axis& Axis::operator = (const Axis &New)
{
    this->_base = New._base;
    this->_dir = New._dir;
    return *this;
}

