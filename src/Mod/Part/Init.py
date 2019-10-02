################################################################################
#  (c) Juergen Riegel (juergen.riegel@web.de) 2001
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
#  FreeCAD init script of the part module  
################################################################################
#FreeCAD.addImportType("CAD formats (*.igs *.iges *.step *.stp *.brep *.brp)","Part")
#FreeCAD.addExportType("CAD formats (*.igs *.iges *.step *.stp *.brep *.brp)","Part")
FreeCAD.addImportType("BREP format (*.brep *.brp)","Part")
FreeCAD.addExportType("BREP format (*.brep *.brp)","Part")
FreeCAD.addImportType("IGES format (*.iges *.igs)","Part")
FreeCAD.addExportType("IGES format (*.iges *.igs)","Part")
FreeCAD.addImportType("STEP with colors (*.step *.stp)","ImportGui")
FreeCAD.addExportType("STEP with colors (*.step *.stp)","ImportGui")

FreeCAD.__unit_test__ += [ "TestPartApp" ]
