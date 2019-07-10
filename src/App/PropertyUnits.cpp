/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2010     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <boost/version.hpp>
# include <boost/filesystem/path.hpp>
# include <cfloat>

/// Here the FreeCAD includes sorted by Base,App,Gui......

#include "Base/Exception.h"
#include "Base/Reader.h"
#include "Base/Writer.h"
#include "Base/Stream.h"
#include "Base/UnitsApi.h"

#include "PropertyUnits.h"
#include "Base/PyObjectBase.h"
#include "Base/QuantityPy.h"
#include "Base/UnitPy.h"

using namespace App;
using namespace Base;
using namespace std;


const PropertyQuantityConstraint::Constraints LengthStandard = {0.0,DBL_MAX,1.0};
const PropertyQuantityConstraint::Constraints AngleStandard = {-360,360,1.0};

//**************************************************************************
//**************************************************************************
// PropertyQuantity
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyQuantity, App::PropertyFloat);

Base::Quantity PropertyQuantity::getQuantityValue(void) const
{
    return Quantity(_dValue,_Unit);
}

const char* PropertyQuantity::getEditorName(void) const
{
    return "Gui::PropertyEditor::PropertyUnitItem";
}

PyObject *PropertyQuantity::getPyObject(void)
{
    return new QuantityPy (new Quantity(_dValue,_Unit));
}

Base::Quantity PropertyQuantity::createQuantityFromPy(PyObject *value)
{
    Base::Quantity quant;

    if (PyUnicode_Check(value)){
        quant = Quantity::parse(QString::fromUtf8(PyUnicode_AsUTF8(value)));
    }

    else if (PyFloat_Check(value))
        quant = Quantity(PyFloat_AsDouble(value),_Unit);
    else if (PyLong_Check(value))
        quant = Quantity((double)PyLong_AsLong(value),_Unit);
    else if (PyObject_TypeCheck(value, &(QuantityPy::Type))) {
        Base::QuantityPy  *pcObject = static_cast<Base::QuantityPy*>(value);
        quant = *(pcObject->getQuantityPtr());
    }
    else {
        std::string error = std::string("wrong type as quantity: ");
        error += value->ob_type->tp_name;
        throw Base::TypeError(error);
    }

    return quant;
}


void PropertyQuantity::setPyObject(PyObject *value)
{
    // Set the unit if Unit object supplied, else check the unit
    // and set the value
    
    if (PyObject_TypeCheck(value, &(UnitPy::Type))) {
        Base::UnitPy  *pcObject = static_cast<Base::UnitPy*>(value);
        Base::Unit unit = *(pcObject->getUnitPtr());
        _Unit = unit;
    }
    else {
        Base::Quantity quant= createQuantityFromPy(value);

        Unit unit = quant.getUnit();
        if (unit.isEmpty()){
            PropertyFloat::setValue(quant.getValue());
            return;
        }

        if (unit != _Unit)
            throw Base::UnitsMismatchError("Not matching Unit!");

        PropertyFloat::setValue(quant.getValue());
    }
}

void PropertyQuantity::setPathValue(const ObjectIdentifier & /*path*/, const boost::any &value)
{
    if (value.type() == typeid(double))
        setValue(boost::any_cast<double>(value));
    else if (value.type() == typeid(Base::Quantity))
        setValue((boost::any_cast<Quantity>(value)).getValue());
    else
        throw bad_cast();
}

const boost::any PropertyQuantity::getPathValue(const ObjectIdentifier & /*path*/) const
{
    return Quantity(_dValue, _Unit);
}

//**************************************************************************
//**************************************************************************
// PropertyQuantityConstraint
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyQuantityConstraint, App::PropertyQuantity);



void PropertyQuantityConstraint::setConstraints(const Constraints* sConstrain)
{
    _ConstStruct = sConstrain;
}

const char* PropertyQuantityConstraint::getEditorName(void) const
{
    return "Gui::PropertyEditor::PropertyUnitConstraintItem";
}


const PropertyQuantityConstraint::Constraints*  PropertyQuantityConstraint::getConstraints(void) const
{
    return _ConstStruct;
}

void PropertyQuantityConstraint::setPyObject(PyObject *value)
{
    Base::Quantity quant= createQuantityFromPy(value);

    Unit unit = quant.getUnit();
    double temp = quant.getValue();
    if (_ConstStruct) {
        if (temp > _ConstStruct->UpperBound)
            temp = _ConstStruct->UpperBound;
        else if (temp < _ConstStruct->LowerBound)
            temp = _ConstStruct->LowerBound;
    }
    quant.setValue(temp);

    if (unit.isEmpty()){
        PropertyFloat::setValue(quant.getValue());
        return;
    }

    if (unit != _Unit)
        throw Base::UnitsMismatchError("Not matching Unit!");

    PropertyFloat::setValue(quant.getValue());
}

//**************************************************************************
//**************************************************************************
// PropertyDistance
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyDistance, App::PropertyQuantity);

PropertyDistance::PropertyDistance()
{
    setUnit(Base::Unit::Length);
}

//**************************************************************************
//**************************************************************************
// PropertySpeed
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertySpeed, App::PropertyQuantity);

PropertySpeed::PropertySpeed()
{
    setUnit(Base::Unit::Velocity);
}

//**************************************************************************
//**************************************************************************
// PropertyAcceleration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyAcceleration, App::PropertyQuantity);

PropertyAcceleration::PropertyAcceleration()
{
    setUnit(Base::Unit::Acceleration);
}

//**************************************************************************
//**************************************************************************
// PropertyLength
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyLength, App::PropertyQuantityConstraint);

PropertyLength::PropertyLength()
{
    setUnit(Base::Unit::Length);
    setConstraints(&LengthStandard);
}

//**************************************************************************
//**************************************************************************
// PropertyArea
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyArea, App::PropertyQuantityConstraint);

PropertyArea::PropertyArea()
{
    setUnit(Base::Unit::Area);
    setConstraints(&LengthStandard);
}

//**************************************************************************
//**************************************************************************
// PropertyVolume
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyVolume, App::PropertyQuantityConstraint);

PropertyVolume::PropertyVolume()
{
    setUnit(Base::Unit::Volume);
    setConstraints(&LengthStandard);
}

//**************************************************************************
//**************************************************************************
// PropertyAngle
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyAngle, App::PropertyQuantityConstraint);

PropertyAngle::PropertyAngle()
{
    setUnit(Base::Unit::Angle);
    setConstraints(&AngleStandard);
}

//**************************************************************************
//**************************************************************************
// PropertyPressure
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyPressure, App::PropertyQuantity);

PropertyPressure::PropertyPressure()
{
    setUnit(Base::Unit::Pressure);
}

//**************************************************************************
//**************************************************************************
// PropertyForce
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TYPESYSTEM_SOURCE(App::PropertyForce, App::PropertyQuantity);

PropertyForce::PropertyForce()
{
    setUnit(Base::Unit::Force);
}

