/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <werner.wm.mayer@gmx.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef MESHGUI_SOFCMESHVERTEX_H
#define MESHGUI_SOFCMESHVERTEX_H

#include "stdexport.h"
#include <Inventor/fields/SoSField.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/elements/SoReplacedElement.h>
#include "Mod/Mesh/App/Core/Elements.h"

namespace MeshGui {

class MeshGuiExport SoSFMeshPointArray : public SoSField {
  typedef SoSField inherited;

  SO_SFIELD_HEADER(SoSFMeshPointArray, MeshCore::MeshPointArray*, MeshCore::MeshPointArray*);

public:
  static void initClass(void);
  void setValue(const MeshCore::MeshPointArray& p);

protected:
  SbBool readBinaryValues(SoInput * in, unsigned long numarg);
  SbBool read1Value(SoInput * in, unsigned long idx);
  void writeBinaryValues(SoOutput * out) const;
  void write1Value(SoOutput * out, unsigned long idx) const;
  int getNumValuesPerLine() const;
};

// -------------------------------------------------------

class MeshGuiExport SoFCMeshVertexElement : public SoReplacedElement {
  typedef SoReplacedElement inherited;

  SO_ELEMENT_HEADER(SoFCMeshVertexElement);

public:
  static void initClass(void);

  virtual void init(SoState * state);
  static void set(SoState * const state, SoNode * const node, const MeshCore::MeshPointArray * const coords);
  static const MeshCore::MeshPointArray * get(SoState * const state);
  static const SoFCMeshVertexElement * getInstance(SoState * state);
  virtual void print(FILE * file) const;

protected:
  virtual ~SoFCMeshVertexElement();
  const MeshCore::MeshPointArray *coords3D;
};

// -------------------------------------------------------

class MeshGuiExport SoFCMeshVertex : public SoNode {
  typedef SoSField inherited;

  SO_NODE_HEADER(SoFCMeshVertex);

public:
  static void initClass(void);
  SoFCMeshVertex(void);

  SoSFMeshPointArray point;

  virtual void doAction(SoAction * action);
  virtual void GLRender(SoGLRenderAction * action);
  virtual void callback(SoCallbackAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void pick(SoPickAction * action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);

protected:
  virtual ~SoFCMeshVertex();
};

} // namespace MeshGui


#endif // MESHGUI_SOFCMESHVERTEX_H

