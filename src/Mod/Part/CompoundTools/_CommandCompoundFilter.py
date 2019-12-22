################################################################################
#  Copyright (c) 2016 - Victor Titov (DeepSOIC) <vv.titov@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
__title__ = "CompoundTools._CommandCompoundFilter"
__author__ = "DeepSOIC, Bernd Hahnebach"
__doc__ = "Compound Filter: remove some children from a compound (features)."


import FreeCAD
if FreeCAD.GuiUp:
    import FreeCADGui
#    from PySide2 import QtGui
    from PySide2 import QtCore, QtWidgets


# translation-related code
#(see forum thread "A new Part tool is being born... JoinFeatures!"
#http://forum.freecadweb.org/viewtopic.php?f=22&t=11112&start=30#p90239 )
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
class _CommandCompoundFilter:
    "Command to create CompoundFilter feature"
    def GetResources(self):
        return {'Pixmap': ":/icons/Part_CompoundFilter.svg",
                'MenuText': QtCore.QT_TRANSLATE_NOOP("Part_CompoundFilter", "Compound Filter"),
                'Accel': "",
                'ToolTip': QtCore.QT_TRANSLATE_NOOP("Part_CompoundFilter", "Compound Filter: remove some childs from a compound")}

    def Activated(self):
        if len(FreeCADGui.Selection.getSelection()) == 1 or len(FreeCADGui.Selection.getSelection()) == 2:
            cmdCreateCompoundFilter(name="CompoundFilter")
        else:
            mb = QtWidgets.QMessageBox()
            mb.setIcon(mb.Icon.Warning)
            mb.setText(_translate("Part_CompoundFilter", "Select a shape that is a compound, first! Second selected item (optional) will be treated as a stencil.", None))
            mb.setWindowTitle(_translate("Part_CompoundFilter", "Bad selection", None))
            mb.exec_()

    def IsActive(self):
        if FreeCAD.ActiveDocument:
            return True
        else:
            return False


if FreeCAD.GuiUp:
    FreeCADGui.addCommand('Part_CompoundFilter', _CommandCompoundFilter())


# helper
def cmdCreateCompoundFilter(name):
    sel = FreeCADGui.Selection.getSelection()
    FreeCAD.ActiveDocument.openTransaction("Create CompoundFilter")
    FreeCADGui.addModule("CompoundTools.CompoundFilter")
    FreeCADGui.doCommand("f = CompoundTools.CompoundFilter.makeCompoundFilter(name = '" + name + "')")
    FreeCADGui.doCommand("f.Base = App.ActiveDocument." + sel[0].Name)
    if len(sel) == 2:
        FreeCADGui.doCommand("f.Stencil = App.ActiveDocument." + sel[1].Name)
        FreeCADGui.doCommand("f.Stencil.ViewObject.hide()")
        FreeCADGui.doCommand("f.FilterType = 'collision-pass'")
    else:
        FreeCADGui.doCommand("f.FilterType = 'window-volume'")

    try:
        FreeCADGui.doCommand("f.Proxy.execute(f)")
        FreeCADGui.doCommand("f.purgeTouched()")
    except Exception as err:
        mb = QtWidgets.QMessageBox()
        mb.setIcon(mb.Icon.Warning)
        mb.setText(_translate("Part_CompoundFilter", "Computing the result failed with an error: \n\n{err}\n\nClick 'Continue' to create the feature anyway, or 'Abort' to cancel.", None)
                   .format(err=err.message))
        mb.setWindowTitle(_translate("Part_CompoundFilter", "Bad selection", None))
        btnAbort = mb.addButton(QtWidgets.QMessageBox.StandardButton.Abort)
        btnOK = mb.addButton(_translate("Part_SplitFeatures", "Continue", None), QtWidgets.QMessageBox.ButtonRole.ActionRole)
        mb.setDefaultButton(btnOK)

        mb.exec_()

        if mb.clickedButton() is btnAbort:
            FreeCAD.ActiveDocument.abortTransaction()
            return

    FreeCADGui.doCommand("f.Base.ViewObject.hide()")
    FreeCADGui.doCommand("f = None")

    FreeCAD.ActiveDocument.commitTransaction()
