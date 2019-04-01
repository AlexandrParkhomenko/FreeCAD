/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/
/** \file FCConfig.h
 *  \brief Include all needed defines and macros
 *  Here all defines and macro switching is done for FreeCAD.
 *  Every used library has its own section to define the configuration.
 *  This file keeps the makefiles and project files cleaner.
 */
//#OSDEPENDENT

#ifndef FC_CONFIG_H
#define FC_CONFIG_H


#ifndef FC_OS_LINUX
#define FC_OS_LINUX
#endif

#ifdef FC_OS_WIN32
#   define PATHSEP '\\'
#else
#   define PATHSEP '/'
#endif


//FIXME: Move to modules where OCC is needed
// Open CasCade

#ifdef FC_OS_LINUX
#   define LIN
#   define LININTEL
//#       define NO_CXX_EXCEPTION
#endif

#define CSFDB

/// enables the use of the OCC DocumentBrowser
#ifndef FC_OS_LINUX
#   define FC_USE_OCAFBROWSER
#endif


#ifdef FC_OCC_DEBUG
#   ifdef FC_DEBUG
#       define DEBUG 1
#   else
#       undef  DEBUG
#   ifndef NDEBUG
#       define NDEBUG
#   endif
#   endif
#endif


//**************************************************************************
// Qt

// Make sure to explicitly use the correct conversion
#define QT_NO_CAST_FROM_ASCII
#undef  QT3_SUPPORT
#define QT_NO_KEYWORDS

#ifndef QT_THREAD_SUPPORT
# define QT_THREAD_SUPPORT
#endif

#ifndef QT_ALTERNATE_QTSMANIP
# define QT_ALTERNATE_QTSMANIP
#endif



// stops inclusion of the QT 3 header through the SoQT header...
//#define __Qt3All__

//**************************************************************************
// Boost
#ifndef BOOST_SIGNALS_NO_DEPRECATION_WARNING
#define BOOST_SIGNALS_NO_DEPRECATION_WARNING
#endif

//**************************************************************************
// Exception handling

// Don't catch C++ exceptions in DEBUG!
#ifdef FC_DEBUG
# define DONT_CATCH_CXX_EXCEPTIONS 1
# define DBG_TRY
# define DBG_CATCH(X)
#else
/// used to switch a catch with the debug state
# define DBG_TRY try {
/// see docu DBGTRY
# define DBG_CATCH(X) } catch (...) { X }
#endif


#   ifndef BaseExport
#       define BaseExport //__declspec(dllexport)
#   endif
#   ifndef GuiExport
#       define GuiExport
#   endif
#   ifndef AppExport
#       define AppExport
#   endif
#   ifndef DataExport
#       define DataExport
#   endif


#endif //FC_CONFIG_H
