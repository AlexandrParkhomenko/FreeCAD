################################################################################
#  Copyright (c) 2018 sliptonic <shopinthewoods@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import FreeCAD
import FreeCADGui
import PathScripts.PathDeburr as PathDeburr
import PathScripts.PathGui as PathGui
import PathScripts.PathLog as PathLog
import PathScripts.PathOpGui as PathOpGui

from PySide2 import QtCore, QtGui, QtWidgets

__title__ = "Path Deburr Operation UI"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Deburr operation page controller and command implementation."

LOGLEVEL = False

if LOGLEVEL:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())

def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)


class TaskPanelOpPage(PathOpGui.TaskPanelPage):
    '''Page controller class for the Deburr operation.'''

    def getForm(self):
        return FreeCADGui.PySideUic.loadUi(":/panels/PageOpDeburrEdit.ui")

    def initPage(self, obj):
        self.opImagePath = "{}Mod/Path/Images/Ops/{}".format(FreeCAD.getHomePath(), 'chamfer.svg') # pylint: disable=attribute-defined-outside-init
        self.opImage = QtGui.QPixmap(self.opImagePath) # pylint: disable=attribute-defined-outside-init
        self.form.opImage.setPixmap(self.opImage)
        iconMiter = QtGui.QDialog(':/icons/edge-join-miter-not.svg')
        iconMiter.addFile(':/icons/edge-join-miter.svg', state=QtGui.QDialog.On)
        iconRound = QtGui.QDialog(':/icons/edge-join-round-not.svg')
        iconRound.addFile(':/icons/edge-join-round.svg', state=QtGui.QDialog.On)
        self.form.joinMiter.setIcon(iconMiter)
        self.form.joinRound.setIcon(iconRound)

    def getFields(self, obj):
        PathGui.updateInputField(obj, 'Width', self.form.value_W)
        PathGui.updateInputField(obj, 'ExtraDepth', self.form.value_h)
        if self.form.joinRound.isChecked():
            obj.Join = 'Round'
        elif self.form.joinMiter.isChecked():
            obj.Join = 'Miter'

        self.updateToolController(obj, self.form.toolController)

    def setFields(self, obj):
        self.form.value_W.setText(FreeCAD.Units.Quantity(obj.Width.Value, FreeCAD.Units.Length).UserString)
        self.form.value_h.setText(FreeCAD.Units.Quantity(obj.ExtraDepth.Value, FreeCAD.Units.Length).UserString)
        self.setupToolController(obj, self.form.toolController)
        self.form.joinRound.setChecked('Round' == obj.Join)
        self.form.joinMiter.setChecked('Miter' == obj.Join)
        self.form.joinFrame.hide()

    def updateWidth(self):
        PathGui.updateInputField(self.obj, 'Width', self.form.value_W)

    def updateExtraDepth(self):
        PathGui.updateInputField(self.obj, 'ExtraDepth', self.form.value_h)

    def getSignalsForUpdate(self, obj):
        signals = []
        signals.append(self.form.joinMiter.clicked)
        signals.append(self.form.joinRound.clicked)
        return signals

    def registerSignalHandlers(self, obj):
        self.form.value_W.editingFinished.connect(self.updateWidth)
        self.form.value_h.editingFinished.connect(self.updateExtraDepth)


Command = PathOpGui.SetupOperation('Deburr',
        PathDeburr.Create,
        TaskPanelOpPage,
        'Path-Deburr',
        QtCore.QT_TRANSLATE_NOOP("PathDeburr", "Deburr"),
        QtCore.QT_TRANSLATE_NOOP("PathDeburr", "Creates a Deburr Path along Edges or around Faces"),
        PathDeburr.SetupProperties)

FreeCAD.Console.PrintLog("Loading PathDeburrGui... done\n")

