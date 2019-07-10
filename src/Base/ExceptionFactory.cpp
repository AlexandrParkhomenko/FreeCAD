/***************************************************************************
 *   Copyright (c) 2017 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include "ExceptionFactory.h"
#include <CXX/Objects.hxx>

using namespace Base;

ExceptionFactory* ExceptionFactory::_pcSingleton = NULL;

ExceptionFactory& ExceptionFactory::Instance(void)
{
    if (_pcSingleton == NULL)
        _pcSingleton = new ExceptionFactory;
    return *_pcSingleton;
}

void ExceptionFactory::Destruct (void)
{
    if (_pcSingleton != 0)
        delete _pcSingleton;
    _pcSingleton = 0;
}

void ExceptionFactory::raiseException (PyObject * pydict) const
{
    std::string classname;
    
    Py::Dict edict(pydict);
    if (edict.hasKey("sclassname")) {
        classname = static_cast<std::string>(Py::String(edict.getItem("sclassname")));

        std::map<const std::string, AbstractProducer*>::const_iterator pProd;

        pProd = _mpcProducers.find(classname.c_str());
        if (pProd != _mpcProducers.end())
            static_cast<AbstractExceptionProducer *>(pProd->second)->raiseException(pydict);
    }
}


