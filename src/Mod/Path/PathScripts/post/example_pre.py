# ***************************************************************************
# *   (c) Yorik van Havre (yorik@uncreated.net) 2014                        *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************/


'''
This is an example preprocessor file for the Path workbench. Its aim is to
open a gcode file, parse its contents, and create the appropriate objects
in FreeCAD.

Read the Path Workbench documentation to know how to create Path objects
from GCode.
'''

import os
import Path
import FreeCAD
import PathScripts.PathLog as PathLog

if False:
    PathLog.setLevel(PathLog.Level.DEBUG, PathLog.thisModule())
    PathLog.trackModule(PathLog.thisModule())
else:
    PathLog.setLevel(PathLog.Level.INFO, PathLog.thisModule())


# to distinguish python built-in open function from the one declared below
if open.__module__ in ['__builtin__','io']:
    pythonopen = open


def open(filename):
    PathLog.track(filename)
    "called when freecad opens a file."
    docname = os.path.splitext(os.path.basename(filename))[0]
    doc = FreeCAD.newDocument(docname)
    insert(filename, doc.Name)


def insert(filename, docname):
    "called when freecad imports a file"
    PathLog.track(filename)
    gfile = pythonopen(filename)
    gcode = gfile.read()
    gfile.close()
    gcode = parse(gcode)
    doc = FreeCAD.getDocument(docname)
    obj = doc.addObject("Path::Feature", "Path")
    path = Path.Path(gcode)
    obj.Path = path

def parse(inputstring):
    "parse(inputstring): returns a parsed output string"
    print("preprocessing...")
    print(inputstring)
    PathLog.track(inputstring)
    # split the input by line
    lines = inputstring.split("\n")
    output = ""
    lastcommand = None
    print (lines)

    for l in lines:
        # remove any leftover trailing and preceding spaces
        l = l.strip()
        if not l:
            # discard empty lines
            continue
        if l[0].upper() in ["N"]:
            # remove line numbers
            l = l.split(" ",1)
            if len(l)>=1:
                l = l[1]
            else:
                continue


        if l[0] in ["(","%","#",";"]:
            # discard comment and other non strictly gcode lines
            continue
        if l[0].upper() in ["G","M"]:
            # found a G or M command: we store it
            output += l + "\n"
            last = l[0].upper()
            for c in l[1:]:
                if not c.isdigit():
                    break
                else:
                    last += c
            lastcommand = last
        elif lastcommand:
            # no G or M command: we repeat the last one
            output += lastcommand + " " + l + "\n"

    print("done preprocessing.")
    return output


print(__name__ + " gcode preprocessor loaded.")
