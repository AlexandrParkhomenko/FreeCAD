# -*- coding: utf-8 -*-

# ***************************************************************************
# *   Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>               *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

'''
The purpose of this file is to collect some handy functions. The reason they
are not in PathUtils (and there is this confusing naming going on) is that
PathUtils depends on PathJob. Which makes it impossible to use the functions
and classes defined there in PathJob.

So if you add to this file and think about importing anything from PathScripts
other than PathLog, then it probably doesn't belong here.
'''

import six
import PathScripts.PathLog as PathLog

LOGLEVEL = False

if LOGLEVEL:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())

# NotValidBaseTypeIds = ['Sketcher::SketchObject']
NotValidBaseTypeIds = []


def isValidBaseObject(obj):
    '''isValidBaseObject(obj) ... returns true if the object can be used as a base for a job.'''
    if hasattr(obj, 'getParentGeoFeatureGroup') and obj.getParentGeoFeatureGroup():
        # Can't link to anything inside a geo feature group anymore
        PathLog.debug("%s is inside a geo feature group" % obj.Label)
        return False
    if hasattr(obj, 'TypeId') and 'App::Part' == obj.TypeId:
        return obj.Group and any(hasattr(o, 'Shape') for o in obj.Group)
    if not hasattr(obj, 'Shape'):
        PathLog.debug("%s has no shape" % obj.Label)
        return False
    if obj.TypeId in NotValidBaseTypeIds:
        PathLog.debug("%s is blacklisted (%s)" % (obj.Label, obj.TypeId))
        return False
    if hasattr(obj, 'Sheets') or hasattr(obj, 'TagText'): # Arch.Panels and Arch.PanelCut
        PathLog.debug("%s is not an Arch.Panel" % (obj.Label))
        return False
    return True

def isSolid(obj):
    '''isSolid(obj) ... return True if the object is a valid solid.'''
    if hasattr(obj, 'Tip'):
        return isSolid(obj.Tip)
    if hasattr(obj, 'Shape'):
        if obj.Shape.Volume > 0.0 and obj.Shape.isClosed():
            return True
    if hasattr(obj, 'TypeId') and 'App::Part' == obj.TypeId:
        if not obj.Group or any(hasattr(o, 'Shape') and not isSolid(o) for o in obj.Group):
            return False
        return True
    return False

def toolControllerForOp(op):
    '''toolControllerForOp(op) ... return the tool controller used by the op.
    If the op doesn't have its own tool controller but has a Base object, return its tool controller.
    Otherwise return None.'''
    if hasattr(op, 'ToolController'):
        return op.ToolController
    if hasattr(op, 'Base'):
        return toolControllerForOp(op.Base)
    return None

def getPublicObject(obj):
    '''getPublicObject(obj) ... returns the object which should be used to reference a feature of the given object.'''
    if hasattr(obj, 'getParentGeoFeatureGroup'):
        body = obj.getParentGeoFeatureGroup()
        if body:
            return getPublicObject(body)
    return obj

def clearExpressionEngine(obj):
    '''clearExpressionEngine(obj) ... removes all expressions from obj.

There is currently a bug that invalidates the DAG if an object
is deleted that still has one or more expressions attached to it.
Use this function to remove all expressions before deletion.'''
    if hasattr(obj, 'ExpressionEngine'):
        for attr, expr in obj.ExpressionEngine: # pylint: disable=unused-variable
            obj.setExpression(attr, None)

def toUnicode(string):
    '''toUnicode(string) ... returns a unicode version of string regardless of the python version.'''
    return six.text_type(string)

def isString(string):
    '''isString(string) ... return True if string is a string, regardless of string type and python version.'''
    return isinstance(string, six.string_types)

def keyValueIter(dictionary):
    '''keyValueIter(dict) ... return iterable object over dictionary's (key,value) tuples.'''
    return six.iteritems(dictionary)
