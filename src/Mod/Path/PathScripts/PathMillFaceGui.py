# ***************************************************************************
# *   Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>               *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import PathScripts.PathMillFace as PathMillFace
import PathScripts.PathOpGui as PathOpGui
import PathScripts.PathPocketBaseGui as PathPocketBaseGui

from PySide2 import QtCore

__title__ = "Path Face Mill Operation UI"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Face Mill operation page controller and command implementation."

class TaskPanelOpPage(PathPocketBaseGui.TaskPanelOpPage):
    '''Page controller class for the face milling operation.'''

    def pocketFeatures(self):
        '''pocketFeatures() ... return FeatureFacing (see PathPocketBaseGui)'''
        return PathPocketBaseGui.FeatureFacing

Command = PathOpGui.SetupOperation('MillFace',
        PathMillFace.Create,
        TaskPanelOpPage,
        'Path-Face',
        QtCore.QT_TRANSLATE_NOOP("PathFace", "Face"),
        QtCore.QT_TRANSLATE_NOOP("PathFace", "Create a Facing Operation from a model or face"),
        PathMillFace.SetupProperties)

FreeCAD.Console.PrintLog("Loading PathMillFaceGui... done\n")

