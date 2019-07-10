/***************************************************************************
 *   Copyright (c) 2006 Juergen Riegel                                     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_PLACEMENT_H
#define BASE_PLACEMENT_H

#include "stdexport.h"
#include "Vector3D.h"
#include "Rotation.h"
#include "Matrix.h"



namespace Base {


/**
 * The Placement class.
 */
class BaseExport Placement
{
public:
    /// default constructor
    Placement(void);
    Placement(const Placement&);
    Placement(const Base::Matrix4D& matrix);
    Placement(const Vector3d& Pos, const Rotation &Rot);
    Placement(const Vector3d& Pos, const Rotation &Rot, const Vector3d& Cnt);
    /// Destruction
    ~Placement () {}

    Matrix4D toMatrix(void) const;
    void fromMatrix(const Matrix4D& m);
    const Vector3d& getPosition(void) const {return _pos;}
    const Rotation& getRotation(void) const {return _rot;}
    void setPosition(const Vector3d& Pos){_pos=Pos;}
    void setRotation(const Rotation& Rot) {_rot = Rot;}

    bool isIdentity() const;
    void invert();
    Placement inverse() const;
    void move(const Vector3d& MovVec);

    /** Operators. */
    //@{
    Placement & operator*=(const Placement & p);
    Placement operator *(const Placement & p) const;
    bool operator == (const Placement&) const;
    bool operator != (const Placement&) const;
    Placement& operator = (const Placement&);

    void multVec(const Vector3d & src, Vector3d & dst) const;
    //@}

    static Placement slerp(const Placement & p0, const Placement & p1, double t);

protected:
    Vector3<double> _pos;
    Base::Rotation  _rot;
};

} // namespace Base


#endif // BASE_PLACEMENT_H 


