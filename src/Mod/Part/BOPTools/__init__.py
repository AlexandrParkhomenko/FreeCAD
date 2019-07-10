#/***************************************************************************
# *   Copyright (c) Victor Titov (DeepSOIC)                                 *
# *                                           (vv.titov@gmail.com) 2016     *
# *                                                                         *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************/

__title__ = "BOPTools package"
__doc__ = """BOPTools Package (part of FreeCAD). Routines that power Connect, Embed, Cutout,
BooleanFragments, Slice and XOR features of Part Workbench. Useful for other custom
BOP-like operations"""

## @package BOPTools
#  \ingroup PART

__all__ = [
"GeneralFuseResult",
"JoinAPI",
"JoinFeatures",
"ShapeMerge",
"Utils",
"SplitAPI",
"SplitFeatures",
]

def importAll():
    "importAll(): imports all modules of BOPTools package"
    from . import GeneralFuseResult
    from . import JoinAPI
    from . import JoinFeatures
    from . import ShapeMerge
    from . import Utils
    from . import SplitAPI
    from . import SplitFeatures

def reloadAll():
    "reloadAll(): reloads all modules of BOPTools package. Useful for debugging."
    for modstr in __all__:
        reload(globals()[modstr])
    import FreeCAD
    if FreeCAD.GuiUp:
        addCommands()

def addCommands():
    "addCommands(): add all GUI commands of BOPTools package to FreeCAD command manager."
    JoinFeatures.addCommands()
    SplitFeatures.addCommands()

def generalFuseIsAvailable():
    """generalFuseIsAvailable(): returns True if FreeCAD's Part.Shape.generalFuse is functional.
    True if Part.OCC_VERSION >= 6.9.0."""
    import Part
    if not hasattr(Part, "OCC_VERSION"):
        return False
    else:
        ver_string = Part.OCC_VERSION
        import re
        match = re.match(r"([0-9]+)\.([0-9]+)\.([0-9]+)",ver_string)
        major,minor,rev = match.groups()
        major = int(major); minor = int(minor); rev = int(rev)
        return (major,minor,rev)>=(6,9,0)
