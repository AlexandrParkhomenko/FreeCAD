# -*- coding: utf-8 -*-
# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2015 Yorik van Havre <yorik@uncreated.net>              *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import FreeCADGui
import PathScripts
from PySide import QtCore

"""Path SimpleCopy command"""


# Qt tanslation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)


class CommandPathSimpleCopy:

    def GetResources(self):
        return {'Pixmap': 'Path-SimpleCopy',
                'MenuText': QtCore.QT_TRANSLATE_NOOP("Path_SimpleCopy", "Simple Copy"),
                'ToolTip': QtCore.QT_TRANSLATE_NOOP("Path_SimpleCopy", "Creates a non-parametric copy of another path")}

    def IsActive(self):
        if bool(FreeCADGui.Selection.getSelection()) is False:
            return False
        try:
            obj = FreeCADGui.Selection.getSelectionEx()[0].Object
            return isinstance(obj.Proxy, PathScripts.PathOp.ObjectOp)
        except:
            return False

    def Activated(self):
        # check that the selection contains exactly what we want
        selection = FreeCADGui.Selection.getSelection()
        if len(selection) != 1:
            FreeCAD.Console.PrintError(
                translate("Path_SimpleCopy", "Please select exactly one path object")+"\n")
            return
        if not(selection[0].isDerivedFrom("Path::Feature")):
            FreeCAD.Console.PrintError(
                translate("Path_SimpleCopy", "Please select exactly one path object")+"\n")
            return

        FreeCAD.ActiveDocument.openTransaction(
            translate("Path_SimpleCopy", "Simple Copy"))
        FreeCADGui.doCommand("srcpath = FreeCADGui.Selection.getSelectionEx()[0].Object.Path\n")

        FreeCADGui.addModule("PathScripts.PathUtils")
        FreeCADGui.addModule("PathScripts.PathCustom")
        FreeCADGui.doCommand('obj = FreeCAD.ActiveDocument.addObject("Path::FeaturePython","' + selection[0].Name + '_SimpleCopy")')
        FreeCADGui.doCommand('PathScripts.PathCustom.ObjectCustom(obj)')
        FreeCADGui.doCommand('obj.ViewObject.Proxy = 0')
        FreeCADGui.doCommand('obj.Gcode = [c.toGCode() for c in srcpath.Commands]')
        FreeCADGui.doCommand('PathScripts.PathUtils.addToJob(obj)')
        FreeCAD.ActiveDocument.commitTransaction()
        FreeCAD.ActiveDocument.recompute()


if FreeCAD.GuiUp:
    # register the FreeCAD command
    FreeCADGui.addCommand('Path_SimpleCopy', CommandPathSimpleCopy())
