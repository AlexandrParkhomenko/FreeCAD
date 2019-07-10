/***************************************************************************
 *   Copyright (c) wandererfan       <wandererfan (at) gmail.com> 2013     *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/
/***************************************************************************
 *  FreeType License (FTL) credit:                                         *
 *  Portions of this software are copyright (c) <1996-2011> The FreeType   *
 *  Project (www.freetype.org).  All rights reserved.                      *
 ***************************************************************************/


// Public header for FT2FC.cpp
#ifndef FT2FC_H
#define FT2FC_H
// public functions
PyObject* FT2FC(const Py_UNICODE *unichars,
                const size_t length,
                const char *FontPath,
                const char *FontName,
                const double stringheight,
                const double tracking);

PyObject* FT2FC(const Py_UNICODE *unichars,
                const size_t length,
                const char *FontSpec,
                const double stringheight,
                const double tracking);

#endif // FT2FC_H

