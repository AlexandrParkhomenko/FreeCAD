/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
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

