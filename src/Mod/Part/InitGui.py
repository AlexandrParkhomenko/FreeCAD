################################################################################
#  (c) Juergen Riegel (juergen.riegel@web.de) 2002
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
#
#  Part gui init module.
#  Gathering all the information to start FreeCAD
#  This is the second one of three init scripts, the third one
#  runs when the gui is up.
################################################################################
class PartWorkbench ( Workbench ):
    "Part workbench object"
    def __init__(self):
        self.__class__.Icon = FreeCAD.getResourceDir() + "Mod/Part/Resources/icons/PartWorkbench.svg"
        self.__class__.MenuText = "Part"
        self.__class__.ToolTip = "Part workbench"

    def Initialize(self):
        # load the module
        import PartGui

        try:
            import BasicShapes.Shapes
        except ImportError as err:
            FreeCAD.Console.PrintError("Features from BasicShapes package cannot be loaded. {err}\n".format(err= str(err)))

        try:
            import CompoundTools._CommandCompoundFilter
            import CompoundTools._CommandExplodeCompound
        except ImportError as err:
            FreeCAD.Console.PrintError("Features from CompoundTools package cannot be loaded. {err}\n".format(err= str(err)))


        try:
            bop = __import__("BOPTools")
            bop.importAll()
            bop.addCommands()
            PartGui.BOPTools = bop
        except Exception as err:
            FreeCAD.Console.PrintError("Features from BOPTools package cannot be loaded. {err}\n".format(err= str(err)))        

    def GetClassName(self):
        return "PartGui::Workbench"

Gui.addWorkbench(PartWorkbench())

FreeCAD.__unit_test__ += [ "TestPartGui" ]
