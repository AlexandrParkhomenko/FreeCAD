/***************************************************************************
 *   Copyright (c) 2018 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/
 

#ifndef BASE_TRANSLATE_H
#define BASE_TRANSLATE_H

#include "stdexport.h"
#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

namespace Base {

class BaseExport Translate : public Py::ExtensionModule<Translate>
{
public:
    Translate();
    virtual ~Translate();

private:
    Py::Object translate(const Py::Tuple& args);
    Py::Object translateNoop(const Py::Tuple& args);
    Py::Object translateNoop3(const Py::Tuple& args);
    Py::Object trNoop(const Py::Tuple& args);
};

} // namespace Base 

#endif // BASE_TRANSLATE_H
