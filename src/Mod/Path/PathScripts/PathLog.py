# -*- coding: utf-8 -*-

# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2016 sliptonic <shopinthewoods@gmail.com>               *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

import FreeCAD
import os
import traceback

class Level:
    """Enumeration of log levels, used for setLevel and getLevel."""
    RESET   = -1
    ERROR   = 0
    WARNING = 1
    NOTICE  = 2
    INFO    = 3
    DEBUG   = 4

    _names = { ERROR: 'ERROR', WARNING: 'WARNING', NOTICE: 'NOTICE', INFO: 'INFO', DEBUG: 'DEBUG' }

    @classmethod
    def toString(cls, level):
        return cls._names.get(level, 'UNKNOWN')

_defaultLogLevel = Level.NOTICE
_moduleLogLevel  = { }
_useConsole = True
_trackModule = { }
_trackAll = False

def logToConsole(yes):
    """(boolean) - if set to True (default behaviour) log messages are printed to the console. Otherwise they are printed to stdout."""
    global _useConsole
    _useConsole = yes

def setLevel(level, module = None):
    """(level, module = None)
       if no module is specified the default log level is set.
       Otherwise the module specific log level is changed (use RESET to clear)."""
    global _defaultLogLevel
    global _moduleLogLevel
    if module:
        if level == Level.RESET:
            if _moduleLogLevel.get(module, -1) != -1:
                del _moduleLogLevel[module]
        else:
            _moduleLogLevel[module] = level
    else:
        if level == Level.RESET:
            _defaultLogLevel = Level.NOTICE
            _moduleLogLevel = { }
        else:
            _defaultLogLevel = level

def getLevel(module = None):
    """(module = None) - return the global (None) or module specific log level."""
    if module:
        return _moduleLogLevel.get(module, _defaultLogLevel)
    return _defaultLogLevel

def thisModule():
    """returns the module id of the caller, can be used for setLevel, getLevel and trackModule."""
    return _caller()[0]

def _caller():
    """internal function to determine the calling module."""
    file, line, func, text = traceback.extract_stack(limit=3)[0]
    return os.path.splitext(os.path.basename(file))[0], line, func

def _log(level, module_line_func, msg):
    """internal function to do the logging"""
    module, line, func = module_line_func
    if getLevel(module) >= level:
        message = "%s.%s: %s" % (module, Level.toString(level), msg)
        if _useConsole:
            message += "\n"
            if level == Level.NOTICE:
                FreeCAD.Console.PrintLog(message)
            elif level == Level.WARNING:
                FreeCAD.Console.PrintWarning(message)
            elif level == Level.ERROR:
                FreeCAD.Console.PrintError(message)
            else:
                FreeCAD.Console.PrintMessage(message)
        else:
            print(message)
        return message
    return None

def debug(msg):
    """(message)"""
    return _log(Level.DEBUG, _caller(), msg)
def info(msg):
    """(message)"""
    return _log(Level.INFO, _caller(), msg)
def notice(msg):
    """(message)"""
    return _log(Level.NOTICE, _caller(), msg)
def warning(msg):
    """(message)"""
    return _log(Level.WARNING, _caller(), msg)
def error(msg):
    """(message)"""
    return _log(Level.ERROR, _caller(), msg)

def trackAllModules(boolean):
    """(boolean) - if True all modules will be tracked, otherwise tracking is up to the module setting."""
    global _trackAll
    _trackAll = boolean

def untrackAllModules():
    """In addition to stop tracking all modules it also clears the tracking flag for all individual modules."""
    global _trackAll
    global _trackModule
    _trackAll = False
    _trackModule = { }

def trackModule(module = None):
    """(module = None) - start tracking given module, current module if not set."""
    global _trackModule
    if module:
        _trackModule[module] = True
    else:
        mod, line, func = _caller()
        _trackModule[mod] = True

def untrackModule(module = None):
    """(module = None) - stop tracking given module, current module if not set."""
    global _trackModule
    if module and _trackModule.get(module, None):
        del _trackModule[module]
    elif not module:
        mod, line, func = _caller()
        if _trackModule.get(mod, None):
            del _trackModule[mod]

def track(*args):
    """(....) - call with arguments of current function you want logged if tracking is enabled."""
    module, line, func = _caller()
    if _trackAll or _trackModule.get(module, None):
        message = "%s(%d).%s(%s)" % (module, line, func, ', '.join([str(arg) for arg in args]))
        if _useConsole:
            FreeCAD.Console.PrintMessage(message + "\n")
        else:
            print(message)
        return message
    return None

