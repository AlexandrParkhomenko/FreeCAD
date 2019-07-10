#***************************************************************************
#*                                                                         *
#*   Copyright (c) 2014 - Juergen Riegel <FreeCAD@juergen-riegel.net>      *  
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
#***************************************************************************

import FreeCAD, FreeCADGui, Sketcher, Part


__title__="Hexagon profile lib"
__author__ = "Juergen Riegel"

App = FreeCAD
Gui = FreeCADGui

def makeHexagonSimple(sketchName=None):
    if not sketchName:
        sketch = App.ActiveDocument.addObject("Sketcher::SketchObject","Hexagon")
    else:
        sketch = App.ActiveDocument.getObject(sketchName)

    geoList = []
    geoList.append(Part.LineSegment(App.Vector(-20.00,34.64,0),App.Vector(20.00,34.64,0)))
    geoList.append(Part.LineSegment(App.Vector(20.00,34.64,0),App.Vector(47.082363,0.00,0)))
    geoList.append(Part.LineSegment(App.Vector(40.00,0.00,0),App.Vector(20.00,-34.64,0)))
    geoList.append(Part.LineSegment(App.Vector(20.00,-34.64,0),App.Vector(-20.00,-34.64,0)))
    geoList.append(Part.LineSegment(App.Vector(-20.00,-34.64,0),App.Vector(-40.00,0.00,0)))
    geoList.append(Part.LineSegment(App.Vector(-40.00,0.00,0),App.Vector(-20.00,34.64,0)))
    (l1,l2,l3,l4,l5,l6) = sketch.addGeometry(geoList)

    conList = []
    conList.append(Sketcher.Constraint('Coincident',l1,2,l2,1))
    conList.append(Sketcher.Constraint('Coincident',l2,2,l3,1))
    conList.append(Sketcher.Constraint('Coincident',l3,2,l4,1))
    conList.append(Sketcher.Constraint('Coincident',l4,2,l5,1))
    conList.append(Sketcher.Constraint('Coincident',l5,2,l6,1))
    conList.append(Sketcher.Constraint('Coincident',l6,2,l1,1))
    conList.append(Sketcher.Constraint('Equal',l1,l2))
    conList.append(Sketcher.Constraint('Equal',l2,l3))
    conList.append(Sketcher.Constraint('Equal',l3,l4))
    conList.append(Sketcher.Constraint('Equal',l4,l5))
    conList.append(Sketcher.Constraint('Equal',l5,l6))
    conList.append(Sketcher.Constraint('Angle',l1,2,l2,1,App.Units.Quantity('120.000000 deg')))
    conList.append(Sketcher.Constraint('Angle',l3,2,l4,1,App.Units.Quantity('120.000000 deg')))
    conList.append(Sketcher.Constraint('Angle',l5,2,l6,1,App.Units.Quantity('120.000000 deg')))
    sketch.addConstraint(conList)
    return

