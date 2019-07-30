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
#include "UnitsSchema.h"

using namespace Base;

QString UnitsSchema::toLocale(const Base::Quantity& quant, double factor, const QString& unitString) const
{
    //return QString("%L1 %2").arg(quant.getValue() / factor).arg(unitString);
    QLocale Lc = QLocale::system();
    const QuantityFormat& format = quant.getFormat();
    if (format.option != QuantityFormat::None) {
        uint opt = static_cast<uint>(format.option);
        Lc.setNumberOptions(static_cast<QLocale::NumberOptions>(opt));
    }

    QString Ln = Lc.toString((quant.getValue() / factor), format.toFormat(), format.precision);
    return QString("%1 %2").arg(Ln, unitString);
}
