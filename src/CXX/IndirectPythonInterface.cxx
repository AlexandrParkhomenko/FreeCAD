//-----------------------------------------------------------------------------
//
// Copyright (c) 1998 - 2007, The Regents of the University of California
// Produced at the Lawrence Livermore National Laboratory
// All rights reserved.
//
// This file is part of PyCXX. For details,see http://cxx.sourceforge.net/. The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the PyCXX distribution.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or materials provided with the distribution.
//  - Neither the name of the UC/LLNL nor  the names of its contributors may be
//    used to  endorse or  promote products derived from  this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  REGENTS  OF  THE  UNIVERSITY OF
// CALIFORNIA, THE U.S.  DEPARTMENT  OF  ENERGY OR CONTRIBUTORS BE  LIABLE  FOR
// ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
//-----------------------------------------------------------------------------

#include "CXX/IndirectPythonInterface.hxx"

namespace Py
{
PYCXX_EXPORT bool _CFunction_Check( PyObject *op )   { return op->ob_type == _CFunction_Type(); }
PYCXX_EXPORT bool _Complex_Check( PyObject *op )     { return op->ob_type == _Complex_Type(); }
PYCXX_EXPORT bool _Dict_Check( PyObject *op )        { return op->ob_type == _Dict_Type(); }
PYCXX_EXPORT bool _Float_Check( PyObject *op )       { return op->ob_type == _Float_Type(); }
PYCXX_EXPORT bool _Function_Check( PyObject *op )    { return op->ob_type == _Function_Type(); }
PYCXX_EXPORT bool _Boolean_Check( PyObject *op )     { return op->ob_type == _Bool_Type(); }
PYCXX_EXPORT bool _List_Check( PyObject *op )        { return op->ob_type == _List_Type(); }
PYCXX_EXPORT bool _Long_Check( PyObject *op )        { return op->ob_type == _Long_Type(); }
PYCXX_EXPORT bool _Method_Check( PyObject *op )      { return op->ob_type == _Method_Type(); }
PYCXX_EXPORT bool _Module_Check( PyObject *op )      { return op->ob_type == _Module_Type(); }
PYCXX_EXPORT bool _Range_Check( PyObject *op )       { return op->ob_type == _Range_Type(); }
PYCXX_EXPORT bool _Slice_Check( PyObject *op )       { return op->ob_type == _Slice_Type(); }
PYCXX_EXPORT bool _TraceBack_Check( PyObject *op )   { return op->ob_type == _TraceBack_Type(); }
PYCXX_EXPORT bool _Tuple_Check( PyObject *op )       { return op->ob_type == _Tuple_Type(); }
PYCXX_EXPORT bool _Type_Check( PyObject *op )        { return op->ob_type == _Type_Type(); }
PYCXX_EXPORT bool _Unicode_Check( PyObject *op )     { return op->ob_type == _Unicode_Type(); }

PYCXX_EXPORT bool _Bytes_Check( PyObject *op )       { return op->ob_type == _Bytes_Type(); }


//================================================================================
//
//    Map onto Macros
//
//================================================================================

//
//    Wrap variables as function calls
//

PYCXX_EXPORT PyObject *_Exc_ArithmeticError()        { return ::PyExc_ArithmeticError; }
PYCXX_EXPORT PyObject *_Exc_AssertionError()         { return ::PyExc_AssertionError; }
PYCXX_EXPORT PyObject *_Exc_AttributeError()         { return ::PyExc_AttributeError; }
PYCXX_EXPORT PyObject *_Exc_EnvironmentError()       { return ::PyExc_EnvironmentError; }
PYCXX_EXPORT PyObject *_Exc_EOFError()               { return ::PyExc_EOFError; }
PYCXX_EXPORT PyObject *_Exc_Exception()              { return ::PyExc_Exception; }
PYCXX_EXPORT PyObject *_Exc_FloatingPointError()     { return ::PyExc_FloatingPointError; }
PYCXX_EXPORT PyObject *_Exc_ImportError()            { return ::PyExc_ImportError; }
PYCXX_EXPORT PyObject *_Exc_IndexError()             { return ::PyExc_IndexError; }
PYCXX_EXPORT PyObject *_Exc_IOError()                { return ::PyExc_IOError; }
PYCXX_EXPORT PyObject *_Exc_KeyboardInterrupt()      { return ::PyExc_KeyboardInterrupt; }
PYCXX_EXPORT PyObject *_Exc_KeyError()               { return ::PyExc_KeyError; }
PYCXX_EXPORT PyObject *_Exc_LookupError()            { return ::PyExc_LookupError; }
PYCXX_EXPORT PyObject *_Exc_MemoryError()            { return ::PyExc_MemoryError; }
PYCXX_EXPORT PyObject *_Exc_NameError()              { return ::PyExc_NameError; }
PYCXX_EXPORT PyObject *_Exc_NotImplementedError()    { return ::PyExc_NotImplementedError; }
PYCXX_EXPORT PyObject *_Exc_OSError()                { return ::PyExc_OSError; }
PYCXX_EXPORT PyObject *_Exc_OverflowError()          { return ::PyExc_OverflowError; }
PYCXX_EXPORT PyObject *_Exc_RuntimeError()           { return ::PyExc_RuntimeError; }
PYCXX_EXPORT PyObject *_Exc_SyntaxError()            { return ::PyExc_SyntaxError; }
PYCXX_EXPORT PyObject *_Exc_SystemError()            { return ::PyExc_SystemError; }
PYCXX_EXPORT PyObject *_Exc_SystemExit()             { return ::PyExc_SystemExit; }
PYCXX_EXPORT PyObject *_Exc_TypeError()              { return ::PyExc_TypeError; }
PYCXX_EXPORT PyObject *_Exc_ValueError()             { return ::PyExc_ValueError; }
PYCXX_EXPORT PyObject *_Exc_ZeroDivisionError()      { return ::PyExc_ZeroDivisionError; }
PYCXX_EXPORT PyObject *_Exc_IndentationError()       { return ::PyExc_IndentationError; }
PYCXX_EXPORT PyObject *_Exc_TabError()               { return ::PyExc_TabError; }
PYCXX_EXPORT PyObject *_Exc_UnboundLocalError()      { return ::PyExc_UnboundLocalError; }
PYCXX_EXPORT PyObject *_Exc_UnicodeError()           { return ::PyExc_UnicodeError; }




//
//    wrap items in Object.h
//
PYCXX_EXPORT PyObject *_None()                       { return &::_Py_NoneStruct; }

PYCXX_EXPORT PyObject *_False()                      { return Py_False; }
PYCXX_EXPORT PyObject *_True()                       { return Py_True; }

PYCXX_EXPORT PyTypeObject *_CFunction_Type()         { return &PyCFunction_Type; }
PYCXX_EXPORT PyTypeObject *_Complex_Type()           { return &PyComplex_Type; }
PYCXX_EXPORT PyTypeObject *_Dict_Type()              { return &PyDict_Type; }
PYCXX_EXPORT PyTypeObject *_Float_Type()             { return &PyFloat_Type; }
PYCXX_EXPORT PyTypeObject *_Function_Type()          { return &PyFunction_Type; }
PYCXX_EXPORT PyTypeObject *_Bool_Type()              { return &PyBool_Type; }
PYCXX_EXPORT PyTypeObject *_List_Type()              { return &PyList_Type; }
PYCXX_EXPORT PyTypeObject *_Long_Type()              { return &PyLong_Type; }
PYCXX_EXPORT PyTypeObject *_Method_Type()            { return &PyMethod_Type; }
PYCXX_EXPORT PyTypeObject *_Module_Type()            { return &PyModule_Type; }
PYCXX_EXPORT PyTypeObject *_Range_Type()             { return &PyRange_Type; }
PYCXX_EXPORT PyTypeObject *_Slice_Type()             { return &PySlice_Type; }
PYCXX_EXPORT PyTypeObject *_TraceBack_Type()         { return &PyTraceBack_Type; }
PYCXX_EXPORT PyTypeObject *_Tuple_Type()             { return &PyTuple_Type; }
PYCXX_EXPORT PyTypeObject *_Type_Type()              { return &PyType_Type; }
PYCXX_EXPORT PyTypeObject *_Unicode_Type()           { return &PyUnicode_Type; }

PYCXX_EXPORT PyTypeObject *_Bytes_Type()             { return &PyBytes_Type; }

//
//    wrap flags
//
PYCXX_EXPORT int &_Py_DebugFlag()                    { return Py_DebugFlag; }
PYCXX_EXPORT int &_Py_InteractiveFlag()              { return Py_InteractiveFlag; }
PYCXX_EXPORT int &_Py_OptimizeFlag()                 { return Py_OptimizeFlag; }
PYCXX_EXPORT int &_Py_NoSiteFlag()                   { return Py_NoSiteFlag; }
PYCXX_EXPORT int &_Py_VerboseFlag()                  { return Py_VerboseFlag; }
PYCXX_EXPORT const char *__Py_PackageContext()       { return _Py_PackageContext; }

//
//    Needed to keep the abstactions for delayload interface
//
void _XINCREF( PyObject *op )
{
    Py_XINCREF( op );
}

void _XDECREF( PyObject *op )
{
    Py_XDECREF( op );
}

}
