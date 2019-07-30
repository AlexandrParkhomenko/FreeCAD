/***************************************************************************
 *   Copyright (c) 2009 Juergen Riegel (FreeCAD@juergen-riegel.net)        *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifdef __GNUC__
# include <unistd.h>
#endif

#include <QString>
#include <QLocale>
#include "Exception.h"
#include "UnitsApi.h"
#include "UnitsSchemaMmMin.h"
#include <cmath>


using namespace Base;


QString UnitsSchemaMmMin::schemaTranslate(const Quantity &quant, double &factor, QString &unitString)
{
    Unit unit = quant.getUnit();
    if (unit == Unit::Length) {
        unitString = QString("mm");
        factor = 1.0;
    }
    else if (unit == Unit::Angle) {
        unitString = QString("\xC2\xB0");
        //unitString = QString(u8"\u00B0"); //C++11 - Not supported by VS2013
        factor = 1.0;
    }
    else if (unit == Unit::Velocity) {
        unitString = QString("mm/min");
        factor = 1./60.;
    }
    else {
        // default action for all cases without special treatment:
        unitString = quant.getUnit().getString();
        factor = 1.0;
    }

    return toLocale(quant, factor, unitString);
}
