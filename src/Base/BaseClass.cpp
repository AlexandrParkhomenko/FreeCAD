/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/



# include <assert.h>

/// Here the FreeCAD includes sorted by Base,App,Gui......
#include "BaseClass.h"
#include "PyObjectBase.h"

using namespace Base;

Type BaseClass::classTypeId = Base::Type::badType();
   
  
//**************************************************************************
// Construction/Destruction

/**
 * A constructor.
 * A more elaborate description of the constructor.
 */
BaseClass::BaseClass()
{

}

/**
 * A destructor.
 * A more elaborate description of the destructor.
 */
BaseClass::~BaseClass()
{
}


//**************************************************************************
// separator for other implementation aspects

void BaseClass::init(void)
{
    assert(BaseClass::classTypeId == Type::badType() && "don't init() twice!");
    /* Make sure superclass gets initialized before subclass. */ 
    /*assert(strcmp(#_parentclass_), "inherited"));*/
    /*Type parentType(Type::fromName(#_parentclass_));*/ 
    /*assert(parentType != Type::badType() && "you forgot init() on parentclass!");*/

    /* Set up entry in the type system. */ 
    BaseClass::classTypeId = 
        Type::createType(Type::badType(), 
                         "Base::BaseClass", 
                         BaseClass::create); 
}

Type BaseClass::getClassTypeId(void) 
{
    return BaseClass::classTypeId; 
}

Type BaseClass::getTypeId(void) const 
{
    return BaseClass::classTypeId; 
}


void BaseClass::initSubclass(Base::Type &toInit,const char* ClassName, const char *ParentName,
                             Type::instantiationMethod method)
{
    // don't init twice!
    assert(toInit == Base::Type::badType());
    // get the parent class
    Base::Type parentType(Base::Type::fromName(ParentName)); 
    // forgot init parent!
    assert(parentType != Base::Type::badType() );

    // create the new type
    toInit = Base::Type::createType(parentType, ClassName, method);
}

/**
 * This method returns the Python wrapper for a C++ object. It's in the responsibility of 
 * the programmer to do the correct reference counting. Basically there are two ways how
 * to implement that: Either always return a new Python object then reference counting is
 * not a matter or return always the same Python object then the reference counter must be
 * incremented by one. However, it's absolutely forbidden to return always the same Python
 * object without incrementing the reference counter. 
 *
 * The default implementation returns 'None'.
 */
PyObject *BaseClass::getPyObject(void)
{
    assert(0);
    Py_Return;
}

void BaseClass::setPyObject(PyObject *)
{
    assert(0);
}
