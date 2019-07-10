/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_SOFCINTERACTIVEELEMENT_H
#define GUI_SOFCINTERACTIVEELEMENT_H

#include "stdexport.h"
#ifndef __InventorAll__
# include "InventorAll.h"
#endif

#include <QtOpenGL.h>

namespace Gui {
/**
 * @author Werner Mayer
 */
class GuiExport SoFCInteractiveElement : public SoReplacedElement {
  typedef SoReplacedElement inherited;

  SO_ELEMENT_HEADER(SoFCInteractiveElement);

public:
  static void initClass(void);

  virtual void init(SoState * state);
  static void set(SoState * const state, SoNode * const node, SbBool mode);
  static SbBool get(SoState * const state);
  static const SoFCInteractiveElement * getInstance(SoState * state);

protected:
  virtual ~SoFCInteractiveElement();
  virtual void setElt(SbBool mode);

private:
  SbBool interactiveMode;
};

class GuiExport SoGLWidgetElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoGLWidgetElement);

public:
  static void initClass(void);

  virtual void init(SoState * state);
  virtual void push(SoState * state);
  virtual void pop(SoState * state, const SoElement * prevTopElement);

  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  static  void set(SoState * state, QOpenGLWidget * window);
  static  void get(SoState * state, QOpenGLWidget *& window);

protected:
  virtual ~SoGLWidgetElement();

protected:
  QOpenGLWidget * window;
};

class GuiExport SoGLRenderActionElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoGLRenderActionElement);

public:
  static void initClass(void);

  virtual void init(SoState * state);
  virtual void push(SoState * state);
  virtual void pop(SoState * state, const SoElement * prevTopElement);

  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  static  void set(SoState * state, SoGLRenderAction * action);
  static  void get(SoState * state, SoGLRenderAction * & action);

protected:
  virtual ~SoGLRenderActionElement();

protected:
  SoGLRenderAction * glRenderAction;
};

class GuiExport SoGLWidgetNode : public SoNode {
    typedef SoNode inherited;

    SO_NODE_HEADER(SoGLWidgetNode);

public:
    static void initClass(void);
    SoGLWidgetNode(void);

    QOpenGLWidget * window;

    virtual void doAction(SoAction * action);
    virtual void GLRender(SoGLRenderAction * action);

protected:
    virtual ~SoGLWidgetNode();
};

class GuiExport SoGLVBOActivatedElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoGLVBOActivatedElement);

public:
  static void initClass(void);

  virtual void init(SoState * state);
  virtual void push(SoState * state);
  virtual void pop(SoState * state, const SoElement * prevTopElement);

  virtual SbBool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  static  void set(SoState * state, SbBool);
  static  void get(SoState * state, SbBool& active);

protected:
  virtual ~SoGLVBOActivatedElement();

protected:
  SbBool active;
};

} // namespace Gui

#endif // GUI_SOFCINTERACTIVEELEMENT_H
