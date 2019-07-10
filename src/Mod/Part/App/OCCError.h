/***************************************************************************
 *   Copyright (c) Sebastian Hoogen   (github@sebastianhoogen.de) 2014     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/

#ifndef _OCCError_h_
#define _OCCError_h_

#include "stdexport.h"
# include <Standard_Version.hxx>
# include <Standard_Failure.hxx>
# include <Standard_AbortiveTransaction.hxx>
# include <Standard_ConstructionError.hxx>
# include <Standard_DefineException.hxx>
# include <Standard_DimensionError.hxx>
# include <Standard_DimensionMismatch.hxx>
# include <Standard_DivideByZero.hxx>
# include <Standard_DomainError.hxx>
# include <Standard_ImmutableObject.hxx>
# include <Standard_LicenseError.hxx>
# include <Standard_LicenseNotFound.hxx>
# include <Standard_MultiplyDefined.hxx>
# include <Standard_NegativeValue.hxx>
# include <Standard_NoMoreObject.hxx>
# include <Standard_NoSuchObject.hxx>
# include <Standard_NotImplemented.hxx>
# include <Standard_NullObject.hxx>
# include <Standard_NullValue.hxx>
# include <Standard_NumericError.hxx>
# include <Standard_OutOfMemory.hxx>
# include <Standard_OutOfRange.hxx>
# include <Standard_Overflow.hxx>
# include <Standard_ProgramError.hxx>
# include <Standard_RangeError.hxx>
# include <Standard_TooManyUsers.hxx>
# include <Standard_TypeMismatch.hxx>
# include <Standard_Underflow.hxx>

#include "Base/Console.h"
#include "Base/PyObjectBase.h"
#include "Base/Interpreter.h"
#include "Base/Exception.h"
#include "App/Application.h"

namespace Part {
Standard_EXPORT extern PyObject* PartExceptionOCCError;
Standard_EXPORT extern PyObject* PartExceptionOCCDomainError;
Standard_EXPORT extern PyObject* PartExceptionOCCRangeError;
Standard_EXPORT extern PyObject* PartExceptionOCCConstructionError;
Standard_EXPORT extern PyObject* PartExceptionOCCDimensionError;


#define PY_TRY	try 

#ifndef DONT_CATCH_CXX_EXCEPTIONS 
/// see docu of PY_TRY 
#  define PY_CATCH_OCC catch (Standard_Failure &e)                  \
    {                                                               \
        std::string str;                                            \
        Standard_CString msg = e.GetMessageString();                \
        str += typeid(e).name();                                    \
        str += " ";                                                 \
        if (msg) {str += msg;}                                      \
        else     {str += "No OCCT Exception Message";}              \
        Base::Console().Error(str.c_str());                         \
        Py_Error(Part::PartExceptionOCCError,str.c_str());          \
    }                                                               \
    catch(Base::Exception &e)                                       \
    {                                                               \
        std::string str;                                            \
        str += "FreeCAD exception thrown (";                        \
        str += e.what();                                            \
        str += ")";                                                 \
        e.ReportException();                                        \
        Py_Error(Base::BaseExceptionFreeCADError,str.c_str());      \
    }                                                               \
    catch(std::exception &e)                                        \
    {                                                               \
        std::string str;                                            \
        str += "STL exception thrown (";                            \
        str += e.what();                                            \
        str += ")";                                                 \
        Base::Console().Error(str.c_str());                         \
        Py_Error(Base::BaseExceptionFreeCADError,str.c_str());      \
    }                                                               \
    catch(const Py::Exception&)                                     \
    {                                                               \
        return NULL;                                                \
    }                                                               \
    catch(const char *e)                                            \
    {                                                               \
        Py_Error(Base::BaseExceptionFreeCADError,e);                \
    }                                                               \
    catch(...)                                                      \
    {                                                               \
        Py_Error(Base::BaseExceptionFreeCADError,"Unknown C++ exception"); \
    }

#else
/// see docu of PY_TRY 
#  define PY_CATCH_OCC catch (Standard_Failure &e)                  \
    {                                                               \
        std::string str;                                            \
        Standard_CString msg = e.GetMessageString();                \
        str += typeid(e).name();                                    \
        str += " ";                                                 \
        if (msg) {str += msg;}                                      \
        else     {str += "No OCCT Exception Message";}              \
        Base::Console().Error(str.c_str());                         \
        Py_Error(Part::PartExceptionOCCError,str.c_str());          \
    }                                                               \
    catch(Base::Exception &e)                                       \
    {                                                               \
        std::string str;                                            \
        str += "FreeCAD exception thrown (";                        \
        str += e.what();                                            \
        str += ")";                                                 \
        e.ReportException();                                        \
        Py_Error(Base::BaseExceptionFreeCADError,str.c_str());      \
    }                                                               \
    catch(std::exception &e)                                        \
    {                                                               \
        std::string str;                                            \
        str += "STL exception thrown (";                            \
        str += e.what();                                            \
        str += ")";                                                 \
        Base::Console().Error(str.c_str());                         \
        Py_Error(Base::BaseExceptionFreeCADError,str.c_str());      \
    }                                                               \
    catch(const Py::Exception&)                                     \
    {                                                               \
        return NULL;                                                \
    }                                                               \
    catch(const char *e)                                            \
    {                                                               \
        Py_Error(Base::BaseExceptionFreeCADError,e);                \
    }

#endif  // DONT_CATCH_CXX_EXCEPTIONS
} //namespace Part
#endif  // _OCCError_h_

