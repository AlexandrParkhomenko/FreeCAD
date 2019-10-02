# ***************************************************************************
# *   Copyright (c) 2016 sliptonic <shopinthewoods@gmail.com>               *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import Part
import Path
import PathScripts.PathLog as PathLog
import PathScripts.PathOp as PathOp
import PathScripts.PathProfileBase as PathProfileBase
import PathScripts.PathUtils as PathUtils

from DraftGeomUtils import findWires
from PySide2 import QtCore

LOGLEVEL = False

if LOGLEVEL:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())


# Qt translation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)

__title__ = "Path Profile Edges Operation"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Path Profile operation based on edges."


class ObjectProfile(PathProfileBase.ObjectProfile):
    '''Proxy object for Profile operations based on edges.'''

    def baseObject(self):
        '''baseObject() ... returns super of receiver
        Used to call base implementation in overwritten functions.'''
        return super(self.__class__, self)

    def areaOpFeatures(self, obj):
        '''areaOpFeatures(obj) ... add support for edge base geometry.'''
        return PathOp.FeatureBaseEdges

    def areaOpShapes(self, obj):
        '''areaOpShapes(obj) ... returns envelope for all wires formed by the base edges.'''
        PathLog.track()

        if obj.UseComp:
            self.commandlist.append(Path.Command("(Compensated Tool Path. Diameter: " + str(self.radius * 2) + ")"))
        else:
            self.commandlist.append(Path.Command("(Uncompensated Tool Path)"))

        shapes = []
        if obj.Base:
            basewires = []

            zMin = None
            for b in obj.Base:
                edgelist = []
                for sub in b[1]:
                    edgelist.append(getattr(b[0].Shape, sub))
                basewires.append((b[0], findWires(edgelist)))
                if zMin is None or b[0].Shape.BoundBox.ZMin < zMin:
                    zMin = b[0].Shape.BoundBox.ZMin

            for base,wires in basewires:
                for wire in wires:
                    f = Part.makeFace(wire, 'Part::FaceMakerSimple')

                    # shift the compound to the bottom of the base object for
                    # proper sectioning
                    zShift = zMin - f.BoundBox.ZMin
                    newPlace = FreeCAD.Placement(FreeCAD.Vector(0, 0, zShift), f.Placement.Rotation)
                    f.Placement = newPlace
                    env = PathUtils.getEnvelope(base.Shape, subshape=f, depthparams=self.depthparams)
                    shapes.append((env, False))
        return shapes

def SetupProperties():
    return PathProfileBase.SetupProperties()

def Create(name, obj = None):
    '''Create(name) ... Creates and returns a Profile based on edges operation.'''
    if obj is None:
        obj = FreeCAD.ActiveDocument.addObject("Path::FeaturePython", name)
    obj.Proxy = ObjectProfile(obj, name)
    return obj
