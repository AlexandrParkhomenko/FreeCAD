/***************************************************************************
 *   Copyright (c) 2018 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include "Translate.h"
#include <QCoreApplication>

using namespace Base;


Translate::Translate()
   : Py::ExtensionModule<Translate>("__Translate__")
{
    add_varargs_method("translate",
        &Translate::translate,
        "translate(context, sourcetext, disambiguation = None, n=-1)\n"
        "-- Returns the translation text for sourceText, by querying\n"
        "the installed translation files. The translation files are\n"
        "searched from the most recently installed file back to the\n"
        "first installed file.");
    add_varargs_method("QT_TRANSLATE_NOOP",
        &Translate::translateNoop,
        "QT_TRANSLATE_NOOP(context, sourcetext)\n"
        "Marks the UTF-8 encoded string literal sourcetext for delayed translation in the given context.\n"
        "The context is typically a class name and also needs to be specified as a string literal.");
    add_varargs_method("QT_TRANSLATE_NOOP3",
        &Translate::translateNoop3,
        "QT_TRANSLATE_NOOP3(context, sourcetext, disambiguation)\n"
        "Marks the UTF-8 encoded string literal sourceText for delayed translation in the given context\n"
        "with the given disambiguation. The context is typically a class and also needs to be specified\n"
        "as a string literal. The string literal disambiguation should be a short semantic tag to tell\n"
        "apart otherwise identical strings.");
    add_varargs_method("QT_TRANSLATE_NOOP_UTF8",
        &Translate::translateNoop,
        "QT_TRANSLATE_NOOP_UTF8(context, sourcetext)\n"
        "Same as QT_TRANSLATE_NOOP");
    add_varargs_method("QT_TR_NOOP",
        &Translate::trNoop,
        "QT_TR_NOOP(sourcetext)\n"
        "Marks the UTF-8 encoded string literal sourcetext for delayed translation in the current context");
    add_varargs_method("QT_TR_NOOP_UTF8",
        &Translate::trNoop,
        "QT_TR_NOOP_UTF8(sourcetext)\n"
        "Same as QT_TR_NOOP");
    initialize("This module is the Translate module"); // register with Python
}

Translate::~Translate()
{

}

Py::Object Translate::translate(const Py::Tuple& args)
{
    char *context;
    char *source;
    char *disambiguation = nullptr;
    int n=-1;
    if (!PyArg_ParseTuple(args.ptr(), "ss|si", &context, &source, &disambiguation, &n))
        throw Py::Exception();

    QString str = QCoreApplication::translate(context, source, disambiguation, n);
    return Py::asObject(PyUnicode_FromString(str.toUtf8()));
}

Py::Object Translate::translateNoop(const Py::Tuple& args)
{
    PyObject* arg1;
    PyObject* arg2;
    if (!PyArg_ParseTuple(args.ptr(), "OO", &arg1, &arg2))
        throw Py::Exception();
    return Py::Object(arg2);
}

Py::Object Translate::translateNoop3(const Py::Tuple& args)
{
    PyObject* arg1;
    PyObject* arg2;
    PyObject* arg3;
    if (!PyArg_ParseTuple(args.ptr(), "OOO", &arg1, &arg2, &arg3))
        throw Py::Exception();
    return Py::Object(arg2);
}

Py::Object Translate::trNoop(const Py::Tuple& args)
{
    PyObject* arg1;
    if (!PyArg_ParseTuple(args.ptr(), "O", &arg1))
        throw Py::Exception();
    return Py::Object(arg1);
}
