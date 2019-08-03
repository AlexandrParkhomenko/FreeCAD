# -*- coding: utf-8 -*-
# ***************************************************************************
# *   Copyright (c) 2015 Dan Falck <ddfalck@gmail.com>                      *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************
''' Used for CNC machine Stops for Path module. Create an Optional or Mandatory Stop.'''

import FreeCAD
import FreeCADGui
import Path
from PySide2 import QtCore

# Qt translation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)

class Stop:
    def __init__(self,obj):
        obj.addProperty("App::PropertyEnumeration", "Stop", "Path", QtCore.QT_TRANSLATE_NOOP("App::Property","Add Optional or Mandatory Stop to the program"))
        obj.Stop=['Optional', 'Mandatory']
        obj.Proxy = self
        mode = 2
        obj.setEditorMode('Placement', mode)

    def __getstate__(self):
        return None

    def __setstate__(self, state):
        return None

    def onChanged(self, obj, prop):
        pass

    def execute(self, obj):
        if obj.Stop == 'Optional':
            word = 'M1'
        else:
            word = 'M0'

        output = ""
        output = word + '\n'
        path = Path.Path(output)
        obj.Path = path


class _ViewProviderStop:

    def __init__(self, vobj):  # mandatory
        vobj.Proxy = self
        mode = 2
        vobj.setEditorMode('LineWidth', mode)
        vobj.setEditorMode('MarkerColor', mode)
        vobj.setEditorMode('NormalColor', mode)
        vobj.setEditorMode('DisplayMode', mode)
        vobj.setEditorMode('BoundingBox', mode)
        vobj.setEditorMode('Selectable', mode)
        vobj.setEditorMode('ShapeColor', mode)
        vobj.setEditorMode('Transparency', mode)
        vobj.setEditorMode('Visibility', mode)

    def __getstate__(self):  # mandatory
        return None

    def __setstate__(self, state):  # mandatory
        return None

    def getIcon(self):  # optional
        return ":/icons/Path-Stop.svg"

    def onChanged(self, vobj, prop):  # optional
        # pylint: disable=unused-argument
        mode = 2
        vobj.setEditorMode('LineWidth', mode)
        vobj.setEditorMode('MarkerColor', mode)
        vobj.setEditorMode('NormalColor', mode)
        vobj.setEditorMode('DisplayMode', mode)
        vobj.setEditorMode('BoundingBox', mode)
        vobj.setEditorMode('Selectable', mode)
        vobj.setEditorMode('ShapeColor', mode)
        vobj.setEditorMode('Transparency', mode)
        vobj.setEditorMode('Visibility', mode)


class CommandPathStop:

    def GetResources(self):
        return {'Pixmap': 'Path-Stop',
                'MenuText': QtCore.QT_TRANSLATE_NOOP("Path_Stop", "Stop"),
                'ToolTip': QtCore.QT_TRANSLATE_NOOP("Path_Stop", "Add Optional or Mandatory Stop to the program")}

    def IsActive(self):
        if FreeCAD.ActiveDocument is not None:
            for o in FreeCAD.ActiveDocument.Objects:
                if o.Name[:3] == "Job":
                    return True
        return False

    def Activated(self):
        FreeCAD.ActiveDocument.openTransaction(
            translate("Path_Stop", "Add Optional or Mandatory Stop to the program"))
        FreeCADGui.addModule("PathScripts.PathStop")
        snippet = '''
import Path
import PathScripts
from PathScripts import PathUtils
prjexists = False
obj = FreeCAD.ActiveDocument.addObject("Path::FeaturePython","Stop")
PathScripts.PathStop.Stop(obj)

PathScripts.PathStop._ViewProviderStop(obj.ViewObject)
PathUtils.addToJob(obj)
'''
        FreeCADGui.doCommand(snippet)
        FreeCAD.ActiveDocument.commitTransaction()
        FreeCAD.ActiveDocument.recompute()

if FreeCAD.GuiUp:
    # register the FreeCAD command
    FreeCADGui.addCommand('Path_Stop', CommandPathStop())


FreeCAD.Console.PrintLog("Loading PathStop... done\n")
