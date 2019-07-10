#***************************************************************************
#*                                                                         *
#*   Copyright (c) 2014 Daniel Falck  <ddfalck@gmail.com>                  *  
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
#***************************************************************************
'''
This macro finds the outside profile of a 3D shape. Right now it just creates wires that represent the shape,but it could be used for finding the outside profile of an object for a toolpath
'''
import FreeCADGui
import DraftGeomUtils
from FreeCAD import Vector
from PathScripts import find_outer_profile as fop

sel = FreeCADGui.Selection.getSelection()[0]
obj = sel
el = fop.edgelist(obj)
hl = fop.horizontal(el)
connected = DraftGeomUtils.findWires(hl)
goodwires = fop.openFilter(connected)

outerwires ,innerwires, same = fop.findOutsideWire(goodwires)
#get distance from outerwires Z to bottom of part
zdiff = obj.Shape.BoundBox.ZMin- outerwires.BoundBox.ZMax
outerwires.Placement.move(Vector(0,0,zdiff))
Part.show(outerwires)

zupperouter = outerwires
zupperouter.Placement.move(Vector(0,0,obj.Shape.BoundBox.ZMax))
Part.show(zupperouter)
