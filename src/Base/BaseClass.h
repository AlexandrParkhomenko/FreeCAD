/***************************************************************************
 *   Copyright (c) Riegel         <juergen.riegel@web.de>                  *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef BASE_BASECLASS_H
#define BASE_BASECLASS_H

#include "stdexport.h"

#include "Type.h"

// Python stuff
typedef struct _object PyObject;


/// define for subclassing Base::BaseClass
#define TYPESYSTEM_HEADER() \
public: \
  static Base::Type getClassTypeId(void); \
  virtual Base::Type getTypeId(void) const; \
  static void init(void);\
  static void *create(void);\
private: \
  static Base::Type classTypeId


/// Like TYPESYSTEM_HEADER, but declare getTypeId as 'override'
#define TYPESYSTEM_HEADER_WITH_OVERRIDE() \
public: \
  static Base::Type getClassTypeId(void); \
  virtual Base::Type getTypeId(void) const override; \
  static void init(void);\
  static void *create(void);\
private: \
  static Base::Type classTypeId


/// define to implement a  subclass of Base::BaseClass
#define TYPESYSTEM_SOURCE_P(_class_) \
Base::Type _class_::getClassTypeId(void) { return _class_::classTypeId; } \
Base::Type _class_::getTypeId(void) const { return _class_::classTypeId; } \
Base::Type _class_::classTypeId = Base::Type::badType();  \
void * _class_::create(void){\
   return new _class_ ();\
}

/// define to implement a  subclass of Base::BaseClass
#define TYPESYSTEM_SOURCE_ABSTRACT_P(_class_) \
Base::Type _class_::getClassTypeId(void) { return _class_::classTypeId; } \
Base::Type _class_::getTypeId(void) const { return _class_::classTypeId; } \
Base::Type _class_::classTypeId = Base::Type::badType();  \
void * _class_::create(void){return 0;}


/// define to implement a subclass of Base::BaseClass
#define TYPESYSTEM_SOURCE(_class_, _parentclass_) \
TYPESYSTEM_SOURCE_P(_class_);\
void _class_::init(void){\
  initSubclass(_class_::classTypeId, #_class_ , #_parentclass_, &(_class_::create) ); \
}

/// define to implement a subclass of Base::BaseClass
#define TYPESYSTEM_SOURCE_ABSTRACT(_class_, _parentclass_) \
TYPESYSTEM_SOURCE_ABSTRACT_P(_class_);\
void _class_::init(void){\
  initSubclass(_class_::classTypeId, #_class_ , #_parentclass_, &(_class_::create) ); \
}

namespace Base
{
/// BaseClass class and root of the type system
class BaseExport BaseClass
{
public: 
  static Type getClassTypeId(void); 
  virtual Type getTypeId(void) const; 
  bool isDerivedFrom(const Type type) const {return getTypeId().isDerivedFrom(type);}

  static void init(void);

  virtual PyObject *getPyObject(void);
  virtual void setPyObject(PyObject *);

  static void *create(void){return 0;}
private: 
  static Type classTypeId;
protected:
  static void initSubclass(Base::Type &toInit,const char* ClassName, const char *ParentName, Type::instantiationMethod method=0);

public:
  /// Construction
  BaseClass();
  /// Destruction
  virtual ~BaseClass();

};

/**
  * Template that works just like dynamic_cast, but expects the argument to
  * inherit from Base::BaseClass.
  *
  */
template<typename T> T * freecad_dynamic_cast(Base::BaseClass * t)
{
    if (t && t->isDerivedFrom(T::getClassTypeId()))
        return static_cast<T*>(t);
    else
        return 0;
}
 
/**
 * Template that works just like dynamic_cast, but expects the argument to
 * inherit from a const Base::BaseClass.
 *
 */
template<typename T> const T * freecad_dynamic_cast(const Base::BaseClass * t)
{
    if (t && t->isDerivedFrom(T::getClassTypeId()))
        return static_cast<const T*>(t);
    else
        return 0;
}


} //namespace Base

#endif // BASE_BASECLASS_H

