/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_PYTHONDEBUG_H
#define GUI_PYTHONDEBUG_H

#include "stdexport.h"
#include <CXX/Extensions.hxx>
#include <frameobject.h>
#include <string>
#include <set>

namespace Gui {

class Breakpoint
{
public:
    Breakpoint();
    Breakpoint(const Breakpoint&);
    Breakpoint& operator=(const Breakpoint&);

    ~Breakpoint();

    const QString& filename() const;
    void setFilename(const QString& fn);

    bool operator ==(const Breakpoint& bp);
    bool operator ==(const QString& fn);

    void addLine(int line);
    void removeLine(int line);
    bool checkLine(int line);

    int countLines()const;
    int lineIndex(int ind)const;

    bool checkBreakpoint(const QString& fn, int line);

private:
    QString _filename;
    std::set<int> _linenums;
};

inline const QString& Breakpoint::filename()const
{
    return _filename;
}

inline int Breakpoint::countLines()const
{
    return static_cast<int>(_linenums.size());
}

inline bool Breakpoint::checkBreakpoint(const QString& fn, int line)
{
    assert(!_filename.isEmpty());
    if (_linenums.find(line) != _linenums.end())
    {
        return fn == _filename;
    }
    return false;
}

inline bool Breakpoint::operator ==(const Breakpoint& bp)
{
    return _filename == bp._filename;
}

inline bool Breakpoint::operator ==(const QString& fn)
{
    return _filename == fn;
}

/**
 * @author Werner Mayer
 */
class GuiExport PythonDebugModule : public Py::ExtensionModule<PythonDebugModule>
{
public:
    static void init_module(void);

    PythonDebugModule();
    virtual ~PythonDebugModule();

private:
    Py::Object getFunctionCallCount(const Py::Tuple &a);
    Py::Object getExceptionCount(const Py::Tuple &a);
    Py::Object getLineCount(const Py::Tuple &a);
    Py::Object getFunctionReturnCount(const Py::Tuple &a);
};

/**
 * @author Werner Mayer
 */
class GuiExport PythonDebugStdout : public Py::PythonExtension<PythonDebugStdout> 
{
public:
    static void init_type(void);    // announce properties and methods

    PythonDebugStdout();
    ~PythonDebugStdout();

    Py::Object repr();
    Py::Object write(const Py::Tuple&);
    Py::Object flush(const Py::Tuple&);
};

/**
 * @author Werner Mayer
 */
class GuiExport PythonDebugStderr : public Py::PythonExtension<PythonDebugStderr> 
{
public:
    static void init_type(void);    // announce properties and methods

    PythonDebugStderr();
    ~PythonDebugStderr();

    Py::Object repr();
    Py::Object write(const Py::Tuple&);
};

/**
 * @author Werner Mayer
 */
class GuiExport PythonDebugExcept : public Py::PythonExtension<PythonDebugExcept> 
{
public:
    static void init_type(void);    // announce properties and methods

    PythonDebugExcept();
    ~PythonDebugExcept();

    Py::Object repr();
    Py::Object excepthook(const Py::Tuple&);
};

class GuiExport PythonDebugger : public QObject
{
    Q_OBJECT

public:
    PythonDebugger();
    ~PythonDebugger();
    Breakpoint getBreakpoint(const QString&) const;
    bool toggleBreakpoint(int line, const QString&);
    void runFile(const QString& fn);
    bool isRunning() const;
    bool start();
    bool stop();
    void tryStop();
    void stepOver();
    void stepInto();
    void stepRun();
    void showDebugMarker(const QString&, int line);
    void hideDebugMarker(const QString&);

Q_SIGNALS:
    void signalNextStep();

private:
    static int tracer_callback(PyObject *obj, PyFrameObject *frame, int what, PyObject *arg);

private:
    struct PythonDebuggerP* d;
};

} // namespace Gui

#endif // GUI_PYTHONDEBUG_H
