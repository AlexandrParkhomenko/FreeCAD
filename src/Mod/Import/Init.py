# FreeCAD init script of the Import module  
# (c) 2001 Juergen Riegel

################################################################################
#  (c) Juergen Riegel (juergen.riegel@web.de) 2002
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
#  Juergen Riegel 2002
################################################################################
# Append the open handler
#FreeCAD.addImportType("STEP 214 (*.step *.stp)","ImportGui")
#FreeCAD.addExportType("STEP 214 (*.step *.stp)","ImportGui")
#FreeCAD.addExportType("IGES files (*.iges *.igs)","ImportGui")
FreeCAD.addImportType("PLMXML files (*.plmxml)","PlmXmlParser")
FreeCAD.addImportType("STEPZ Zip File Type (*.stpZ *.stpz)","stepZ") 
FreeCAD.addExportType("STEPZ zip File Type (*.stpZ *.stpz)","stepZ") 

# Add initial parameters value if they are not set

paramGetV = FreeCAD.ParamGet("User parameter:BaseApp/Preferences/Mod/Import/hSTEP")
if  paramGetV.GetBool("ReadShapeCompoundMode", False) != paramGetV.GetBool("ReadShapeCompoundMode", True):
    paramGetV.SetBool("ReadShapeCompoundMode", True)
