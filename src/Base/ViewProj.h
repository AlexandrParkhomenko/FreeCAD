/***************************************************************************
 *   Copyright (c) 2005 Imetric 3D GmbH                                    *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_VIEWPROJ_H
#define BASE_VIEWPROJ_H

#include "stdexport.h"
#include "Vector3D.h"
#include "Matrix.h"


namespace Base {

/**
 * Abstract base class for all project methods.
 */
class BaseExport ViewProjMethod
{
public:
    virtual ~ViewProjMethod(){}
    virtual bool isValid() const { return true; }
    /** Convert 3D point to 2D projection plane */
    virtual Vector3f operator()(const Vector3f &rclPt) const = 0;
    /** Convert 3D point to 2D projection plane */
    virtual Vector3d operator()(const Vector3d &rclPt) const = 0;
    /** Convert a 2D point on the projection plane in 3D space */
    virtual Vector3f inverse (const Vector3f &rclPt) const = 0;
    /** Convert a 2D point on the projection plane in 3D space */
    virtual Vector3d inverse (const Vector3d &rclPt) const = 0;
    /** Calculate the projection (+ mapping) matrix */
    virtual Matrix4D getProjectionMatrix (void) const = 0; 

protected:
    ViewProjMethod(){}
};

/**
 * The ViewProjMatrix class returns the result of the multiplication
 * of the 3D vector and the view transformation matrix.
 */
class BaseExport ViewProjMatrix : public ViewProjMethod
{
public:
    ViewProjMatrix (const Matrix4D &rclMtx);
    virtual ~ViewProjMatrix();

    Vector3f operator()(const Vector3f &rclPt) const;
    Vector3d operator()(const Vector3d &rclPt) const;
    Vector3f inverse (const Vector3f &rclPt) const;
    Vector3d inverse (const Vector3d &rclPt) const;

    Matrix4D getProjectionMatrix (void) const;

protected:
    bool isOrthographic;
    Matrix4D _clMtx, _clMtxInv;
};

} // namespace Base

#endif // BASE_VIEWPROJ_H
