/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <werner.wm.mayer@gmx.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_SOFC_MESH_NODE_H
#define MESHGUI_SOFC_MESH_NODE_H

#include "stdexport.h"
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>

namespace Mesh {
class MeshObject;
}

namespace MeshGui {

class MeshGuiExport SoFCMeshNode : public SoShape {
    typedef SoShape inherited;

    SO_NODE_HEADER(SoFCMeshNode);

public:
    static void initClass();
    SoFCMeshNode();
    void setMesh(const Mesh::MeshObject* mesh);

    virtual void write( SoWriteAction* action );
    unsigned int MaximumTriangles;

protected:
    virtual void GLRender(SoGLRenderAction *action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
    virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);
    virtual void generatePrimitives(SoAction *action);
    virtual SoDetail * createTriangleDetail(SoRayPickAction * action,
                                            const SoPrimitiveVertex * v1,
                                            const SoPrimitiveVertex * v2,
                                            const SoPrimitiveVertex * v3,
                                            SoPickedPoint * pp);

    virtual SbBool readInstance( SoInput* in, unsigned short  flags );

private:
    // Force using the reference count mechanism.
    virtual ~SoFCMeshNode() {};
    virtual void notify(SoNotList * list);
    // Draw faces
    void drawFaces(SbBool needNormals) const;
    void drawPoints(SbBool needNormals) const;
    unsigned int countTriangles() const;
    void createRoughModel(bool simplest);

private:
    const Mesh::MeshObject*  _mesh;
    unsigned int _ctPrimitives;
    SoMFVec3f point;
    SoMFInt32 coordIndex;
};

// ------------------------------------------------------------

class MeshGuiExport SoFCMeshOpenEdge : public SoShape {
    typedef SoShape inherited;

    SO_NODE_HEADER(SoFCMeshOpenEdge);
    
public:
    static void initClass();
    SoFCMeshOpenEdge();
    void setMesh(const Mesh::MeshObject* mesh);

protected:
    virtual void GLRender(SoGLRenderAction *action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
    virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);
    virtual void generatePrimitives(SoAction *action);
private:
    // Force using the reference count mechanism.
    virtual ~SoFCMeshOpenEdge() {};
    void drawLines() const ;

private:
    const Mesh::MeshObject*  _mesh;
};

} // namespace MeshGui


#endif // MESHGUI_SOFC_MESH_NODE_H

