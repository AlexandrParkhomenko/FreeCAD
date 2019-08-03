#***************************************************************************
#*                                                                         *
#*   Copyright (c) 2014 - Juergen Riegel <FreeCAD@juergen-riegel.net>      *  
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
#***************************************************************************

import FreeCAD, Sketcher

if FreeCAD.GuiUp:
    import FreeCADGui,SketcherGui,os
    from PySide2 import QtCore, QtGui
    from PySide2.QtCore import Qt
    from PySide2.QtGui import QApplication, QCursor
    from FreeCADGui import PySideUic as uic

    #s=os.path.dirname(__file__)
    #s=os.path.join(s,"ProfileLib")
    #FreeCADGui.addIconPath(s)

__title__="Sketcher profile lib handling"
__author__ = "Juergen Riegel"


def isProfileActive():
    return not FreeCAD.ActiveDocument is None

def getSketch():
    edit = FreeCADGui.ActiveDocument.getInEdit()
    if edit and edit.isDerivedFrom('SketcherGui::ViewProviderSketch'):
        return edit.Object
    #act = FreeCAD.ActiveDocument.ActiveObject
    #if act and act.isDerivedFrom('Sketcher::SketchObject'):
    #    return act
    return None

class _CommandProfileHexagon1:
    "The basis hexagon profile command definition"
    def GetResources(self):
        return {'Pixmap'  : 'Sketcher_ProfilesHexagon1',
                'MenuText': QtCore.QT_TRANSLATE_NOOP("Sketcher_ProfilesHexagon1","Creates a hexagonal profile"),
                'Accel': "",
                'CmdType': "ForEdit",
                'ToolTip': QtCore.QT_TRANSLATE_NOOP("Sketcher_ProfilesHexagon1","Creates a hexagonal profile in the sketch")}
        
    def Activated(self):
        FreeCAD.ActiveDocument.openTransaction("Create hexagon profile")
        FreeCADGui.addModule("ProfileLib.Hexagon")
        sketch = getSketch()
        if not sketch is None:
            FreeCADGui.doCommand("ProfileLib.Hexagon.makeHexagonSimple('%s')" % (sketch.Name))
        else:
            FreeCADGui.doCommand("ProfileLib.Hexagon.makeHexagonSimple()")
        FreeCAD.ActiveDocument.recompute()

    def IsActive(self):
        return isProfileActive()


FreeCADGui.addCommand('Sketcher_ProfilesHexagon1',_CommandProfileHexagon1())
