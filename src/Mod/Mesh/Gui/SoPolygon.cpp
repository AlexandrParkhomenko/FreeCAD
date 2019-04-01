/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/



# ifdef FC_OS_WIN32
# include <windows.h>
# endif
# ifdef FC_OS_MACOSX
# include <OpenGL/gl.h>
# else
# include <GL/gl.h>
# endif
# include <float.h>
# include <algorithm>
# include <Inventor/actions/SoCallbackAction.h>
# include <Inventor/actions/SoGetBoundingBoxAction.h>
# include <Inventor/actions/SoGetPrimitiveCountAction.h>
# include <Inventor/actions/SoGLRenderAction.h>
# include <Inventor/actions/SoPickAction.h>
# include <Inventor/actions/SoWriteAction.h>
# include <Inventor/bundles/SoMaterialBundle.h>
# include <Inventor/bundles/SoTextureCoordinateBundle.h>
# include <Inventor/elements/SoGLCacheContextElement.h>
# include <Inventor/errors/SoReadError.h>
# include <Inventor/misc/SoState.h>
#endif

# include <Inventor/elements/SoCoordinateElement.h>
# include <float.h>

#include "SoPolygon.h"

using namespace MeshGui;


SO_NODE_SOURCE(SoPolygon);

void SoPolygon::initClass()
{
    SO_NODE_INIT_CLASS(SoPolygon, SoShape, "Shape");
}

SoPolygon::SoPolygon()
{
    SO_NODE_CONSTRUCTOR(SoPolygon);

    SO_NODE_ADD_FIELD(startIndex, (0));
    SO_NODE_ADD_FIELD(numVertices, (0));
    SO_NODE_ADD_FIELD(highlight, (false));
    SO_NODE_ADD_FIELD(render, (true));
}

/**
 * Renders the polygon.
 */
void SoPolygon::GLRender(SoGLRenderAction *action)
{
    if (shouldGLRender(action) && render.getValue())
    {
        SoState*  state = action->getState();
        const SoCoordinateElement * coords = SoCoordinateElement::getInstance(state);
        if (!coords) return;
        const SbVec3f * points = coords->getArrayPtr3();
        if (!points) return;

        SoMaterialBundle mb(action);
        SoTextureCoordinateBundle tb(action, true, false);
        SoLazyElement::setLightModel(state, SoLazyElement::BASE_COLOR);
        mb.sendFirst();  // make sure we have the correct material

        int32_t len = coords->getNum();
        drawPolygon(points, len);
    }
}

/**
 * Renders the polygon.
 */
void SoPolygon::drawPolygon(const SbVec3f * points,int32_t len) const
{
    glLineWidth(3.0f);
    int32_t beg = startIndex.getValue();
    int32_t cnt = numVertices.getValue();
    int32_t end = beg + cnt;
    if (end > len)
        return; // wrong setup, too few points
    // draw control mesh
    glBegin(GL_LINES);
    for (int32_t i = beg; i < end; ++i) {
        int32_t j = (i-beg+1) % cnt + beg;
        glVertex3fv(points[i].getValue());
        glVertex3fv(points[j].getValue());
    }
    glEnd();
}

/**
 * Calculates picked point based on primitives generated by subclasses.
 */
void
SoPolygon::rayPick(SoRayPickAction * action)
{
    //if (this->shouldRayPick(action)) {
    //    this->computeObjectSpaceRay(action);

    //    const SoBoundingBoxCache* bboxcache = getBoundingBoxCache();
    //    if (!bboxcache || !bboxcache->isValid(action->getState()) ||
    //        SoFCMeshObjectShape_ray_intersect(action, bboxcache->getProjectedBox())) {
    //        this->generatePrimitives(action);
    //    }
    //}
    inherited::rayPick(action);
}

void SoPolygon::generatePrimitives(SoAction* /*action*/)
{
}

/**
 * Sets the bounding box of the mesh to \a box and its center to \a center.
 */
void SoPolygon::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
    SoState*  state = action->getState();
    const SoCoordinateElement * coords = SoCoordinateElement::getInstance(state);
    if (!coords) return;
    const SbVec3f * points = coords->getArrayPtr3();
    if (!points) return;
    float maxX=-FLT_MAX, minX=FLT_MAX,
          maxY=-FLT_MAX, minY=FLT_MAX,
          maxZ=-FLT_MAX, minZ=FLT_MAX;
    int32_t len = coords->getNum();
    int32_t beg = startIndex.getValue();
    int32_t cnt = numVertices.getValue();
    int32_t end = beg + cnt;
    if (end <= len) {
        for (int32_t i=beg; i<end; i++) {
            maxX = std::max<float>(maxX,points[i][0]);
            minX = std::min<float>(minX,points[i][0]);
            maxY = std::max<float>(maxY,points[i][1]);
            minY = std::min<float>(minY,points[i][1]);
            maxZ = std::max<float>(maxZ,points[i][2]);
            minZ = std::min<float>(minZ,points[i][2]);
        }

        box.setBounds(minX,minY,minZ,maxX,maxY,maxZ);
        center.setValue(0.5f*(minX+maxX),0.5f*(minY+maxY),0.5f*(minZ+maxZ));
    }
    else {
        box.setBounds(SbVec3f(0,0,0), SbVec3f(0,0,0));
        center.setValue(0.0f,0.0f,0.0f);
    }
}
