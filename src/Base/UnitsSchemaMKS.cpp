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
#include "UnitsSchemaMKS.h"
#include <cmath>

using namespace Base;


QString UnitsSchemaMKS::schemaTranslate(const Quantity &quant, double &factor, QString &unitString)
{
    double UnitValue = std::abs(quant.getValue());
    Unit unit = quant.getUnit();

    // now do special treatment on all cases seems necessary:
    if (unit == Unit::Length) {  // Length handling ============================
        if (UnitValue < 0.000000001) {// smaller then 0.001 nm -> scientific notation
            unitString = QString("m");
            factor = 1000.0;
        }
        else if(UnitValue < 0.001) {
            unitString = QString("nm");
            factor = 0.000001;
        }
        else if(UnitValue < 0.1) {
            unitString = QString::fromUtf8("\xC2\xB5m");
            factor = 0.001;
        }
        else if(UnitValue < 100.0) {
            unitString = QString("mm");
            factor = 1.0;
        }
        else if(UnitValue < 10000000.0) {
            unitString = QString("m");
            factor = 1000.0;
        }
        else if(UnitValue < 100000000000.0 ) {
            unitString = QString("km");
            factor = 1000000.0;
        }
        else { // bigger then 1000 km -> scientific notation
            unitString = QString("m");
            factor = 1000.0;
        }
    }
    else if (unit == Unit::Area) {
        if (UnitValue < 100.0) {// smaller than 1 square cm
            unitString = QString("mm^2");
            factor = 1.0;
        }
        else if (UnitValue < 10000000000000.0) {
            unitString = QString("m^2");
            factor = 1000000.0;
        }
        else { // bigger then 1 square kilometer
            unitString = QString("km^2");
            factor = 1000000000000.0;
        }
    }
    else if (unit == Unit::Mass) {
        // TODO Cascade for the weights
        // default action for all cases without special treatment:
        unitString = quant.getUnit().getString();
        factor = 1.0;
    }
    else if (unit == Unit::Density) {
        if (UnitValue < 0.0001) {
            unitString = QString("kg/m^3");
            factor = 0.000000001;
        }
        else if (UnitValue < 1.0) {
            unitString = QString("kg/cm^3");
            factor = 0.001;
        }
        else {
            unitString = QString("kg/mm^3");
            factor = 1.0;
        }
    }
    else if (unit == Unit::Volume) {
        if (UnitValue < 1000000.0) {// smaller than 10 cubic cm
            unitString = QString("mm^3");
            factor = 1.0;
        }
        else if (UnitValue < 1000000000000000000.0) {
            unitString = QString("m^3");
            factor = 1000000000.0;
        }
        else { // bigger then 1 cubic kilometer
            unitString = QString("km^3");
            factor = 1000000000000000000.0;
        }
    }
    else if ((unit == Unit::Pressure) || (unit == Unit::Stress)) {
        if (UnitValue < 10.0) {// Pa is the smallest
            unitString = QString("Pa");
            factor = 0.001;
        }
        else if (UnitValue < 10000.0) {
            unitString = QString("kPa");
            factor = 1.0;
        }
        else if (UnitValue < 10000000.0) {
            unitString = QString("MPa");
            factor = 1000.0;
        }
        else if (UnitValue < 10000000000.0) {
            unitString = QString("GPa");
            factor = 1000000.0;
        }
        else { // bigger then 1000 GPa -> scientific notation
            unitString = QString("Pa");
            factor = 0.001;
        }
    }
    else if (unit == Unit::ThermalConductivity) {
        if (UnitValue > 1000000) {
            unitString = QString("W/mm/K");
            factor = 1000000.0;
        }
        else {
            unitString = QString("W/m/K");
            factor = 1000.0;
        }
    }
    else if (unit == Unit::ThermalExpansionCoefficient) {
        if (UnitValue < 0.001) {
            unitString = QString::fromUtf8("\xC2\xB5m/m/K");
            factor = 0.000001;
        }
        else {
            unitString = QString("m/m/K");
            factor = 1.0;
        }
    }
    else if (unit == Unit::SpecificHeat) {
        unitString = QString("J/kg/K");
        factor = 1000000.0;
    }
    else if (unit == Unit::ThermalTransferCoefficient) {
        unitString = QString("W/m^2/K");
        factor = 1.0;
    }
    else if (unit == Unit::Power) {
        unitString = QString("W");
        factor = 1000000;
    }
    else if (unit == Unit::ElectricPotential) {
        unitString = QString("V");
        factor = 1000000;
    }
    else if (unit == Unit::SpecificEnergy) {
        unitString = QString("m^2/s^2");
        factor = 1000000;
    }
    else if (unit == Unit::HeatFlux) {
        unitString = QString("W/m^2");
        factor = 1.0;
    }
    else if (unit == Unit::Velocity) {
        unitString = QString("m/s");
        factor = 1000.0;
    }
    else if (unit == Unit::DynamicViscosity) {
        unitString = QString("kg/(m*s)");
        factor = 0.001;
    }
    else {
        // default action for all cases without special treatment:
        unitString = quant.getUnit().getString();
        factor = 1.0;
    }

    return toLocale(quant, factor, unitString);
}
