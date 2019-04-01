/***************************************************************************
 *   Copyright (c) Jürgen Riegel          (juergen.riegel@web.de) 2002     *
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


#ifndef APP_PRECOMPILED_H
#define APP_PRECOMPILED_H

#include <FCConfig.h>

// standard
#include <cstdio>
#include <cassert>
#include <ctime>
#include <csignal>
#include <stdexcept> //ApplicationPy.cpp

// Streams
#include <iostream>
#include <sstream>

// STL 
#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <stack>
#include <sstream>
#include <queue>
#include <bitset>
#include <exception>
#include <random>

// Boost
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <boost/regex.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/utility.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <boost/program_options.hpp>
//namespace po = boost::program_options;

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>


#endif // APP_PRECOMPILED_H
