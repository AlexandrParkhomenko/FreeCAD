# -*- coding: utf-8 -*-

# ***************************************************************************
# *   Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>               *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import FreeCADGui
import PathScripts.PathGui as PathGui
import PathScripts.PathOpGui as PathOpGui

from PySide2 import QtCore

__title__ = "Path Profile Operation Base UI"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Base page controller for profile operations."

def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)

FeatureSide       = 0x01
FeatureProcessing = 0x02

class TaskPanelOpPage(PathOpGui.TaskPanelPage):
    '''Base class for profile operation page controllers. Two sub features are
    support
        FeatureSide       ... Is the Side property exposed in the UI
        FeatureProcessing ... Are the processing check boxes supported by the operation
    '''

    def profileFeatures(self):
        '''profileFeatures() ... return which of the optional profile features are supported.
        Currently two features are supported:
            FeatureSide       ... Is the Side property exposed in the UI
            FeatureProcessing ... Are the processing check boxes supported by the operation
        Must be overwritten by subclasses.'''

    def getForm(self):
        '''getForm() ... returns UI customized according to profileFeatures()'''
        form = FreeCADGui.PySideUic.loadUi(":/panels/PageOpProfileFullEdit.ui")

        if not FeatureSide & self.profileFeatures():
            form.cutSide.hide()
            form.cutSideLabel.hide()

        if not FeatureProcessing & self.profileFeatures():
            form.processCircles.hide()
            form.processHoles.hide()
            form.processPerimeter.hide()

        return form

    def getFields(self, obj):
        '''getFields(obj) ... transfers values from UI to obj's proprties'''
        PathGui.updateInputField(obj, 'OffsetExtra', self.form.extraOffset)
        if obj.UseComp != self.form.useCompensation.isChecked():
            obj.UseComp = self.form.useCompensation.isChecked()
        if obj.UseStartPoint != self.form.useStartPoint.isChecked():
            obj.UseStartPoint = self.form.useStartPoint.isChecked()
        if obj.Direction != str(self.form.direction.currentText()):
            obj.Direction = str(self.form.direction.currentText())

        self.updateToolController(obj, self.form.toolController)

        if FeatureSide & self.profileFeatures():
            if obj.Side != str(self.form.cutSide.currentText()):
                obj.Side = str(self.form.cutSide.currentText())

        if FeatureProcessing & self.profileFeatures():
            if obj.processHoles != self.form.processHoles.isChecked():
                obj.processHoles = self.form.processHoles.isChecked()
            if obj.processPerimeter != self.form.processPerimeter.isChecked():
                obj.processPerimeter = self.form.processPerimeter.isChecked()
            if obj.processCircles != self.form.processCircles.isChecked():
                obj.processCircles = self.form.processCircles.isChecked()

    def setFields(self, obj):
        '''setFields(obj) ... transfers obj's property values to UI'''
        self.form.extraOffset.setText(FreeCAD.Units.Quantity(obj.OffsetExtra.Value, FreeCAD.Units.Length).UserString)
        self.form.useCompensation.setChecked(obj.UseComp)
        self.form.useStartPoint.setChecked(obj.UseStartPoint)

        self.selectInComboBox(obj.Direction, self.form.direction)
        self.setupToolController(obj, self.form.toolController)

        if FeatureSide & self.profileFeatures():
            self.selectInComboBox(obj.Side, self.form.cutSide)

        if FeatureProcessing & self.profileFeatures():
            self.form.processHoles.setChecked(obj.processHoles)
            self.form.processPerimeter.setChecked(obj.processPerimeter)
            self.form.processCircles.setChecked(obj.processCircles)

    def getSignalsForUpdate(self, obj):
        '''getSignalsForUpdate(obj) ... return list of signals for updating obj'''
        signals = []
        signals.append(self.form.direction.currentIndexChanged)
        signals.append(self.form.useCompensation.clicked)
        signals.append(self.form.useStartPoint.clicked)
        signals.append(self.form.extraOffset.editingFinished)

        if FeatureSide & self.profileFeatures():
            signals.append(self.form.cutSide.currentIndexChanged)

        if FeatureProcessing & self.profileFeatures():
            signals.append(self.form.processHoles.clicked)
            signals.append(self.form.processPerimeter.clicked)
            signals.append(self.form.processCircles.clicked)

        return signals
