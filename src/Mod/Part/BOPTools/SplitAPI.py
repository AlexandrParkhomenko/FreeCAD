################################################################################
#  Copyright (c) Victor Titov (DeepSOIC)
#  (vv.titov@gmail.com) 2016
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
__title__="BOPTools.SplitAPI module"
__author__ = "DeepSOIC"
__doc__ = "Split functions that operate on list_of_shapes."

import Part
from . import ShapeMerge
from .GeneralFuseResult import GeneralFuseResult
from . import Utils
import FreeCAD

def booleanFragments(list_of_shapes, mode, tolerance = 0.0):
    """booleanFragments(list_of_shapes, mode, tolerance = 0.0): functional part of
    BooleanFragments feature. It's just result of generalFuse plus a bit of
    post-processing.

    mode is a string. It can be "Standard", "Split" or "CompSolid".
    "Standard" - return generalFuse as is.
    "Split" - wires and shells will be split at intersections.
    "CompSolid" - solids will be extracted from result of generelFuse, and compsolids will
    be made from them; all other stuff is discarded."""

    pieces, map = list_of_shapes[0].generalFuse(list_of_shapes[1:], tolerance)
    if mode == "Standard":
        return pieces
    elif mode == "CompSolid":
        solids = pieces.Solids
        if len(solids) < 1:
            raise ValueError("No solids in the result. Can't make CompSolid.")
        elif len(solids) == 1:
            FreeCAD.Console.PrintWarning("Part_BooleanFragments: only one solid in the result, generating trivial compsolid.")
        return ShapeMerge.mergeSolids(solids, bool_compsolid= True)
    elif mode == "Split":
        gr = GeneralFuseResult(list_of_shapes, (pieces,map))
        gr.splitAggregates()
        return Part.Compound(gr.pieces)
    else:
        raise ValueError("Unknown mode: {mode}".format(mode= mode))

def slice(base_shape, tool_shapes, mode, tolerance = 0.0):
    """slice(base_shape, tool_shapes, mode, tolerance = 0.0): functional part of
    Slice feature. Splits base_shape into pieces based on intersections with tool_shapes.

    mode is a string. It can be "Standard", "Split" or "CompSolid".
    "Standard" - return like generalFuse: edges, faces and solids are split, but wires,
    shells, compsolids get extra segments but remain in one piece.
    "Split" - wires and shells will be split at intersections, too.
    "CompSolid" - slice a solid and glue it back together to make a compsolid"""

    shapes = [base_shape] + [Part.Compound([tool_shape]) for tool_shape in tool_shapes] # hack: putting tools into compounds will prevent contamination of result with pieces of tools
    if len(shapes) < 2:
        raise ValueError("No slicing objects supplied!")
    pieces, map = shapes[0].generalFuse(shapes[1:], tolerance)
    gr = GeneralFuseResult(shapes, (pieces,map))
    if mode == "Standard":
        result = gr.piecesFromSource(shapes[0])
    elif mode == "CompSolid":
        solids = Part.Compound(gr.piecesFromSource(shapes[0])).Solids
        if len(solids) < 1:
            raise ValueError("No solids in the result. Can't make compsolid.")
        elif len(solids) == 1:
            FreeCAD.Console.PrintWarning("Part_Slice: only one solid in the result, generating trivial compsolid.")
        result = ShapeMerge.mergeSolids(solids, bool_compsolid= True).childShapes()
    elif mode == "Split":
        gr.splitAggregates(gr.piecesFromSource(shapes[0]))
        result = gr.piecesFromSource(shapes[0])
    return result[0] if len(result) == 1 else Part.Compound(result)

def xor(list_of_shapes, tolerance = 0.0):
    """xor(list_of_shapes, tolerance = 0.0): boolean XOR operation."""
    list_of_shapes = Utils.upgradeToAggregateIfNeeded(list_of_shapes)
    pieces, map = list_of_shapes[0].generalFuse(list_of_shapes[1:], tolerance)
    gr = GeneralFuseResult(list_of_shapes, (pieces,map))
    gr.explodeCompounds()
    gr.splitAggregates()
    pieces_to_keep = []
    for piece in gr.pieces:
        if len(gr.sourcesOfPiece(piece)) % 2 == 1:
            pieces_to_keep.append(piece)
    return Part.Compound(pieces_to_keep)
