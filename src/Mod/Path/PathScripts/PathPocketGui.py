# -*- coding: utf-8 -*-

# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>               *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import PathScripts.PathOpGui as PathOpGui
import PathScripts.PathPocket as PathPocket
import PathScripts.PathPocketBaseGui as PathPocketBaseGui

from PySide import QtCore

__title__ = "Path Pocket Operation UI"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Pocket operation page controller and command implementation."

class TaskPanelOpPage(PathPocketBaseGui.TaskPanelOpPage):
    '''Page controller class for Pocket operation'''

    def pocketFeatures(self):
        '''pocketFeatures() ... return FeaturePocket (see PathPocketBaseGui)'''
        return PathPocketBaseGui.FeaturePocket

Command = PathOpGui.SetupOperation('Pocket 3D',
        PathPocket.Create,
        TaskPanelOpPage,
        'Path-3DPocket',
        QtCore.QT_TRANSLATE_NOOP("PathPocket", "3D Pocket"),
        QtCore.QT_TRANSLATE_NOOP("PathPocket", "Creates a Path 3D Pocket object from a face or faces"),
        PathPocket.SetupProperties)

FreeCAD.Console.PrintLog("Loading PathPocketGui... done\n")
