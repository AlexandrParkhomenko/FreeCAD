################################################################################
#  Copyright (c) 2018 sliptonic <shopinthewoods@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
# pylint: disable=unused-import

import PathScripts.PathLog as PathLog

LOGLEVEL = False

if LOGLEVEL:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())

Processed = False

def Startup():
    global Processed # pylint: disable=global-statement
    if not Processed:
        PathLog.debug('Initializing PathGui')
        from PathScripts import PathAdaptiveGui
        from PathScripts import PathArray
        from PathScripts import PathComment
        from PathScripts import PathCustom
        from PathScripts import PathDeburrGui
        from PathScripts import PathDressupAxisMap
        from PathScripts import PathDressupDogbone
        from PathScripts import PathDressupDragknife
        from PathScripts import PathDressupRampEntry
        from PathScripts import PathDressupTagGui
        from PathScripts import PathDressupLeadInOut
        from PathScripts import PathDrillingGui
        from PathScripts import PathEngraveGui
        from PathScripts import PathFixture
        from PathScripts import PathHelixGui
        from PathScripts import PathHop
        from PathScripts import PathInspect
        from PathScripts import PathMillFaceGui
        from PathScripts import PathPocketGui
        from PathScripts import PathPocketShapeGui
        from PathScripts import PathPost
        from PathScripts import PathProfileContourGui
        from PathScripts import PathProfileEdgesGui
        from PathScripts import PathProfileFacesGui
        from PathScripts import PathSanity
        from PathScripts import PathSetupSheetGui
        from PathScripts import PathSimpleCopy
#        from PathScripts import PathSimulatorGui
        from PathScripts import PathStop
        try:
            import ocl
            from PathScripts import PathSurfaceGui
        except ImportError:
            import FreeCAD
            FreeCAD.Console.PrintError("OpenCamLib is not working!\n")
        from PathScripts import PathToolController
        from PathScripts import PathToolControllerGui
        from PathScripts import PathToolLibraryManager
        from PathScripts import PathUtilsGui
        Processed = True
    else:
        PathLog.debug('Skipping PathGui initialisation')

