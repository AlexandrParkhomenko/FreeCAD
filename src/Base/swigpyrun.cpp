/***************************************************************************
 *   Copyright (c) 2008 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#include "PyExport.h"
#include "Exception.h"
#if (defined(HAVE_SWIG) && (HAVE_SWIG == 1))
#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdeprecated-register"
#elif defined (__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"
# if __GNUC__ >= 8
# pragma GCC diagnostic ignored "-Wcast-function-type"
# endif
#endif
namespace Swig_python {
#define SWIG_PYTHON_NO_BUILD_NONE
#include <swigpyrun.h>
#include "swigpyrun.inl"
}
#if defined(__clang__)
# pragma clang diagnostic pop
#elif defined (__GNUC__)
# pragma GCC diagnostic pop
#endif
#endif // HAVE_SWIG

