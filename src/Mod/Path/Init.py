################################################################################
#  (c) Yorik van Havre (yorik@uncreated.net) 2014
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################

# Get the Parameter Group of this module
ParGrp = App.ParamGet("System parameter:Modules").GetGroup("Path")

# Set the needed information
ParGrp.SetString("HelpIndex",        "Path/Help/index.html")
ParGrp.SetString("WorkBenchName",    "Path")
ParGrp.SetString("WorkBenchModule",  "PathWorkbench.py")

FreeCAD.__unit_test__ += [ "TestPathApp" ]
