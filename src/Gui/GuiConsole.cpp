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
//#OSDEPENDENT


# include "stdio.h"
# include "fcntl.h"
# include <iostream>

#include "GuiConsole.h"

using namespace Gui;

// safely ignore GUIConsole::s_nMaxLines and  GUIConsole::s_nRefCount
GUIConsole::GUIConsole (void) {}
GUIConsole::~GUIConsole (void) {}
void GUIConsole::Message(const char *sMsg) { std::cout<<sMsg; }
void GUIConsole::Warning(const char *sWarn){ std::cerr<<"Warning: "<<sWarn; }
void GUIConsole::Error  (const char *sErr) { std::cerr<<"Error: "<<sErr;}
void GUIConsole::Log  (const char *sLog)   { std::clog<<sLog;}

