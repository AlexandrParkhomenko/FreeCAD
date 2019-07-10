/***************************************************************************
 *   Copyright (c) 2009 Juergen Riegel  (FreeCAD@juergen-riegel.net>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef BASE_UNITSSCHEMAIMPERIAL1_H
#define BASE_UNITSSCHEMAIMPERIAL1_H


#include <string>
#include <QString>
#include "UnitsSchema.h"

namespace Base {
    

/** The schema class for the imperial unit system
 *  Here are the definitions for the imperial unit system.
 *  It also defines how the value/units get printed.
 */
class UnitsSchemaImperial1: public UnitsSchema
{
public:
    //virtual void setSchemaUnits(void);
    //virtual void resetSchemaUnits(void);
    virtual QString schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString);
};

/** The schema class for the imperial unit system
 *  Here are the definitions for the imperial unit system.
 *  It also defines how the value/units get printed.
 */
class UnitsSchemaImperialDecimal: public UnitsSchema
{
public:
    //virtual void setSchemaUnits(void);
    //virtual void resetSchemaUnits(void);
    virtual QString schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString);
};

/** The schema class for the imperial unit system
 *  Here are the definitions for the imperial unit system.
 *  It also defines how the value/units get printed.
 */
class UnitsSchemaImperialBuilding: public UnitsSchema
{
public:
    //virtual void setSchemaUnits(void);
    //virtual void resetSchemaUnits(void);
    virtual QString schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString);
};

/** The schema class for Civil Engineering in the imperial unit system
 *  All measurements in ft, ft^2, ft^3, ft/sec.  
 *  Pressure is in psi.
 */
class UnitsSchemaImperialCivil: public UnitsSchema
{
public:
    //virtual void setSchemaUnits(void);
    //virtual void resetSchemaUnits(void);
    virtual QString schemaTranslate(const Base::Quantity& quant, double &factor, QString &unitString);
};


} // namespace Base


#endif // BASE_UNITSSCHEMAIMPERIAL1_H
