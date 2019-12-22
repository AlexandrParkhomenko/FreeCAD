################################################################################
#  (c) Yorik van Havre (yorik@uncreated.net) 2014
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
TOOLTIP='''
This is an example postprocessor file for the Path workbench. It is used
to save a list of FreeCAD Path objects to a file.

Read the Path Workbench documentation to know how to convert Path objects
to GCode.
'''

import datetime
now = datetime.datetime.now()


# to distinguish python built-in open function from the one declared below
if open.__module__ in ['__builtin__','io']:
    pythonopen = open


def export(objectslist, filename,argstring):
    "called when freecad exports a list of objects"
    if len(objectslist) > 1:
        print("This script is unable to write more than one Path object")
        return
    obj = objectslist[0]
    if not hasattr(obj, "Path"):
        print("the given object is not a path")
    gcode = obj.Path.toGCode()
    gcode = parse(gcode)
    gfile = pythonopen(filename, "w")
    gfile.write(gcode)
    gfile.close()


def parse(inputstring):
    "parse(inputstring): returns a parsed output string"
    print("postprocessing...")

    output = ""

    # write some stuff first
    output += "N10 ;time:"+str(now)+"\n"
    output += "N20 G17 G20 G80 G40 G90\n"
    output += "N30 (Exported by FreeCAD)\n"

    linenr = 100
    lastcommand = None
    # treat the input line by line
    lines = inputstring.split("\n")
    for line in lines:
        # split the G/M command from the arguments
        if " " in line:
            command, args = line.split(" ", 1)
        else:
            # no space found, which means there are no arguments
            command = line
            args = ""
        # add a line number
        output += "N" + str(linenr) + " "
        # only print the command if it is not the same as the last one
        if command != lastcommand:
            output += command + " "
        output += args + "\n"
        # increment the line number
        linenr += 10
        # store the latest command
        lastcommand = command

    # write some more stuff at the end
    output += "N" + str(linenr) + " M05\n"
    output += "N" + str(linenr + 10) + " M25\n"
    output += "N" + str(linenr + 20) + " G00 X-1.0 Y1.0\n"
    output += "N" + str(linenr + 30) + " G17 G80 G40 G90\n"
    output += "N" + str(linenr + 40) + " M99\n"

    print("done postprocessing.")
    return output

print(__name__ + " gcode postprocessor loaded.")
