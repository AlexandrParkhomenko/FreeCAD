# FreeCAD init script of the Points module
# (c) 2005 Juergen Riegel

################################################################################
#  (c) Juergen Riegel (juergen.riegel@web.de) 2005
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
#  Juergen Riegel 2002
################################################################################
# Append the open handler
FreeCAD.addImportType("Point formats (*.asc *.pcd *.ply)","Points")
FreeCAD.addExportType("Point formats (*.asc *.pcd *.ply)","Points")
