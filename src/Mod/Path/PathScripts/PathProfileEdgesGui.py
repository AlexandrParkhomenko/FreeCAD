# -*- coding: utf-8 -*-

# ***************************************************************************
# *   Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>               *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import PathScripts.PathOpGui as PathOpGui
import PathScripts.PathProfileBaseGui as PathProfileBaseGui
import PathScripts.PathProfileEdges as PathProfileEdges

from PySide import QtCore

__title__ = "Path Profile based on edges Operation UI"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Profile based on edges operation page controller and command implementation."

class TaskPanelOpPage(PathProfileBaseGui.TaskPanelOpPage):
    '''Page controller for profile based on edges operation.'''

    def profileFeatures(self):
        '''profileFeatures() ... return FeatureSide
        See PathProfileBaseGui.py for details.'''
        return PathProfileBaseGui.FeatureSide

Command = PathOpGui.SetupOperation('Profile Edges',
        PathProfileEdges.Create,
        TaskPanelOpPage,
        'Path-Profile-Edges',
        QtCore.QT_TRANSLATE_NOOP("PathProfile", "Edge Profile"),
        QtCore.QT_TRANSLATE_NOOP("PathProfile", "Profile based on edges"),
        PathProfileEdges.SetupProperties)

FreeCAD.Console.PrintLog("Loading PathProfileEdgesGui... done\n")
