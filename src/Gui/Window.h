/***************************************************************************
 *   Copyright (c) 2004 Jürgen Riegel <juergen.riegel@web.de>              *
 *   FreeCAD LICENSE IS LGPL WITHOUT ANY WARRANTY                          *
 ***************************************************************************/


#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H


#include "stdexport.h"
#include "Base/Parameter.h"
#include "View.h"

namespace Gui {

/** Adapter class to the parameter of FreeCAD for all windows
 * Retrieve the parameter group of the specific window by the windowname.
 * @author Jürgen Riegel
 */
class GuiExport WindowParameter : public ParameterGrp::ObserverType
{
public:
  WindowParameter(const char *name);
  virtual ~WindowParameter();

  bool setGroupName( const char* name );
  void OnChange(Base::Subject<const char*> &rCaller, const char * sReason);

  /// get the parameters
  static ParameterGrp::handle getDefaultParameter(void);
  /// return the parameter group of this window
  ParameterGrp::handle getWindowParameter(void);

private:
  ParameterGrp::handle _handle;
};

} // namespace Gui

#endif // GUI_WINDOW_H
