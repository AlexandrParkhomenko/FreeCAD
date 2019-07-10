# -*- coding: utf-8 -*-

# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2014 Yorik van Havre <yorik@uncreated.net>              *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import FreeCADGui
from PySide import QtCore, QtGui

"""Path Copy object and FreeCAD command"""

# Qt tanslation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)


class ObjectPathCopy:

    def __init__(self, obj):
        obj.addProperty("App::PropertyLink", "Base", "Path", QtCore.QT_TRANSLATE_NOOP("App::Property", "The path to be copied"))
        obj.addProperty("App::PropertyLink", "ToolController", "Path", QtCore.QT_TRANSLATE_NOOP("App::Property", "The tool controller that will be used to calculate the path"))
        obj.Proxy = self

    def __getstate__(self):
        return None

    def __setstate__(self, state):
        return None

    def execute(self, obj):
        if obj.Base:
            if hasattr(obj.Base, 'ToolController'):
                obj.ToolController = obj.Base.ToolController
            if obj.Base.Path:
                obj.Path = obj.Base.Path.copy()


class ViewProviderPathCopy:

    def __init__(self, vobj):
        vobj.Proxy = self

    def attach(self, vobj):
        self.Object = vobj.Object
        return

    def getIcon(self):
        return ":/icons/Path-Copy.svg"

    def __getstate__(self):
        return None

    def __setstate__(self, state):
        return None


class CommandPathCopy:

    def GetResources(self):
        return {'Pixmap': 'Path-Copy',
                'MenuText': QtCore.QT_TRANSLATE_NOOP("Path_Copy", "Copy"),
                'ToolTip': QtCore.QT_TRANSLATE_NOOP("Path_Copy", "Creates a linked copy of another path")}

    def IsActive(self):
        if FreeCAD.ActiveDocument is not None:
            for o in FreeCAD.ActiveDocument.Objects:
                if o.Name[:3] == "Job":
                        return True
        return False

    def Activated(self):

        FreeCAD.ActiveDocument.openTransaction(
            translate("Path_Copy", "Create Copy"))
        FreeCADGui.addModule("PathScripts.PathCopy")

        consolecode = '''
import Path
import PathScripts
from PathScripts import PathCopy
selGood = True
# check that the selection contains exactly what we want
selection = FreeCADGui.Selection.getSelection()
proj = selection[0].InList[0] #get the group that the selectied object is inside

if len(selection) != 1:
    FreeCAD.Console.PrintError(translate("Path_Copy", "Please select one path object")+"\n")
    selGood = False

if not selection[0].isDerivedFrom("Path::Feature"):
    FreeCAD.Console.PrintError(translate("Path_Copy", "The selected object is not a path")+"\n")
    selGood = False

if selGood:
    obj = FreeCAD.ActiveDocument.addObject("Path::FeaturePython", str(selection[0].Name)+'_Copy')
    PathScripts.PathCopy.ObjectPathCopy(obj)
    PathScripts.PathCopy.ViewProviderPathCopy(obj.ViewObject)
    obj.Base = FreeCAD.ActiveDocument.getObject(selection[0].Name)
    if hasattr(obj.Base, 'ToolController'):
        obj.ToolController = obj.Base.ToolController

g = proj.Group
g.append(obj)
proj.Group = g

FreeCAD.ActiveDocument.recompute()

'''

        FreeCADGui.doCommand(consolecode)
        FreeCAD.ActiveDocument.commitTransaction()
        FreeCAD.ActiveDocument.recompute()


if FreeCAD.GuiUp:
    # register the FreeCAD command
    FreeCADGui.addCommand('Path_Copy', CommandPathCopy())

FreeCAD.Console.PrintLog("Loading PathCopy... done\n")
