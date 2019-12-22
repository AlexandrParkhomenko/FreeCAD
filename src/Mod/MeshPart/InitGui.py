# MeshPart gui init module  
# (c) 2003 Juergen Riegel
#
# Gathering all the information to start FreeCAD
# This is the second one of three init scripts, the third one
# runs when the gui is up

################################################################################
#  (c) Juergen Riegel (juergen.riegel@web.de) 2002
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
#  Juergen Riegel 2002
################################################################################
class MeshPartWorkbench ( Workbench ):
	"MeshPart workbench object"
	Icon = """
			/* XPM */
			static const char *MeshPart_Box[]={
			"16 16 3 1",
			". c None",
			"# c #000000",
			"a c #c6c642",
			"................",
			".......#######..",
			"......#aaaaa##..",
			".....#aaaaa###..",
			"....#aaaaa##a#..",
			"...#aaaaa##aa#..",
			"..#aaaaa##aaa#..",
			".########aaaa#..",
			".#aaaaa#aaaaa#..",
			".#aaaaa#aaaa##..",
			".#aaaaa#aaa##...",
			".#aaaaa#aa##....",
			".#aaaaa#a##... .",
			".#aaaaa###......",
			".########.......",
			"................"};
			"""
	MenuText = "MeshPart"
	ToolTip = "MeshPart workbench"

	def Initialize(self):
		# load the module
		import MeshPartGui
		import MeshPart
	def GetClassName(self):
		return "MeshPartGui::Workbench"

#Gui.addWorkbench(MeshPartWorkbench())
