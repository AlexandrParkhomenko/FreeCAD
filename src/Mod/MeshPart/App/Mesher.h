/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHPART_MESHER_H
#define MESHPART_MESHER_H

#include <sstream>
#include "Base/Stream.h"
#ifdef HAVE_SMESH
#include <SMESH_Version.h>
#endif

class TopoDS_Shape;
class SMESH_Gen;

namespace Mesh { class MeshObject; }
namespace MeshPart {

class Mesher
{
public:
    enum Method {
        None = 0,
        Mefisto = 1,
        Standard = 3
    };

    Mesher(const TopoDS_Shape&);
    ~Mesher();

    void setMethod(Method m)
    { method = m; }
    Method getMethod() const
    { return method; }

    /** @name Mefisto settings */
    //@{
    void setMaxLength(double s)
    { maxLength = s; }
    double getMaxLength() const
    { return maxLength; }
    void setMaxArea(double s)
    { maxArea = s; }
    double getMaxArea() const
    { return maxArea; }
    void setLocalLength(double s)
    { localLength = s; }
    double getLocalLength() const
    { return localLength; }
    void setDeflection(double s)
    { deflection = s; }
    double getDeflection() const
    { return deflection; }
    void setAngularDeflection(double s)
    { angularDeflection = s; }
    double getAngularDeflection() const
    { return angularDeflection; }
    void setMinMaxLengths(double f, double l)
    { minLen = f; maxLen = l; }
    void getMinMaxLengths(double& f, double& l) const
    { f = minLen; l= maxLen; }
    void setRegular(bool s)
    { regular = s; }
    bool isRegular() const
    { return regular; }
    void setRelative(bool s)
    { relative = s; }
    bool isRelative() const
    { return relative; }
    void setSegments(bool s)
    { segments = s; }
    bool isSegments() const
    { return segments; }
    void setColors(const std::vector<uint32_t>& c)
    { colors = c; }
    //@}

    Mesh::MeshObject* createMesh() const;

private:
    const TopoDS_Shape& shape;
    Method method;
    double maxLength;
    double maxArea;
    double localLength;
    double deflection;
    double angularDeflection;
    double minLen, maxLen;
    bool relative;
    bool regular;
    bool segments;
    std::vector<uint32_t> colors;
    struct Vertex;

    static SMESH_Gen *_mesh_gen;
};

class MeshingOutput : public std::streambuf
{
public:
    MeshingOutput();

protected:
    int overflow(int c = EOF);
    int sync();

private:
    std::string buffer;
};

} // namespace MeshPart

#endif // MESHPART_MESHER_H
