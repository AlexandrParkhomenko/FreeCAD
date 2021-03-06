################################################################################
#  Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import FreeCAD
import FreeCADGui
import PathScripts.PathCircularHoleBaseGui as PathCircularHoleBaseGui
import PathScripts.PathHelix as PathHelix
import PathScripts.PathLog as PathLog
import PathScripts.PathOpGui as PathOpGui

from PySide2 import QtCore

__doc__ = "Helix operation page controller and command implementation."

LOGLEVEL = False

if LOGLEVEL:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.NOTICE, PathLog.thisModule())


class TaskPanelOpPage(PathCircularHoleBaseGui.TaskPanelOpPage):
    '''Page controller class for Helix operations.'''

    def getForm(self):
        '''getForm() ... return UI'''
        return FreeCADGui.PySideUic.loadUi(":/panels/PageOpHelixEdit.ui")

    def getFields(self, obj):
        '''getFields(obj) ... transfers values from UI to obj's proprties'''
        PathLog.track()
        if obj.Direction != str(self.form.direction.currentText()):
            obj.Direction = str(self.form.direction.currentText())
        if obj.StartSide != str(self.form.startSide.currentText()):
            obj.StartSide = str(self.form.startSide.currentText())
        if obj.StepOver != self.form.stepOverPercent.value():
            obj.StepOver = self.form.stepOverPercent.value()

        self.updateToolController(obj, self.form.toolController)

    def setFields(self, obj):
        '''setFields(obj) ... transfers obj's property values to UI'''
        PathLog.track()

        self.form.stepOverPercent.setValue(obj.StepOver)
        self.selectInComboBox(obj.Direction, self.form.direction)
        self.selectInComboBox(obj.StartSide, self.form.startSide)

        self.setupToolController(obj, self.form.toolController)

    def getSignalsForUpdate(self, obj):
        '''getSignalsForUpdate(obj) ... return list of signals for updating obj'''
        signals = []

        signals.append(self.form.stepOverPercent.editingFinished)
        signals.append(self.form.direction.currentIndexChanged)
        signals.append(self.form.startSide.currentIndexChanged)
        signals.append(self.form.toolController.currentIndexChanged)

        return signals

Command = PathOpGui.SetupOperation('Helix',
        PathHelix.Create,
        TaskPanelOpPage,
        'Path-Helix',
        QtCore.QT_TRANSLATE_NOOP("PathHelix", "Helix"),
        QtCore.QT_TRANSLATE_NOOP("PathHelix", "Creates a Path Helix object from a features of a base object"),
        PathHelix.SetupProperties)

FreeCAD.Console.PrintLog("Loading PathHelixGui... done\n")
