################################################################################
#  Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import FreeCAD
import FreeCADGui
import PathScripts.PathSurface as PathSurface
import PathScripts.PathGui as PathGui
import PathScripts.PathOpGui as PathOpGui

from PySide2 import QtCore

__title__ = "Path Surface Operation UI"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Surface operation page controller and command implementation."


class TaskPanelOpPage(PathOpGui.TaskPanelPage):
    '''Page controller class for the Surface operation.'''

    def getForm(self):
        '''getForm() ... returns UI'''
        return FreeCADGui.PySideUic.loadUi(":/panels/PageOpSurfaceEdit.ui")

    def getFields(self, obj):
        '''getFields(obj) ... transfers values from UI to obj's proprties'''
        PathGui.updateInputField(obj, 'DepthOffset', self.form.depthOffset)
        PathGui.updateInputField(obj, 'SampleInterval', self.form.sampleInterval)

        if obj.StepOver != self.form.stepOver.value():
            obj.StepOver = self.form.stepOver.value()

        if obj.Algorithm != str(self.form.algorithmSelect.currentText()):
            obj.Algorithm = str(self.form.algorithmSelect.currentText())

        if obj.BoundBox != str(self.form.boundBoxSelect.currentText()):
            obj.BoundBox = str(self.form.boundBoxSelect.currentText())

        if obj.DropCutterDir != str(self.form.dropCutterDirSelect.currentText()):
            obj.DropCutterDir = str(self.form.dropCutterDirSelect.currentText())

        obj.DropCutterExtraOffset.x = FreeCAD.Units.Quantity(self.form.boundBoxExtraOffsetX.text()).Value
        obj.DropCutterExtraOffset.y = FreeCAD.Units.Quantity(self.form.boundBoxExtraOffsetY.text()).Value

        if obj.Optimize != self.form.optimizeEnabled.isChecked():
            obj.Optimize = self.form.optimizeEnabled.isChecked()

        self.updateToolController(obj, self.form.toolController)

    def setFields(self, obj):
        '''setFields(obj) ... transfers obj's property values to UI'''
        self.selectInComboBox(obj.Algorithm, self.form.algorithmSelect)
        self.selectInComboBox(obj.BoundBox, self.form.boundBoxSelect)
        self.selectInComboBox(obj.DropCutterDir, self.form.dropCutterDirSelect)

        self.form.boundBoxExtraOffsetX.setText(str(obj.DropCutterExtraOffset.x))
        self.form.boundBoxExtraOffsetY.setText(str(obj.DropCutterExtraOffset.y))
        self.form.depthOffset.setText(FreeCAD.Units.Quantity(obj.DepthOffset.Value, FreeCAD.Units.Length).UserString)
        self.form.sampleInterval.setText(str(obj.SampleInterval))
        self.form.stepOver.setValue(obj.StepOver)

        if obj.Optimize:
            self.form.optimizeEnabled.setCheckState(QtCore.Qt.Checked)
        else:
            self.form.optimizeEnabled.setCheckState(QtCore.Qt.Unchecked)

        self.setupToolController(obj, self.form.toolController)

    def getSignalsForUpdate(self, obj):
        '''getSignalsForUpdate(obj) ... return list of signals for updating obj'''
        signals = []
        signals.append(self.form.toolController.currentIndexChanged)
        signals.append(self.form.algorithmSelect.currentIndexChanged)
        signals.append(self.form.boundBoxSelect.currentIndexChanged)
        signals.append(self.form.dropCutterDirSelect.currentIndexChanged)
        signals.append(self.form.boundBoxExtraOffsetX.editingFinished)
        signals.append(self.form.boundBoxExtraOffsetY.editingFinished)
        signals.append(self.form.sampleInterval.editingFinished)
        signals.append(self.form.stepOver.editingFinished)
        signals.append(self.form.depthOffset.editingFinished)
        signals.append(self.form.optimizeEnabled.stateChanged)

        return signals

    def updateVisibility(self):
        if self.form.algorithmSelect.currentText() == "OCL Dropcutter":
            self.form.boundBoxExtraOffsetX.setEnabled(True)
            self.form.boundBoxExtraOffsetY.setEnabled(True)
            self.form.boundBoxSelect.setEnabled(True)
            self.form.dropCutterDirSelect.setEnabled(True)
            self.form.stepOver.setEnabled(True)
        else:
            self.form.boundBoxExtraOffsetX.setEnabled(False)
            self.form.boundBoxExtraOffsetY.setEnabled(False)
            self.form.boundBoxSelect.setEnabled(False)
            self.form.dropCutterDirSelect.setEnabled(False)
            self.form.stepOver.setEnabled(False)

    def registerSignalHandlers(self, obj):
        self.form.algorithmSelect.currentIndexChanged.connect(self.updateVisibility)


Command = PathOpGui.SetupOperation('Surface',
        PathSurface.Create,
        TaskPanelOpPage,
        'Path-3DSurface',
        QtCore.QT_TRANSLATE_NOOP("Surface", "3D Surface"),
        QtCore.QT_TRANSLATE_NOOP("Surface", "Create a 3D Surface Operation from a model"),
        PathSurface.SetupProperties)

FreeCAD.Console.PrintLog("Loading PathSurfaceGui... done\n")
