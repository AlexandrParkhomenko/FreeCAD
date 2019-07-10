/***************************************************************************
 *   Copyright (c) 2011 Juergen Riegel                                     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef BASE_AXIS_H
#define BASE_AXIS_H

#include "stdexport.h"

#include "Vector3D.h"
#include "Placement.h"

namespace Base {

/**
 * The Axis class.
 */
class BaseExport Axis
{
public:
    /// default constructor
    Axis(void);
    Axis(const Axis&);
    Axis(const Vector3d& Orig, const Vector3d& Dir);
    /// Destruction
    ~Axis () {}

    const Vector3d& getBase(void) const {return _base;}
    const Vector3d& getDirection(void) const {return _dir;}
    void setBase(const Vector3d& Orig) {_base=Orig;}
    void setDirection(const Vector3d& Dir) {_dir=Dir;}

    void reverse();
    Axis reversed() const;
    void move(const Vector3d& MovVec);

    /** Operators. */
    //@{
    Axis& operator *=(const Placement &p);
    Axis operator *(const Placement &p) const;
    bool operator ==(const Axis&) const;
    bool operator !=(const Axis&) const;
    Axis& operator =(const Axis&);
    //@}

protected:
    Vector3d _base;
    Vector3d _dir;
};

} // namespace Base

#endif // BASE_AXIS_H
