/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_GUICONSOLE_H
#define GUI_GUICONSOLE_H


#include "stdexport.h"
#include "Base/Console.h"

namespace Gui {

/** The console window class
 *  This class opens a console window when instantiated 
 *  and redirects the stdio streams to it as long it exists. 
 *  This is for Windows only!
 *  After instantiation it automatically registers itself at
 *  the FCConsole class and gets all the FCConsoleObserver
 *  messages. The class must not used directly! Only the 
 *  FCConsole class is allowed!
 *  @see FCConsole
 *  \author Jürgen Riegel
 */
class GuiExport GUIConsole :public Base::ConsoleObserver
{
public:
  /// Constructor
  GUIConsole(void);
  /// Destructor
  virtual ~GUIConsole(void);
  //@{
    /** Observer implementation */
  virtual void Warning(const char *sWarn);
  virtual void Message(const char *sMsg);
  virtual void Error  (const char *sErr);
  virtual void Log    (const char *sErr);
  const char* Name(void){return "GUIConsole";}
  //@}

protected:
  static const unsigned int s_nMaxLines;
  static unsigned int       s_nRefCount;
};

} // namespace Gui

#endif // GUI_GUICONSOLE_H

