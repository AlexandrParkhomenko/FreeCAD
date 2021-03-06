/***************************************************************************
 *   Copyright (c) 2016 Yorik van Havre <yorik@uncreated.net>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifdef __GNUC__
# include <unistd.h>
#endif

#include <QString>
#include <QLocale>
#include "Exception.h"
#include "UnitsApi.h"
#include "UnitsSchemaCentimeters.h"
#include <cmath>

using namespace Base;


QString UnitsSchemaCentimeters::schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString)
{
    Unit unit = quant.getUnit();
    if (unit == Unit::Length) {
        // all length units in centimeters
        unitString = QString("cm");
        factor = 10.0;
    }
    else if (unit == Unit::Area) {
        // all area units in square meters
        unitString = QString("m^2");
        factor = 1000000.0;
    }
    else if (unit == Unit::Volume) {
        // all area units in cubic meters
        unitString = QString("m^3");
        factor = 1000000000.0;
    }
    else if (unit == Unit::Power) {
        unitString = QString("W");
        factor = 1000000;
    }
    else if (unit == Unit::ElectricPotential) {
        unitString = QString("V");
        factor = 1000000;
    }
    else if (unit == Unit::HeatFlux) {
        unitString = QString("W/m^2");
        factor = 1.0;
    }
    else if (unit == Unit::Velocity) {
        unitString = QString("mm/min");
        factor = 1.0/60;
    }
    else {
        // default action for all cases without special treatment:
        unitString = quant.getUnit().getString();
        factor = 1.0;
    }

    return toLocale(quant, factor, unitString);
}
