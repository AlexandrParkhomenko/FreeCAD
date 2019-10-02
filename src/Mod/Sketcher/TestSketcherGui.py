#   (c) Juergen Riegel (FreeCAD@juergen-riegel.net) 2011      LGPL
#   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import FreeCAD, FreeCADGui, os, sys, unittest, Sketcher, SketcherGui


#---------------------------------------------------------------------------
# define the test cases to test the FreeCAD Sketcher module
#---------------------------------------------------------------------------


#class SketcherGuiTestCases(unittest.TestCase):
#	def setUp(self):
#		self.Doc = FreeCAD.newDocument("SketchGuiTest")
#
#	def testBoxCase(self):
#		self.Box = self.Doc.addObject('Sketcher::SketchObject','SketchBox')
#		self.Box.addGeometry(Part.LineSegment(App.Vector(-99.230339,36.960674,0),App.Vector(69.432587,36.960674,0)))
#		self.Box.addGeometry(Part.LineSegment(App.Vector(69.432587,36.960674,0),App.Vector(69.432587,-53.196629,0)))
#		self.Box.addGeometry(Part.LineSegment(App.Vector(69.432587,-53.196629,0),App.Vector(-99.230339,-53.196629,0)))
#		self.Box.addGeometry(Part.LineSegment(App.Vector(-99.230339,-53.196629,0),App.Vector(-99.230339,36.960674,0)))
################################################################################
#	def tearDown(self):
#		#closing doc
#		FreeCAD.closeDocument("SketchGuiTest")
