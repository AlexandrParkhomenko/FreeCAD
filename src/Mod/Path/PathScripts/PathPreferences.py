# -*- coding: utf-8 -*-

# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2014 Yorik van Havre <yorik@uncreated.net>              *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import glob
import os
import PathScripts.PathLog as PathLog

PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())
#PathLog.trackModule()

DefaultFilePath           = "DefaultFilePath"
DefaultJobTemplate        = "DefaultJobTemplate"
DefaultStockTemplate      = "DefaultStockTemplate"
DefaultTaskPanelLayout    = "DefaultTaskPanelLayout"

PostProcessorDefault      = "PostProcessorDefault"
PostProcessorDefaultArgs  = "PostProcessorDefaultArgs"
PostProcessorBlacklist    = "PostProcessorBlacklist"
PostProcessorOutputFile   = "PostProcessorOutputFile"
PostProcessorOutputPolicy = "PostProcessorOutputPolicy"

# Linear tolerance to use when generating Paths, eg when tessellating geometry
GeometryTolerance       = "GeometryTolerance"
LibAreaCurveAccuracy    = "LibAreaCurveAccuarcy"

EnableExperimentalFeatures = "EnableExperimentalFeatures"


def preferences():
    return FreeCAD.ParamGet("User parameter:BaseApp/Preferences/Mod/Path")

def pathScriptsSourcePath():
    return FreeCAD.getHomePath() + ("Mod/Path/PathScripts/")

def pathScriptsPostSourcePath():
    return pathScriptsSourcePath() + ("/post/")

def allAvailablePostProcessors():
    allposts = []
    for path in searchPaths():
        posts = [ str(os.path.split(os.path.splitext(p)[0])[1][:-5]) for p in glob.glob(path + '/*_post.py')]
        allposts.extend(posts)
    allposts.sort()
    return allposts

def allEnabledPostProcessors(include = None):
    blacklist = postProcessorBlacklist()
    enabled = [processor for processor in allAvailablePostProcessors() if not processor in blacklist]
    if include:
        l = list(set(include + enabled))
        l.sort()
        return l
    return enabled


def defaultPostProcessor():
    pref = preferences()
    return pref.GetString(PostProcessorDefault, "")

def defaultPostProcessorArgs():
    pref = preferences()
    return pref.GetString(PostProcessorDefaultArgs, "")

def defaultGeometryTolerance():
    return preferences().GetFloat(GeometryTolerance, 0.01)

def defaultLibAreaCurveAccuracy():
    return preferences().GetFloat(LibAreaCurveAccuracy, 0.01)

def defaultFilePath():
    return preferences().GetString(DefaultFilePath)

def filePath():
    path = defaultFilePath()
    if not path:
        path = macroFilePath()
    return path

def macroFilePath():
    grp = FreeCAD.ParamGet("User parameter:BaseApp/Preferences/Macro")
    return grp.GetString("MacroPath", FreeCAD.getUserMacroDir())

def searchPaths():
    paths = []
    p = defaultFilePath()
    if p:
        paths.append(p)
    paths.append(macroFilePath())
    paths.append(pathScriptsPostSourcePath())
    paths.append(pathScriptsSourcePath())
    return paths

def defaultJobTemplate():
    template = preferences().GetString(DefaultJobTemplate)
    if 'xml' not in template:
        return template
    return ''

def setJobDefaults(filePath, jobTemplate, geometryTolerance, curveAccuracy):
    PathLog.track("(%s='%s', %s, %s, %s)" % (DefaultFilePath, filePath, jobTemplate, geometryTolerance, curveAccuracy))
    pref = preferences()
    pref.SetString(DefaultFilePath, filePath)
    pref.SetString(DefaultJobTemplate, jobTemplate)
    pref.SetFloat(GeometryTolerance, geometryTolerance)
    pref.SetFloat(LibAreaCurveAccuracy, curveAccuracy)

def postProcessorBlacklist():
    pref = preferences()
    blacklist = pref.GetString(PostProcessorBlacklist, "")
    if not blacklist:
        return []
    return eval(blacklist)

def setPostProcessorDefaults(processor, args, blacklist):
    pref = preferences()
    pref.SetString(PostProcessorDefault, processor)
    pref.SetString(PostProcessorDefaultArgs, args)
    pref.SetString(PostProcessorBlacklist, "%s" % (blacklist))


def setOutputFileDefaults(file, policy):
    pref = preferences()
    pref.SetString(PostProcessorOutputFile, file)
    pref.SetString(PostProcessorOutputPolicy, policy)

def defaultOutputFile():
    pref = preferences()
    return pref.GetString(PostProcessorOutputFile, "")

def defaultOutputPolicy():
    pref = preferences()
    return pref.GetString(PostProcessorOutputPolicy, "")

def defaultStockTemplate():
    return preferences().GetString(DefaultStockTemplate, "")
def setDefaultStockTemplate(template):
    preferences().SetString(DefaultStockTemplate, template)

def defaultTaskPanelLayout():
    return preferences().GetInt(DefaultTaskPanelLayout, 0)
def setDefaultTaskPanelLayout(style):
    preferences().SetInt(DefaultTaskPanelLayout, style)

def experimentalFeaturesEnabled():
    return preferences().GetBool(EnableExperimentalFeatures, False)

