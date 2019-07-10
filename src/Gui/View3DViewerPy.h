/***************************************************************************
 *   Copyright (c) Stefan Tröger          (stefantroeger@gmx.net) 2014     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_VIEW3DVIEWERPY_H
#define GUI_VIEW3DVIEWERPY_H

#include "Base/PyObjectBase.h"
#include <CXX/Extensions.hxx>
#include <list>

namespace Gui {

class View3DInventorViewer;

/**
 * @brief Python interface for View3DInventorViewer
 * 
 * The interface does not offer all methods the c++ View3DInventorViewer counterpart has, respectively
 * also not everything the QuarterWidget and the SoQtQuarterAdaptor offers. It only exposes 
 * methods with additioanl functionality in comparison to the View3DInventorPy class. Everything that
 * can be done from there has no interface here. 
 */
class View3DInventorViewerPy : public Py::PythonExtension<View3DInventorViewerPy>
{
public:
    static void init_type(void);    // announce properties and methods

    View3DInventorViewerPy(View3DInventorViewer *vi);
    ~View3DInventorViewerPy();

    Py::Object repr();
    Py::Object getattr(const char *);
    int setattr(const char *, const Py::Object &);

    //exposed methods
    Py::Object getSoEventManager(const Py::Tuple&);
    Py::Object getSoRenderManager(const Py::Tuple&);
    Py::Object getSceneGraph(const Py::Tuple&);
    Py::Object setSceneGraph(const Py::Tuple&);

    Py::Object seekToPoint(const Py::Tuple&);
    Py::Object setFocalDistance(const Py::Tuple& args);
    Py::Object getFocalDistance(const Py::Tuple& args);
    Py::Object getPoint(const Py::Tuple& args);
    Py::Object getPickRadius(const Py::Tuple& args);
    Py::Object setPickRadius(const Py::Tuple& args);

    Py::Object setBackgroundColor(const Py::Tuple& args);
    Py::Object setRedirectToSceneGraph(const Py::Tuple& args);
    Py::Object isRedirectedToSceneGraph(const Py::Tuple& args);

    // NaviCube handling
    Py::Object setEnabledNaviCube(const Py::Tuple& args);
    Py::Object isEnabledNaviCube(const Py::Tuple& args);
    Py::Object setNaviCubeCorner(const Py::Tuple& args);


private:
    typedef PyObject* (*method_varargs_handler)(PyObject *_self, PyObject *_args);
    static method_varargs_handler pycxx_handler;
    static PyObject *method_varargs_ext_handler(PyObject *_self, PyObject *_args);

private:
    std::list<PyObject*> callbacks;
    View3DInventorViewer* _viewer;
    friend class View3DInventorViewer;
};

} // namespace Gui

#endif //GUI_VIEW3DPY_H
