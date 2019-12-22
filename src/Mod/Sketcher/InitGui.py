# Sketcher gui init module  
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
class SketcherWorkbench ( Workbench ):
    "Sketcher workbench object"
    def __init__(self):
        self.__class__.Icon = FreeCAD.getResourceDir() + "Mod/Sketcher/Resources/icons/SketcherWorkbench.svg"
        self.__class__.MenuText = "Sketcher"
        self.__class__.ToolTip = "Sketcher workbench"

    def Initialize(self):
        # load the module
        import SketcherGui
        import Sketcher
        try:
            import Profiles
        except ImportError:
            print("Error in Profiles module")
            
    def GetClassName(self):
        return "SketcherGui::Workbench"

Gui.addWorkbench(SketcherWorkbench())

FreeCAD.__unit_test__ += [ "TestSketcherGui" ]
