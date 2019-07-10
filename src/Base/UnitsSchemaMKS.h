/***************************************************************************
 *   Copyright (c) 2009 Juergen Riegel  (FreeCAD@juergen-riegel.net>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_UNITSSCHEMAMKS_H
#define BASE_UNITSSCHEMAMKS_H


#include <string>
#include <QString>
#include "UnitsSchema.h"

namespace Base {
    

/**
 * The UnitSchema class
 */
class UnitsSchemaMKS: public UnitsSchema
{
public:
    virtual QString schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString);
};


} // namespace Base


#endif // BASE_UNITSSCHEMAMKS_H
