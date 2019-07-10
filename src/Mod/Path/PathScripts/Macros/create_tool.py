#***************************************************************************
#*                                                                         *
#*   Copyright (c) 2014 Daniel Falck  <ddfalck@gmail.com>                  *  
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
#***************************************************************************

'''
This macro is used in conjunction with the toolpathparams script to create an object that represents a tool for use in a CNC program. Create a group and then select it- then run the macro.
You will have to edit the parameters inside the Data tab of the tool object.
'''

import FreeCAD
import FreeCADGui
import PathScripts
import toolpathparams as tp


tl = FreeCAD.ActiveDocument.addObject("App::FeaturePython","Tools")

tp.ToolParams(tl)
tp.ViewProviderToolParams(tl.ViewObject)

sel = FreeCADGui.Selection.getSelection()
g = sel[0]
g.addObject(tl)
App.activeDocument().recompute()
