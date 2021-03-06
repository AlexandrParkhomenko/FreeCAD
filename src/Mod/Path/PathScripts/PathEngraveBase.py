################################################################################
#  Copyright (c) 2018 sliptonic <shopinthewoods@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import DraftGeomUtils
import Path
import PathScripts.PathGeom as PathGeom
import PathScripts.PathLog as PathLog
import PathScripts.PathOp as PathOp
import copy

from PySide2 import QtCore

__doc__ = "Base class for all ops in the engrave family."

LOGLEVEL = False

if LOGLEVEL:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())

# Qt translation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)

class ObjectOp(PathOp.ObjectOp):
    '''Proxy base class for engrave operations.'''

    def getZValues(self, obj):
        zValues = []
        if obj.StepDown.Value != 0:
            z = obj.StartDepth.Value - obj.StepDown.Value

            while z > obj.FinalDepth.Value:
                zValues.append(z)
                z -= obj.StepDown.Value
        zValues.append(obj.FinalDepth.Value)
        return zValues

    def buildpathocc(self, obj, wires, zValues, rel=False):
        '''buildpathocc(obj, wires, zValues, rel=False) ... internal helper function to generate engraving commands.'''
        PathLog.track(obj.Label, len(wires), zValues)

        for wire in wires:
            offset = wire

            # reorder the wire
            if hasattr(obj, 'StartVertex'):
                offset = DraftGeomUtils.rebaseWire(offset, obj.StartVertex)

            edges = copy.copy(offset.Edges)
            last = None

            for z in zValues:
                if last:
                    if rel:
                        self.commandlist.append(Path.Command('G1', {'X': last.x, 'Y': last.y, 'Z': last.z - z, 'F': self.vertFeed}))
                    else:
                        self.commandlist.append(Path.Command('G1', {'X': last.x, 'Y': last.y, 'Z': z, 'F': self.vertFeed}))

                for edge in edges:
                    if not last:
                        # we set the first move to our first point
                        last = edge.Vertexes[0].Point
                        if len(offset.Edges) > 1:
                            ve = edge.Vertexes[-1]
                            e2 = offset.Edges[1]
                            if not PathGeom.pointsCoincide(ve.Point, e2.Vertexes[0].Point) and not PathGeom.pointsCoincide(ve.Point, e2.Vertexes[-1].Point):
                                PathLog.debug("flip first edge")
                                last = edge.Vertexes[-1].Point
                            else:
                                PathLog.debug("original first edge")
                        else:
                            PathLog.debug("not enough edges to flip")

                        self.commandlist.append(Path.Command('G0', {'X': last.x, 'Y': last.y, 'Z': obj.ClearanceHeight.Value, 'F': self.horizRapid}))
                        self.commandlist.append(Path.Command('G0', {'X': last.x, 'Y': last.y, 'Z': obj.SafeHeight.Value, 'F': self.vertRapid}))
                        if rel:
                            self.commandlist.append(Path.Command('G1', {'X': last.x, 'Y': last.y, 'Z': last.z - z, 'F': self.vertFeed}))
                        else:
                            self.commandlist.append(Path.Command('G1', {'X': last.x, 'Y': last.y, 'Z': z, 'F': self.vertFeed}))

                    if PathGeom.pointsCoincide(last, edge.Vertexes[0].Point):
                        for cmd in PathGeom.cmdsForEdge(edge):
                            self.appendCommand(cmd, z, rel)
                        last = edge.Vertexes[-1].Point
                    else:
                        for cmd in PathGeom.cmdsForEdge(edge, True):
                            self.appendCommand(cmd, z, rel)
                        last = edge.Vertexes[0].Point
            self.commandlist.append(Path.Command('G0', {'Z': obj.ClearanceHeight.Value, 'F': self.vertRapid}))

    def appendCommand(self, cmd, z, rel):
        params = cmd.Parameters
        if rel:
            z = params['Z'] - z
        params.update({'Z': z, 'F': self.horizFeed})
        self.commandlist.append(Path.Command(cmd.Name, params))

    def opSetDefaultValues(self, obj, job):
        '''opSetDefaultValues(obj) ... set depths for engraving'''
        if PathOp.FeatureDepths & self.opFeatures(obj):
            if job and len(job.Model.Group) > 0:
                bb = job.Proxy.modelBoundBox(job)
                obj.OpStartDepth = bb.ZMax
                obj.OpFinalDepth = bb.ZMax - max(obj.StepDown.Value, 0.1)
            else:
                obj.OpFinalDepth = -0.1

