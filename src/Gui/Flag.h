/***************************************************************************
 *   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_FLAG_H
#define GUI_FLAG_H

#include "stdexport.h"
#include <QLayout>
#include <QRect>
#include <QWidgetItem>
#include <Inventor/SbVec3f.h>
#include <QtOpenGL.h>
#include "Gui/GLPainter.h"

namespace Gui {
class View3DInventorViewer;

/**
 * @author Werner Mayer
 */
#if 1
class GuiExport Flag : public QOpenGLWidget
{
    Q_OBJECT

public:
    Flag(QWidget* parent=0);
    ~Flag();

    QSize sizeHint() const;
    void setOrigin(const SbVec3f&);
    const SbVec3f& getOrigin() const;
    void drawLine(Gui::View3DInventorViewer*, int tox, int toy);
    void setText(const QString&);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void contextMenuEvent(QContextMenuEvent *);

private:
    QString text;
    SbVec3f coord;
    QPoint dragPosition;
};
#else
class GuiExport Flag : public QWidget
{
    Q_OBJECT

public:
    Flag(QWidget* parent=0);
    ~Flag();

    QSize sizeHint() const;
    void setOrigin(const SbVec3f&);
    const SbVec3f& getOrigin() const;
    void drawLine(int tox, int toy);
    void setText(const QString&);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void contextMenuEvent(QContextMenuEvent *);

private:
    QString text;
    SbVec3f coord;
    QPoint dragPosition;
    QImage image;
};
#endif

class FlagLayout : public QLayout
{
    Q_OBJECT

public:
    enum Position { TopLeft, TopRight, BottomLeft, BottomRight };

    FlagLayout(QWidget *parent, int margin = 0, int spacing = -1);
    FlagLayout(int spacing = -1);
    ~FlagLayout();

    void addItem(QLayoutItem *item);
    void addWidget(QWidget *widget, Position position);
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    QLayoutItem *takeAt(int index);

    void add(QLayoutItem *item, Position position);

private:
    struct ItemWrapper
    {
        ItemWrapper(QLayoutItem *i, Position p) {
            item = i;
            position = p;
        }

        QLayoutItem *item;
        Position position;
    };

    enum SizeType { MinimumSize, SizeHint };
    QSize calculateSize(SizeType sizeType) const;

    QList<ItemWrapper *> list;
};

class GuiExport GLFlagWindow : public Gui::GLGraphicsItem
{
    TYPESYSTEM_HEADER();

public:
    GLFlagWindow(View3DInventorViewer*);
    virtual ~GLFlagWindow();
    void addFlag(Flag* item, FlagLayout::Position pos);
    void removeFlag(Flag* item);
    void deleteFlags();
    Flag* getFlag(int) const;
    int countFlags() const;

    void paintGL();

private:
    View3DInventorViewer* _viewer;
    FlagLayout* _flagLayout;
};

} // namespace Gui


#endif // GUI_FLAG_H
