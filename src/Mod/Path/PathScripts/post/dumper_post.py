# ***************************************************************************
# *   (c) sliptonic (shopinthewoods@gmail.com) 2014                        *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************/
TOOLTIP='''
Dumper is an extremely simple postprocessor file for the Path workbench. It is used
to dump the command list from one or more Path objects for simple inspection. This post
doesn't do any manipulation of the path and doesn't write anything to disk.  It just
shows the dialog so you can see it.  Useful for debugging, but not much else.
'''
import datetime
from PathScripts import PostUtils

now = datetime.datetime.now()
SHOW_EDITOR = True

# to distinguish python built-in open function from the one declared below
if open.__module__ in ['__builtin__','io']:
    pythonopen = open


def export(objectslist, filename,argstring):
    output = '''(This output produced with the dump post processor)
(Dump is useful for inspecting the raw commands in your paths)
(but is not useful for driving machines.)
(Consider setting a default postprocessor in your project or )
(exporting your paths using a specific post that matches your machine)

'''

    "called when freecad exports a list of objects"
    for obj in objectslist:

        if not hasattr(obj, "Path"):
            print("the object " + obj.Name + " is not a path. Please select only path and Compounds.")
            return
        print("postprocessing...")
        output += parse(obj)

    if SHOW_EDITOR:
        dia = PostUtils.GCodeEditorDialog()
        dia.editor.setText(output)
        result = dia.exec_()
        if result:
            final = dia.editor.toPlainText()
        else:
            final = output
    else:
        final = output

    print("done postprocessing.")
    return final


def parse(pathobj):
    out = ""

    if hasattr(pathobj, "Group"):  # We have a compound or project.
        out += "(Group: " + pathobj.Label + ")\n"
        for p in pathobj.Group:
            out += parse(p)
        return out
    else:  # parsing simple path

        if not hasattr(pathobj, "Path"):  # groups might contain non-path things like stock.
            return out

        out += "(Path: " + pathobj.Label + ")\n"

        for c in pathobj.Path.Commands:
            out += str(c) + "\n"
        return out

print(__name__ + " gcode postprocessor loaded.")
