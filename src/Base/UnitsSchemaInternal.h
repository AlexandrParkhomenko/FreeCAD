/***************************************************************************
 *   Copyright (c) 2009 Juergen Riegel  (FreeCAD@juergen-riegel.net>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_UNITSSCHEMAINTERNAL_H
#define BASE_UNITSSCHEMAINTERNAL_H


#include <string>
#include <QString>
#include "UnitsSchema.h"

namespace Base {
    

/** The standard units schema
 *  Here is defined what internal (base) units FreeCAD uses.
 *  FreeCAD uses a mm/kg/deg scala.
 *  Also it defines how the units get presented.
 */
class UnitsSchemaInternal: public UnitsSchema
{
public:
    virtual QString schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString);
};


} // namespace Base


#endif // BASE_UNITSSCHEMAINTERNAL_H
