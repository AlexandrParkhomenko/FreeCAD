/***************************************************************************
 *   Copyright (c) 2006 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_SPLITVIEW3DINVENTOR_H
#define GUI_SPLITVIEW3DINVENTOR_H

#include "stdexport.h"
#include "MDIView.h"

#include "Base/Parameter.h"
#include <CXX/Extensions.hxx>
#include <vector>

namespace Gui {
class View3DInventorViewer;
class AbstractSplitViewPy;

/** The SplitView3DInventor class allows to create a window with two or more Inventor views.
 *  \author Werner Mayer
 */
class GuiExport AbstractSplitView : public MDIView, public ParameterGrp::ObserverType
{
    TYPESYSTEM_HEADER();

public:
    AbstractSplitView(Gui::Document* pcDocument, QWidget* parent, Qt::WindowFlags wflags=0);
    ~AbstractSplitView();

    virtual const char *getName(void) const;

    /// Message handler
    virtual bool onMsg(const char* pMsg, const char** ppReturn);
    virtual bool onHasMsg(const char* pMsg) const;
    virtual void OnChange(ParameterGrp::SubjectType &rCaller,ParameterGrp::MessageType Reason);
    virtual void onUpdate(void);
    virtual void deleteSelf();

    View3DInventorViewer *getViewer(unsigned int) const;
    void setOverrideCursor(const QCursor&);

    PyObject *getPyObject(void);
    void setPyObject(PyObject *);
    int getSize();

protected:
    void setupSettings();

protected:
    /// handle to the viewer parameter group
    ParameterGrp::handle hGrp;
    std::vector<View3DInventorViewer*> _viewer;
    PyObject *_viewerPy;
};

class AbstractSplitViewPy : public Py::PythonExtension<AbstractSplitViewPy>
{
public:
    static void init_type(void);    // announce properties and methods

    AbstractSplitViewPy(AbstractSplitView *vi);
    ~AbstractSplitViewPy();

    Py::Object repr();

    Py::Object fitAll(const Py::Tuple&);
    Py::Object viewBottom(const Py::Tuple&);
    Py::Object viewFront(const Py::Tuple&);
    Py::Object viewLeft(const Py::Tuple&);
    Py::Object viewRear(const Py::Tuple&);
    Py::Object viewRight(const Py::Tuple&);
    Py::Object viewTop(const Py::Tuple&);
    Py::Object viewIsometric(const Py::Tuple&);
    Py::Object getViewer(const Py::Tuple&);
    Py::Object sequence_item(ssize_t);
    Py::Object close(const Py::Tuple&);
    int sequence_length();

private:
    AbstractSplitView* _view;
    friend class AbstractSplitView;
    void testExistence();
};

/** The SplitView3DInventor class allows to create a window with two or more Inventor views.
 *  \author Werner Mayer
 */
class GuiExport SplitView3DInventor : public AbstractSplitView
{
    TYPESYSTEM_HEADER();

public:
    SplitView3DInventor(int views, Gui::Document* pcDocument, QWidget* parent, Qt::WindowFlags wflags=0);
    ~SplitView3DInventor();
};

} // namespace Gui

#endif  //GUI_SPLITVIEW3DINVENTOR_H

