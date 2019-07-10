/***************************************************************************
 *   Copyright (c) 2004 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_PYTHONCONSOLE_PY_H
#define GUI_PYTHONCONSOLE_PY_H

#include <CXX/Extensions.hxx>

class QTimer;

namespace Gui {
class PythonConsole;

/**
 * Python class for redirection of stdout to FreeCAD's Python
 * console window. This allows to show all Python messages in  
 * the same window where the commands are performed.
 * @see PythonStderr
 * @see PythonConsole
 * @author Werner Mayer
 */
class PythonStdout : public Py::PythonExtension<PythonStdout> 
{
private:
    PythonConsole* pyConsole;

public:
    static void init_type(void);    // announce properties and methods

    PythonStdout(PythonConsole *pc);
    ~PythonStdout();

    Py::Object getattr(const char *name);
    Py::Object repr();
    Py::Object write(const Py::Tuple&);
    Py::Object flush(const Py::Tuple&);
    Py::Object isatty();
};

/**
 * Python class for redirection of stderr to FreeCAD's Python
 * console window. This allows to show all Python messages in 
 * the same window where the commands are performed.
 * @see PythonStdout
 * @see PythonConsole
 * @author Werner Mayer
 */
class PythonStderr : public Py::PythonExtension<PythonStderr> 
{
private:
    PythonConsole* pyConsole;

public:
    static void init_type(void);    // announce properties and methods

    PythonStderr(PythonConsole *pc);
    ~PythonStderr();

    Py::Object getattr(const char *name);
    Py::Object repr();
    Py::Object write(const Py::Tuple&);
    Py::Object flush(const Py::Tuple&);
    Py::Object isatty();
};

/**
 * Python class for redirection of stdout to FreeCAD's output
 * console window. This allows to report all Python output to
 * the output window which simplifies debugging scripts.
 * @see PythonStdout
 * @see PythonStderr
 * @author Werner Mayer
 */
class OutputStdout : public Py::PythonExtension<OutputStdout>
{
public:
    static void init_type(void);    // announce properties and methods

    OutputStdout();
    ~OutputStdout();

    Py::Object getattr(const char *name);
    Py::Object repr();
    Py::Object write(const Py::Tuple&);
    Py::Object flush(const Py::Tuple&);
    Py::Object isatty();
};

/**
 * Python class for redirection of stderr to FreeCAD's output
 * console window. This allows to report all Python errors to 
 * the output window which simplifies error tracking.
 * @see PythonStdout
 * @see PythonStderr
 * @author Werner Mayer
 */
class OutputStderr : public Py::PythonExtension<OutputStderr> 
{
public:
    static void init_type(void);    // announce properties and methods

    OutputStderr();
    ~OutputStderr();

    Py::Object getattr(const char *name);
    Py::Object repr();
    Py::Object write(const Py::Tuple&);
    Py::Object flush(const Py::Tuple&);
    Py::Object isatty();
};

/**
 * Python class for redirection of stdin to an input dialog of Qt.
 * @author Werner Mayer
 */
class PythonStdin : public Py::PythonExtension<PythonStdin> 
{
private:
    PythonConsole* pyConsole;

public:
    static void init_type(void);    // announce properties and methods

    PythonStdin(PythonConsole *pc);
    ~PythonStdin();

    Py::Object repr();
    Py::Object readline(const Py::Tuple&);
};

} // namespace Gui

#endif // GUI_PYTHONCONSOLE_PY_H
