/***************************************************************************
 *   Copyright (c) 2011 Juergen Riegel                                     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_Unit_H
#define BASE_Unit_H

#include "stdexport.h"
#include <stdint.h>
#include <string>
#include <QString>

namespace Base {

#define UnitSignatureLengthBits 4
#define UnitSignatureMassBits 4
#define UnitSignatureTimeBits 4
#define UnitSignatureElectricCurrentBits 4
#define UnitSignatureThermodynamicTemperatureBits 4
#define UnitSignatureAmountOfSubstanceBits 4
#define UnitSignatureLuminousIntensityBits 4
#define UnitSignatureAngleBits 4

struct UnitSignature{
    int32_t Length:UnitSignatureLengthBits;
    int32_t Mass:UnitSignatureMassBits;
    int32_t Time:UnitSignatureTimeBits;
    int32_t ElectricCurrent:UnitSignatureElectricCurrentBits;
    int32_t ThermodynamicTemperature:UnitSignatureThermodynamicTemperatureBits;
    int32_t AmountOfSubstance:UnitSignatureAmountOfSubstanceBits;
    int32_t LuminousIntensity:UnitSignatureLuminousIntensityBits;
    int32_t Angle:UnitSignatureAngleBits;
};
/**
 * The Unit class.
 */
class BaseExport Unit
{
public:
    /// default constructor
    Unit(int8_t Length,int8_t Mass=0,int8_t Time=0,int8_t ElectricCurrent=0,int8_t ThermodynamicTemperature=0,int8_t AmountOfSubstance=0,int8_t LuminousIntensity=0,int8_t Angle=0);
    Unit(void);
    Unit(const Unit&);
    Unit(const QString& expr);
    /// Destruction
    ~Unit () {}


    /** Operators. */
    //@{
    inline Unit& operator *=(const Unit& that);
    inline Unit& operator /=(const Unit& that);
    Unit operator *(const Unit&) const;
    Unit operator /(const Unit&) const;
    bool operator ==(const Unit&) const;
    bool operator !=(const Unit&that) const {return !(*this == that);}
    Unit& operator =(const Unit&);
    Unit pow(signed char exp)const;
    //@}
    /// get the unit signature
    const UnitSignature & getSignature(void)const {return Sig;} 
    bool isEmpty(void)const;
    
    QString getString(void) const;
    /// get the type as an string such as "Area", "Length" or "Pressure". 
    QString getTypeString(void) const;

    /** Predefined Unit types. */
    //@{
    /// Length unit
    static Unit Length;
    /// Mass unit
    static Unit Mass;
    /// Angle
    static Unit Angle;
    static Unit Density;

    static Unit Area;
    static Unit Volume;
    static Unit TimeSpan;
    static Unit Velocity;
    static Unit Acceleration;
    static Unit Temperature;

    static Unit ElectricCurrent;
    static Unit ElectricPotential;
    static Unit AmountOfSubstance;
    static Unit LuminousIntensity;

    // Pressure
    static Unit CompressiveStrength;
    static Unit Pressure;
    static Unit ShearModulus;
    static Unit Stress;
    static Unit UltimateTensileStrength;
    static Unit YieldStrength;
    static Unit YoungsModulus;

    static Unit Force;
    static Unit Work;
    static Unit Power;

    static Unit SpecificEnergy;
    static Unit ThermalConductivity;
    static Unit ThermalExpansionCoefficient;
    static Unit SpecificHeat;
    static Unit ThermalTransferCoefficient;
    static Unit HeatFlux;
    static Unit DynamicViscosity;
    static Unit KinematicViscosity;

    //@}
protected:
    UnitSignature Sig;
};

inline Unit& Unit::operator *=(const Unit& that)
{
    *this = *this * that;
    return *this;
}

inline Unit& Unit::operator /=(const Unit& that)
{
    *this = *this / that;
    return *this;
}

} // namespace Base

#endif // BASE_Unit_H
