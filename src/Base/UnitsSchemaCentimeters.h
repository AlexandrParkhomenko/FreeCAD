/***************************************************************************
 *   Copyright (c) 2016 Yorik van Havre <yorik@uncreated.net>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef BASE_UNITSSCHEMACENTIMETERS_H
#define BASE_UNITSSCHEMACENTIMETERS_H


#include <string>
#include <QString>
#include "UnitsSchema.h"

namespace Base {

/**
 * The UnitSchema class
 */
class UnitsSchemaCentimeters: public UnitsSchema
{
public:
    virtual QString schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString);
};

} // namespace Base

#endif // BASE_UNITSSCHEMACENTIMETERS_H
