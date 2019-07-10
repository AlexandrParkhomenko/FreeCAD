/***************************************************************************
 *   Copyright (c) 2009 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_SOFCINDEXEDFACESET_H
#define MESHGUI_SOFCINDEXEDFACESET_H

#include "stdexport.h"
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFColor.h>

class SoGLCoordinateElement;
class SoTextureCoordinateBundle;

typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;

namespace MeshGui {

class MeshRenderer
{
public:
    MeshRenderer();
    ~MeshRenderer();
    void generateGLArrays(SoGLRenderAction*, SoMaterialBindingElement::Binding binding,
        std::vector<float>& vertex, std::vector<int32_t>& index);
    void renderFacesGLArray(SoGLRenderAction *action);
    void renderCoordsGLArray(SoGLRenderAction *action);
    bool canRenderGLArray(SoGLRenderAction *action) const;
    bool matchMaterial(SoState*) const;
    static bool shouldRenderDirectly(bool);

private:
    class Private;
    Private* p;
};

/**
 * class SoFCMaterialEngine
 * \brief The SoFCMaterialEngine class is used to notify an
 * SoFCIndexedFaceSet node about material changes.
 *
 * @author Werner Mayer
 */
class MeshGuiExport SoFCMaterialEngine : public SoEngine
{
    SO_ENGINE_HEADER(SoFCMaterialEngine);

public:
    SoFCMaterialEngine();
    static void initClass();

    SoMFColor diffuseColor;
    SoEngineOutput trigger;

private:
    virtual ~SoFCMaterialEngine();
    virtual void evaluate();
    virtual void inputChanged(SoField *);
};

/**
 * class SoFCIndexedFaceSet
 * \brief The SoFCIndexedFaceSet class is designed to optimize redrawing a mesh
 * during user interaction.
 *
 * @author Werner Mayer
 */
class MeshGuiExport SoFCIndexedFaceSet : public SoIndexedFaceSet {
    typedef SoIndexedFaceSet inherited;

    SO_NODE_HEADER(SoFCIndexedFaceSet);

public:
    static void initClass();
    SoFCIndexedFaceSet();

    SoSFBool updateGLArray;
    unsigned int renderTriangleLimit;

    void invalidate();

protected:
    // Force using the reference count mechanism.
    virtual ~SoFCIndexedFaceSet() {}
    virtual void GLRender(SoGLRenderAction *action);
    void drawFaces(SoGLRenderAction *action);
    void drawCoords(const SoGLCoordinateElement * const vertexlist,
                    const int32_t *vertexindices,
                    int numindices,
                    const SbVec3f *normals,
                    const int32_t *normalindices,
                    SoMaterialBundle *materials,
                    const int32_t *matindices,
                    const int32_t binding,
                    const SoTextureCoordinateBundle * const texcoords,
                    const int32_t *texindices);

    void doAction(SoAction * action);

private:
    void startSelection(SoAction * action);
    void stopSelection(SoAction * action);
    void renderSelectionGeometry(const SbVec3f *);
    void startVisibility(SoAction * action);
    void stopVisibility(SoAction * action);
    void renderVisibleFaces(const SbVec3f *);

    void generateGLArrays(SoGLRenderAction * action);

private:
    MeshRenderer render;
    GLuint *selectBuf;
};

} // namespace MeshGui


#endif // MESHGUI_SOFCINDEXEDFACESET_H

