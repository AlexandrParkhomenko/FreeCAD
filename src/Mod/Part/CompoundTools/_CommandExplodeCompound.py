# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2016 - Victor Titov (DeepSOIC) <vv.titov@gmail.com>     *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

__title__ = "CompoundTools._CommandExplodeCompound"
__author__ = "DeepSOIC"
__doc__ = "ExplodeCompound: create a bunch of CompoundFilter objects to split a compound into pieces."

from .Explode import explodeCompound

import FreeCAD
if FreeCAD.GuiUp:
    import FreeCADGui
    from PySide2 import QtWidgets #  QtGui,
    from PySide2 import QtCore


# translation-related code
    try:
        _fromUtf8 = QtCore.QString.fromUtf8
    except Exception:
        def _fromUtf8(s):
            return s
    try:
        _encoding = QtWidgets.QApplication.UnicodeUTF8
        def _translate(context, text, disambig):
            return QtWidgets.QApplication.translate(context, text, disambig, _encoding)
    except AttributeError:
        def _translate(context, text, disambig):
            return QtWidgets.QApplication.translate(context, text, disambig)


# command class
class _CommandExplodeCompound:
    "Command to explode a compound"
    def GetResources(self):
        return {'Pixmap': ":/icons/Part_ExplodeCompound.svg",
                'MenuText': QtCore.QT_TRANSLATE_NOOP("Part_ExplodeCompound", "Explode compound"),
                'Accel': "",
                'ToolTip': QtCore.QT_TRANSLATE_NOOP("Part_ExplodeCompound", "Explode compound: split up a list of shapes into separate objects")}

    def Activated(self):
        if len(FreeCADGui.Selection.getSelection()) == 1:
            cmdExplode()
        else:
            mb = QtWidgets.QMessageBox()
            mb.setIcon(mb.Icon.Warning)
            mb.setText(_translate("Part_ExplodeCompound", "Select a shape that is a compound, first!", None))
            mb.setWindowTitle(_translate("Part_ExplodeCompound", "Bad selection", None))
            mb.exec_()

    def IsActive(self):
        if FreeCAD.ActiveDocument:
            return True
        else:
            return False


if FreeCAD.GuiUp:
    FreeCADGui.addCommand('Part_ExplodeCompound', _CommandExplodeCompound())




def cmdExplode():
    FreeCAD.ActiveDocument.openTransaction("Explode")
    try:
        sel = FreeCADGui.Selection.getSelectionEx()
        if len(sel) != 1:
            raise ValueError("Bad selection","More than one object selected. You have selected {num} objects.".format(num= len(sel)))
        obj = sel[0].Object
        FreeCADGui.addModule("CompoundTools.Explode")
        FreeCADGui.doCommand("input_obj = App.ActiveDocument."+obj.Name)
        FreeCADGui.doCommand("CompoundTools.Explode.explodeCompound(input_obj)")
        FreeCADGui.doCommand("input_obj.ViewObject.hide()")
    except Exception:
        FreeCAD.ActiveDocument.abortTransaction()
        raise
        
    FreeCAD.ActiveDocument.commitTransaction()
    FreeCADGui.doCommand("App.ActiveDocument.recompute()")
    
