#ifndef ZIPIOS_CONFIG_H
#define ZIPIOS_CONFIG_H

#include <FCConfig.h>

#define HAVE_STD_IOSTREAM 1
// gcc and others
#ifndef S_ISSOCK
#define S_ISSOCK(mode)	0
#endif
#include <stdint.h>

#endif // ZIPIOS_CONFIG_H

/** \file
    Configuration header file that allows compatibility with win32 compilers
*/

/*
  Zipios++ - a small C++ library that provides easy access to .zip files.
  Copyright (C) 2000  1. Thomas Søndergaard 2. Kevin Shea
  Written by Kevin Shea
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/
