# -*- coding: utf-8 -*-

# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2018 sliptonic <shopinthewoods@gmail.com>               *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import FreeCADGui
import PathScripts.PathJob as PathJob

def selection():
    '''isActive() ... return True if a dressup command is possible.'''
    if FreeCAD.ActiveDocument:
        sel = FreeCADGui.Selection.getSelectionEx()
        if len(sel) == 1 and sel[0].Object.isDerivedFrom("Path::Feature") and PathJob.Instances():
            return sel[0].Object
    return None

def hasEntryMethod(path):
    '''hasEntryDressup(path) ... returns true if the given object already has an entry method attached.'''
    if 'RampEntry' in path.Name or 'LeadInOut' in path.Name:
        return True
    if 'Dressup' in path.Name and hasattr(path, 'Base'):
        return hasEntryMethod(path.Base)
    return False

def baseOp(path):
    '''baseOp(path) ... return the base operation underlying the given path'''
    if 'Dressup' in path.Name:
        return baseOp(path.Base)
    return path

def toolController(path):
    '''toolController(path) ... return the tool controller from the base op.'''
    return baseOp(path).ToolController

