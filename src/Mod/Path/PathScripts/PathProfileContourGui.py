################################################################################
#  Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import FreeCAD
import PathScripts.PathOpGui as PathOpGui
import PathScripts.PathProfileBaseGui as PathProfileBaseGui
import PathScripts.PathProfileContour as PathProfileContour

from PySide2 import QtCore

__title__ = "Path Contour Operation UI"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Contour operation page controller and command implementation."

class TaskPanelOpPage(PathProfileBaseGui.TaskPanelOpPage):
    '''Page controller for the contour operation UI.'''

    def profileFeatures(self):
        '''profileFeatues() ... return 0 - profile doesn't support any of the optional UI features.'''
        return 0

Command = PathOpGui.SetupOperation('Contour',
        PathProfileContour.Create,
        TaskPanelOpPage,
        'Path-Contour',
        QtCore.QT_TRANSLATE_NOOP("PathProfileContour", "Contour"),
        QtCore.QT_TRANSLATE_NOOP("PathProfileContour", "Creates a Contour Path for the Base Object "),
        PathProfileContour.SetupProperties)

FreeCAD.Console.PrintLog("Loading PathProfileContourGui... done\n")
