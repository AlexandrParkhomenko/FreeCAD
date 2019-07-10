# Mesh gui init module
# (c) 2004 Werner Mayer
#
# Gathering all the information to start FreeCAD
# This is the second one of three init scripts, the third one
# runs when the gui is up

#***************************************************************************
#*   (c) Werner Mayer <werner.wm.mayer@gmx.de> 2004                        *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
#*   Werner Mayer 2004                                                     *
#***************************************************************************/

class MeshWorkbench (Workbench):
    "Mesh workbench object"
    def __init__(self):
        self.__class__.Icon = FreeCAD.getResourceDir() + "Mod/Mesh/Resources/icons/MeshWorkbench.svg"
        self.__class__.MenuText = "Mesh Design"
        self.__class__.ToolTip = "Mesh design workbench"

    def Initialize(self):
        import Mesh
        import MeshGui
        try:
            import flatmesh
            import MeshFlatteningCommand
        except ImportError as e:
            import FreeCAD
            FreeCAD.Console.PrintLog((str(e)))
    def GetClassName(self):
        return "MeshGui::Workbench"

Gui.addWorkbench(MeshWorkbench())
