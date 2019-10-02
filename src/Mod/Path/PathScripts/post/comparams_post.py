#***************************************************************************
#*                                                                         *
#*   Copyright (c) 2015 Dan Falck <ddfalck@gmail.com>                      *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
#***************************************************************************
TOOLTIP=''' Example Post, using Path.Commands instead of Path.toGCode strings for Path gcode output. '''

import FreeCAD
import Path, PathScripts
from PathScripts import PostUtils

SHOW_EDITOR=True

def fmt(num):
    fnum = ""
    fnum += '%.3f' % (num)
    return fnum

def ffmt(num):
    fnum = ""
    fnum += '%.1f' % (num)
    return fnum

class saveVals(object):
    ''' save command info for modal output'''
    def __init__(self, command):
        self.com = command.Name
        self.params = command.Parameters

    def retVals(self):
        return self.com, self.params

def lineout(command, oldvals, modal):
    line = ""
    if modal and (oldvals.com == command.Name):
        line +=""
    else:
        line += str(command.Name)
    if command.Name == 'M6':
        line+= 'T'+str(int(command.Parameters['T']))
    if command.Name == 'M3':
        line+= 'S'+str(ffmt(command.Parameters['S']))
    if command.Name == 'M4':
        line+= 'S'+str(ffmt(command.Parameters['S']))
    if 'X' in command.Parameters:
        line += "X"+str(fmt(command.Parameters['X']))
    if 'Y' in command.Parameters:
        line += "Y"+str(fmt(command.Parameters['Y']))
    if 'Z' in command.Parameters:
        line += "Z"+str(fmt(command.Parameters['Z']))
    if 'I' in command.Parameters:
        line += "I"+str(fmt(command.Parameters['I']))
    if 'J' in command.Parameters:
        line += "J"+str(fmt(command.Parameters['J']))
    if 'F' in command.Parameters:
        line += "F"+str(ffmt(command.Parameters['F']))
    return line

def export(obj,filename,argstring):
    modal=True
    commands = obj[0]
    gcode = ''
    safetyblock1 = 'G90G40G49\n'
    gcode+=safetyblock1

    units = FreeCAD.ParamGet("User parameter:BaseApp/Preferences/Units")
    if units.GetInt('UserSchema') == 0:
        firstcommand = Path.Command('G21') #metric mode
    else:
        firstcommand = Path.Command('G20') #inch mode
    oldvals = saveVals(firstcommand) #save first command for modal use
    fp = obj[0]
    gcode+= firstcommand.Name

    if hasattr(fp,"Path"):
        for c in fp.Path.Commands:
            gcode+= lineout(c, oldvals, modal)+'\n'
            oldvals = saveVals(c)
        gcode+='M2\n'
        gfile = open(filename,"w")
        gfile.write(gcode)
        gfile.close()
    else:
        FreeCAD.Console.PrintError('Select a path object and try again\n')

    if SHOW_EDITOR:
        FreeCAD.Console.PrintMessage('Editor Activated\n')
        dia = PostUtils.GCodeEditorDialog()
        dia.editor.setText(gcode)
        dia.exec_()


