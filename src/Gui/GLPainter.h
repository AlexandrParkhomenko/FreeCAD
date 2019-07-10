/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_GLPAINTER_H
#define GUI_GLPAINTER_H

#include "stdexport.h"
#include <GL/gl.h>

#include "Base/BaseClass.h"
#include <QtOpenGL.h>
#include <QPoint>

class QPaintDevice;

namespace Gui {
class View3DInventorViewer;
class GuiExport GLPainter
{
public:
    GLPainter();
    virtual ~GLPainter();

    bool begin(QPaintDevice * device);
    bool end();
    bool isActive() const;

    /** @name Setter methods */
    //@{
    void setLineWidth(float);
    void setPointSize(float);
    void setColor(float, float, float, float=0);
    void setLogicOp(GLenum);
    void resetLogicOp();
    void setDrawBuffer(GLenum);
    void setLineStipple(GLint factor, GLushort pattern);
    void resetLineStipple();
    //@}

    /** @name Draw routines */
    //@{
    void drawRect (int x, int y, int w, int h);
    void drawLine (int x1, int y1, int x2, int y2);
    void drawPoint(int x, int y);
    //@}

private:
    QOpenGLWidget* viewer;
    GLfloat depthrange[2];
    GLdouble projectionmatrix[16];
    GLint width, height;
    bool logicOp;
    bool lineStipple;
};

class GuiExport GLGraphicsItem : public Base::BaseClass
{
    TYPESYSTEM_HEADER();

public:
    GLGraphicsItem()
    {
    }
    virtual ~GLGraphicsItem()
    {
    }
    virtual void paintGL() = 0;
};

class GuiExport Rubberband : public Gui::GLGraphicsItem
{
    View3DInventorViewer* viewer;
    int x_old, y_old, x_new, y_new;
    float rgb_r, rgb_g, rgb_b, rgb_a;
    bool working, stipple;

public:
    Rubberband(View3DInventorViewer* v);
    Rubberband();
    ~Rubberband();
    void setWorking(bool on);
    void setLineStipple(bool on);
    bool isWorking();
    void setViewer(View3DInventorViewer* v);
    void setCoords(int x1, int y1, int x2, int y2);
    void setColor(float r, float g, float b, float a);
    void paintGL();
};

class GuiExport Polyline : public Gui::GLGraphicsItem
{
    View3DInventorViewer* viewer;
    std::vector<QPoint> _cNodeVector;
    int x_new, y_new;
    float rgb_r, rgb_g, rgb_b, rgb_a, line;
    bool working, closed, stippled;
    GLPainter p;

public:
    Polyline(View3DInventorViewer* v);
    Polyline();
    ~Polyline();
    void setWorking(bool on);
    bool isWorking() const;
    void setViewer(View3DInventorViewer* v);
    void setCoords(int x, int y);
    void setColor(int r, int g, int b, int a=0);
    void setLineWidth(float l);
    void setClosed(bool c);
    void setCloseStippled(bool c);
    void addNode(const QPoint& p);
    void popNode();
    void clear();
    void paintGL();
};

} // namespace Gui

#endif  // GUI_GLPAINTER_H

