# Import gui init module  
# (c) 2003 Juergen Riegel
#
# Gathering all the information to start FreeCAD
# This is the second one of three init scripts, the third one
# runs when the gui is up

#***************************************************************************
#*   (c) Juergen Riegel (juergen.riegel@web.de) 2002                       *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
#*   Juergen Riegel 2002                                                   *
#***************************************************************************/


"""
class ImportWorkbench ( Workbench ):
	"Import workbench object"
	def Activate(self):
		# load the module
		try:
			Log ('Loading ImportGui module')
			import Import
			import ImportGui
		except ImportError:
			Err('Cannot load ImportGui')
			raise
	def GetIcon(self):
		# returns an icon for the workbench
		return ["/* XPM */\n"
			"static const char *fileopen[] = {\n"
			"\"16 13 5 1\",\n"
			"\". c #040404\",\n"
			"\"# c #808304\",\n"
			"\"a c None\",\n"
			"\"b c #f3f704\",\n"
			"\"c c #f3f7f3\",\n"
			"\"aaaaaaaaa...aaaa\",\n"
			"\"aaaaaaaa.aaa.a.a\",\n"
			"\"aaaaaaaaaaaaa..a\",\n"
			"\"a...aaaaaaaa...a\",\n"
			"\".bcb.......aaaaa\",\n"
			"\".cbcbcbcbc.aaaaa\",\n"
			"\".bcbcbcbcb.aaaaa\",\n"
			"\".cbcb...........\",\n"
			"\".bcb.#########.a\",\n"
			"\".cb.#########.aa\",\n"
			"\".b.#########.aaa\",\n"
			"\"..#########.aaaa\",\n"
			"\"...........aaaaa\"};\n"]

Gui.addWorkbench("Import",ImportWorkbench())
"""
# See https://forum.freecadweb.org/viewtopic.php?f=3&t=26782
#import Import_rc
#FreeCADGui.addPreferencePage(":/ui/preferences-import.ui","Import-Export")
