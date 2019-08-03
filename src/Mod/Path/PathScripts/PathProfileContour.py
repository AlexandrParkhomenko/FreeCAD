# -*- coding: utf-8 -*-

# ***************************************************************************
# *   Copyright (c) 2016 sliptonic <shopinthewoods@gmail.com>               *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import Part
import Path
import PathScripts.PathProfileBase as PathProfileBase
import PathScripts.PathLog as PathLog

from PathScripts import PathUtils
from PySide2 import QtCore

FreeCAD.setLogLevel('Path.Area', 0)

LOGLEVEL = False

if LOGLEVEL:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())

# Qt translation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)

__title__ = "Path Contour Operation"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Implementation of the Contour operation."


class ObjectContour(PathProfileBase.ObjectProfile):
    '''Proxy object for Contour operations.'''

    def baseObject(self):
        '''baseObject() ... returns super of receiver
        Used to call base implementation in overwritten functions.'''
        return super(self.__class__, self)

    def areaOpFeatures(self, obj):
        '''areaOpFeatures(obj) ... returns 0, Contour only requires the base profile features.'''
        return 0

    def initAreaOp(self, obj):
        '''initAreaOp(obj) ... call super's implementation and hide Side property.'''
        self.baseObject().initAreaOp(obj)
        obj.setEditorMode('Side', 2) # it's always outside

    def areaOpOnDocumentRestored(self, obj):
        obj.setEditorMode('Side', 2) # it's always outside

    def areaOpSetDefaultValues(self, obj, job):
        '''areaOpSetDefaultValues(obj, job) ... call super's implementation and set Side="Outside".'''
        self.baseObject().areaOpSetDefaultValues(obj, job)
        obj.Side = 'Outside'

    def areaOpShapes(self, obj):
        '''areaOpShapes(obj) ... return envelope over the job's Base.Shape or all Arch.Panel shapes.'''
        if obj.UseComp:
            self.commandlist.append(Path.Command("(Compensated Tool Path. Diameter: " + str(self.radius * 2) + ")"))
        else:
            self.commandlist.append(Path.Command("(Uncompensated Tool Path)"))

        isPanel = False

        if not isPanel:
            return [(PathUtils.getEnvelope(partshape=base.Shape, subshape=None, depthparams=self.depthparams), False) for base in self.model if hasattr(base, 'Shape')]

    def areaOpAreaParams(self, obj, isHole):
        params = self.baseObject().areaOpAreaParams(obj, isHole)
        params['Coplanar'] = 2
        return params

    def opUpdateDepths(self, obj):
        obj.OpStartDepth = obj.OpStockZMax
        obj.OpFinalDepth = obj.OpStockZMin

def SetupProperties():
    return [p for p in PathProfileBase.SetupProperties() if p != 'Side']

def Create(name, obj = None):
    '''Create(name) ... Creates and returns a Contour operation.'''
    if obj is None:
        obj   = FreeCAD.ActiveDocument.addObject("Path::FeaturePython", name)
    obj.Proxy = ObjectContour(obj, name)
    return obj
