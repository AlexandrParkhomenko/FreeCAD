################################################################################
#  Copyright (c) 2009 Yorik van Havre <yorik@uncreated.net>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
# add Import/Export types
App.addImportType("Autodesk DXF 2D (*.dxf)","importDXF") 
App.addImportType("SVG as geometry (*.svg)","importSVG")
App.addImportType("Open CAD Format (*.oca *.gcad)","importOCA")
App.addImportType("Common airfoil data (*.dat)","importAirfoilDAT")
App.addExportType("Autodesk DXF 2D (*.dxf)","importDXF")
App.addExportType("Flattened SVG (*.svg)","importSVG")
App.addExportType("Open CAD Format (*.oca)","importOCA")
App.addImportType("Autodesk DWG 2D (*.dwg)","importDWG") 
App.addExportType("Autodesk DWG 2D (*.dwg)","importDWG")
