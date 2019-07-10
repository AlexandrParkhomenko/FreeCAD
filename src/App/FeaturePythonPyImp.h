/***************************************************************************
 *   Copyright (c) 2013 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

#ifndef APP_FEATUREPYTHONPYIMP_H
#define APP_FEATUREPYTHONPYIMP_H

#include "Base/BaseClass.h"
#include "Base/Interpreter.h"
#include "App/PropertyContainerPy.h"

#define PYTHON_TYPE_DEF(_class_, _subclass_) \
    class _class_ : public _subclass_ \
    { \
    public: \
        static PyTypeObject Type; \
    public: \
        _class_(Base::BaseClass *pcObject, PyTypeObject *T = &Type); \
        virtual ~_class_(); \
    };

#define PYTHON_TYPE_IMP(_class_, _subclass_) \
    PyTypeObject _class_::Type = { \
        PyVarObject_HEAD_INIT(&PyType_Type, 0) \
        ""#_class_"",  \
        sizeof(_class_),  \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        Py_TPFLAGS_BASETYPE|Py_TPFLAGS_DEFAULT, \
        ""#_class_"", \
        0, 0, 0, 0, 0, 0, 0, 0, 0, \
        &_subclass_::Type, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 \
    }; \
    _class_::_class_(Base::BaseClass *pcObject, PyTypeObject *T) \
        : _subclass_(reinterpret_cast<_subclass_::PointerType>(pcObject), T) \
    { \
    } \
    _class_::~_class_() \
    { \
    }



namespace App
{

/**
 * @author Werner Mayer
 */
template <class FeaturePyT>
class FeaturePythonPyT : public FeaturePyT
{
public:
    static PyTypeObject   Type;

public:
    FeaturePythonPyT(Base::BaseClass *pcObject, PyTypeObject *T = &Type);
    virtual ~FeaturePythonPyT();

    /** @name callbacks and implementers for the python object methods */
    //@{
    static  int __setattro(PyObject *PyObj, PyObject *attro, PyObject *value);
    //@}
    PyObject *_getattr(const char *attr);              // __getattr__ function
    int _setattr(const char *attr, PyObject *value);        // __setattr__ function

protected:
    PyObject * dict_methods;

private:
};

} //namespace App

#include "FeaturePythonPyImp.inl"

#endif // APP_FEATUREPYTHONPYIMP_H
