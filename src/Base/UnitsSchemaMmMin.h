/***************************************************************************
 *   Copyright (c) 2009 Juergen Riegel  (FreeCAD@juergen-riegel.net>       *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_UNITSSCHEMAMMMIN_H
#define BASE_UNITSSCHEMAMMMIN_H


#include <string>
#include <QString>
#include "UnitsSchema.h"

namespace Base {


/*  Metric units schema intended for design of small parts and for CNC
 *  Lengths are alwais in mm.
 *  Angles in degrees (use degree symbol)
 *  Velocities in mm/min (as used in g-code).
 */
class UnitsSchemaMmMin: public UnitsSchema
{
public:
    virtual QString schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString);
};


} // namespace Base


#endif // BASE_UNITSSCHEMAMMMIN_H
