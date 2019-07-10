/***************************************************************************
 *   Copyright (c) 2017 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef BASE_EXCEPTIONFACTORY_H
#define BASE_EXCEPTIONFACTORY_H


#include "stdexport.h"
#include "FCConfig.h"

#include "Factory.h"

namespace Base
{

/// Abstract base class of all exception producers
class BaseExport AbstractExceptionProducer : public AbstractProducer
{
public:
    AbstractExceptionProducer () {}
    ~AbstractExceptionProducer() {}
    // just implement it
    void* Produce () const {
        return nullptr;
    }
    virtual void raiseException(PyObject * pydict) const = 0;
};

// --------------------------------------------------------------------

/** The ExceptionFactory */
class BaseExport ExceptionFactory : public Factory
{
public:
    static ExceptionFactory& Instance(void);
    static void Destruct (void);
    
    void raiseException(PyObject * pydict) const;
    
private:
    static ExceptionFactory* _pcSingleton;
    
    ExceptionFactory(){}
    ~ExceptionFactory(){}
};

/* Producers */

template <class CLASS>
class ExceptionProducer : public AbstractExceptionProducer
{
public:
    ExceptionProducer ()
    {
        ExceptionFactory::Instance().AddProducer(typeid(CLASS).name(), this);
    }
    
    virtual ~ExceptionProducer (){}
    
    void raiseException(PyObject * pydict) const
    {
        CLASS c;
        c.setPyObject(pydict);

        throw c;
    }
};

} //namespace Base


#endif

