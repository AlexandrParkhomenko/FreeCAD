# Points gui init module
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



class PointsWorkbench ( Workbench ):
    "Points workbench object"
    def __init__(self):
        self.__class__.Icon = FreeCAD.getResourceDir() + "Mod/Points/Resources/icons/PointsWorkbench.svg"
        self.__class__.MenuText = "Points"
        self.__class__.ToolTip = "Points workbench"

    def Initialize(self):
        # load the module
        import PointsGui
    def GetClassName(self):
        return "PointsGui::Workbench"

Gui.addWorkbench(PointsWorkbench())
