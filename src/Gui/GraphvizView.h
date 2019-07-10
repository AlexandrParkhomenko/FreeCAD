/***************************************************************************
 *   Copyright (c) 2014 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_GRAPHVIZVIEW_H
#define GUI_GRAPHVIZVIEW_H

#include "stdexport.h"
#include "MDIView.h"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>


class QGraphicsScene;
class QGraphicsView;
class QSvgRenderer;
class QGraphicsSvgItem;
class GraphicsViewZoom;

namespace Gui 
{

class GraphvizWorker;

class GuiExport GraphvizView : public MDIView
{
    Q_OBJECT

public:
    GraphvizView(App::Document &_doc, QWidget* parent=0);
    ~GraphvizView();

    QByteArray exportGraph(const QString& filter);

    /// Message handler
    virtual bool onMsg(const char* pMsg,const char** ppReturn);
    /// Message handler test
    virtual bool onHasMsg(const char* pMsg) const;
    /** @name Printing */
    //@{
    virtual void print(QPrinter* printer);
    /** Print content of view */
    virtual void print();
    /** Print to PDF file */
    virtual void printPdf();
    /** Show a preview dialog */
    virtual void printPreview();
    //@}

private Q_SLOTS:
    void svgFileRead(const QByteArray & data);
    void error();
    void done();

private:
    void updateSvgItem(const App::Document &doc);
    void disconnectSignals();

    const App::Document& doc;
    std::string graphCode;
    QGraphicsScene* scene;
    QGraphicsView* view;
    GraphicsViewZoom* zoomer;
    QGraphicsSvgItem* svgItem;
    QSvgRenderer* renderer;
    GraphvizWorker* thread;
    int nPending;

    typedef boost::signals2::scoped_connection Connection;
    Connection recomputeConnection;
    Connection undoConnection;
    Connection redoConnection;
};

} // namespace Gui

#endif // GUI_GRAPHVIZVIEW_H
