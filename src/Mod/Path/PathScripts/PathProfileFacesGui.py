# -*- coding: utf-8 -*-

# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>               *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import PathScripts.PathOpGui as PathOpGui
import PathScripts.PathProfileBaseGui as PathProfileBaseGui
import PathScripts.PathProfileFaces as PathProfileFaces

from PySide import QtCore

__title__ = "Path Profile based on faces Operation UI"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Profile based on faces operation page controller and command implementation."

class TaskPanelOpPage(PathProfileBaseGui.TaskPanelOpPage):
    '''Page controller for profile based on faces operation.'''

    def profileFeatures(self):
        '''profileFeatures() ... return FeatureSide | FeatureProcessing.
        See PathProfileBaseGui.py for details.'''
        return PathProfileBaseGui.FeatureSide | PathProfileBaseGui.FeatureProcessing

Command = PathOpGui.SetupOperation('Profile Faces',
        PathProfileFaces.Create,
        TaskPanelOpPage,
        'Path-Profile-Face',
        QtCore.QT_TRANSLATE_NOOP("PathProfile", "Face Profile"),
        QtCore.QT_TRANSLATE_NOOP("PathProfile", "Profile based on face or faces"),
        PathProfileFaces.SetupProperties)

FreeCAD.Console.PrintLog("Loading PathProfileFacesGui... done\n")
