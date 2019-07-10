# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2019 Werner Mayer <wmayer[at]users.sourceforge.net>     *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

__title__ = "BasicShapes.Shapes"
__author__ = "Werner Mayer"
__doc__ = "Basic shapes"


import FreeCAD
from FreeCAD import Qt
import FreeCADGui
import Part
import math
import sys

def makeTube(outerRadius, innerRadius, height):
    outer_cylinder = Part.makeCylinder(outerRadius, height)
    shape = outer_cylinder
    if innerRadius > 0 and innerRadius < outerRadius:
        inner_cylinder = Part.makeCylinder(innerRadius, height)
        shape = outer_cylinder.cut(inner_cylinder)
    return shape


class TubeFeature:
    def __init__(self, obj):
        obj.Proxy = self
        obj.addProperty("App::PropertyLength","OuterRadius","Tube","Outer radius").OuterRadius = 5.0
        obj.addProperty("App::PropertyLength","InnerRadius","Tube","Inner radius").InnerRadius = 2.0
        obj.addProperty("App::PropertyLength","Height","Tube", "Height of the tube").Height = 10.0

    def execute(self, fp):
        fp.Shape = makeTube(fp.OuterRadius, fp.InnerRadius, fp.Height)


class _CommandMakeTube:
    "Make tube command"
    def GetResources(self):
        return {'MenuText': Qt.QT_TRANSLATE_NOOP("Part_MakeTube","Create tube"),
                'Accel': "",
                'CmdType': "ForEdit",
                'ToolTip': Qt.QT_TRANSLATE_NOOP("Part_MakeTube","Creates a tube")}
        
    def Activated(self):
        FreeCAD.ActiveDocument.openTransaction("Create tube")
        tube = FreeCAD.ActiveDocument.addObject("Part::FeaturePython","Tube")
        TubeFeature(tube)
        tube.ViewObject.Proxy = 0
        FreeCAD.ActiveDocument.commitTransaction()
        FreeCAD.ActiveDocument.recompute()

    def IsActive(self):
        return not FreeCAD.ActiveDocument is None


FreeCADGui.addCommand('Part_MakeTube',_CommandMakeTube())
