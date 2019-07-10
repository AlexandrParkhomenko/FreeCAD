# -*- coding: utf-8 -*-

# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2014 Yorik van Havre <yorik@uncreated.net>              *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import Part
import PathScripts.PathGeom as PathGeom
import PathScripts.PathLog as PathLog
import PathScripts.PathOp as PathOp
import PathScripts.PathPocketBase as PathPocketBase
import PathScripts.PathUtils as PathUtils
import sys

from PySide import QtCore

__doc__ = "Class and implementation of the Pocket operation."

if False:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())

# Qt tanslation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)


class ObjectPocket(PathPocketBase.ObjectPocket):
    '''Proxy object for Pocket operation.'''

    def pocketOpFeatures(self, obj):
        return PathOp.FeatureNoFinalDepth

    def initPocketOp(self, obj):
        '''initPocketOp(obj) ... setup receiver'''
        pass

    def pocketInvertExtraOffset(self):
        return False

    def areaOpShapes(self, obj):
        '''areaOpShapes(obj) ... return shapes representing the solids to be removed.'''
        PathLog.track()

        removalshapes = []
        if obj.Base:
            PathLog.debug("base items exist.  Processing...")
            for base in obj.Base:
                PathLog.debug("Base item: {}".format(base))
                for sub in base[1]:
                    if "Face" in sub:
                        shape = Part.makeCompound([getattr(base[0].Shape, sub)])
                    else:
                        edges = [getattr(base[0].Shape, sub) for sub in base[1]]
                        shape = Part.makeFace(edges, 'Part::FaceMakerSimple')

                    env = PathUtils.getEnvelope(base[0].Shape, subshape=shape, depthparams=self.depthparams)
                    obj.removalshape = env.cut(base[0].Shape)
                    obj.removalshape.tessellate(0.1)
                    removalshapes.append((obj.removalshape, False))
        else:  # process the job base object as a whole
            PathLog.debug("processing the whole job base object")
            for base in self.model:
                env = PathUtils.getEnvelope(base.Shape, subshape=None, depthparams=self.depthparams)
                obj.removalshape = env.cut(base.Shape)
                obj.removalshape.tessellate(0.1)
                removalshapes.append((obj.removalshape, False))
        return removalshapes

    def areaOpSetDefaultValues(self, obj, job):
        '''areaOpSetDefaultValues(obj, job) ... set default values'''
        obj.StepOver = 100
        obj.ZigZagAngle = 45

def SetupProperties():
    return PathPocketBase.SetupProperties()

def Create(name, obj = None):
    '''Create(name) ... Creates and returns a Pocket operation.'''
    if obj is None:
        obj = FreeCAD.ActiveDocument.addObject("Path::FeaturePython", name)
    proxy = ObjectPocket(obj, name)
    return obj
