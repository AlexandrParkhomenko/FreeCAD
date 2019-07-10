/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef GUI_UTILITIES_H
#define GUI_UTILITIES_H

#include "stdexport.h"
#include "Base/ViewProj.h"
#include "App/Material.h"
#include <vector>
#include <Inventor/SbColor.h>
#include <Inventor/SbVec2f.h>
#include <Inventor/SbViewVolume.h>
#include <Inventor/SbMatrix.h>

class SbViewVolume;
class QAbstractItemView;

namespace Base {
// Specialization for SbVec3f
template <>
struct vec_traits<SbVec3f> {
    typedef SbVec3f vec_type;
    typedef float float_type;
    vec_traits(const vec_type& v) : v(v){}
    inline float_type x() { return v[0]; }
    inline float_type y() { return v[1]; }
    inline float_type z() { return v[2]; }
private:
    const vec_type& v;
};

// Specialization for SbVec3d
template <>
struct vec_traits<SbVec3d> {
    typedef SbVec3d vec_type;
    typedef double float_type;
    vec_traits(const vec_type& v) : v(v){}
    inline float_type x() { return v[0]; }
    inline float_type y() { return v[1]; }
    inline float_type z() { return v[2]; }
private:
    const vec_type& v;
};

// Specialization for SbColor
template <>
struct vec_traits<SbColor> {
    typedef SbColor vec_type;
    typedef float float_type;
    vec_traits(const vec_type& v) : v(v){}
    inline float_type x() { return v[0]; }
    inline float_type y() { return v[1]; }
    inline float_type z() { return v[2]; }
private:
    const vec_type& v;
};

// Specialization for Color
template <>
struct vec_traits<App::Color> {
    typedef App::Color vec_type;
    typedef float float_type;
    vec_traits(const vec_type& v) : v(v){}
    inline float_type x() { return v.r; }
    inline float_type y() { return v.g; }
    inline float_type z() { return v.b; }
private:
    const vec_type& v;
};
}

namespace App{ class DocumentObject; }
namespace Gui {

/**
 */
class GuiExport ViewVolumeProjection : public Base::ViewProjMethod
{
public:
    ViewVolumeProjection (const SbViewVolume &vv);
    virtual ~ViewVolumeProjection(){}

    Base::Vector3f operator()(const Base::Vector3f &rclPt) const;
    Base::Vector3d operator()(const Base::Vector3d &rclPt) const;
    Base::Vector3f inverse (const Base::Vector3f &rclPt) const;
    Base::Vector3d inverse (const Base::Vector3d &rclPt) const;

    void setTransform(const Base::Matrix4D&);
    Base::Matrix4D getProjectionMatrix () const;

protected:
    SbViewVolume viewVolume;
    SbMatrix matrix;
    SbMatrix invert;
    bool hasTransform;
    Base::Matrix4D transform;
};

class GuiExport Tessellator
{
public:
    Tessellator(const std::vector<SbVec2f>&);
    std::vector<int> tessellate() const;

private:
    static void tessCB(void * v0, void * v1, void * v2, void * cbdata);

private:
    std::vector<SbVec2f> polygon;
};

class GuiExport ItemViewSelection
{
public:
    ItemViewSelection(QAbstractItemView* view);
    void applyFrom(const std::vector<App::DocumentObject*> objs);

private:
    QAbstractItemView* view;
    class MatchName;
};

} // namespace Gui

#endif // GUI_UTILITIES_H
