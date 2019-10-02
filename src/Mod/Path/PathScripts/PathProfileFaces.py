################################################################################
#  Copyright (c) 2014 Yorik van Havre <yorik@uncreated.net>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import FreeCAD
import Part
import Path
#  import PathScripts.PathAreaOp as PathAreaOp
import PathScripts.PathLog as PathLog
import PathScripts.PathOp as PathOp
import PathScripts.PathProfileBase as PathProfileBase
import PathScripts.PathUtils as PathUtils
import numpy

#  from PathScripts.PathUtils import depth_params
from PySide2 import QtCore

__title__ = "Path Profile Faces Operation"
__author__ = "sliptonic (Brad Collette)"
__doc__ = "Path Profile operation based on faces."
__contributors__ = "russ4262 (Russell Johnson, russ4262@gmail.com)"
__created__ = "2014"
__scriptVersion__ = "2j usable"
__lastModified__ = "2019-07-25 14:48 CST"

LOGLEVEL = PathLog.Level.INFO  # change to .DEBUG to enable debugging messages
PathLog.setLevel(LOGLEVEL, PathLog.thisModule())

# Qt translation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)


class ObjectProfile(PathProfileBase.ObjectProfile):
    '''Proxy object for Profile operations based on faces.'''

    def baseObject(self):
        '''baseObject() ... returns super of receiver
        Used to call base implementation in overwritten functions.'''
        return super(self.__class__, self)

    def areaOpFeatures(self, obj):
        '''baseObject() ... returns super of receiver
        Used to call base implementation in overwritten functions.'''
        return PathOp.FeatureBaseFaces | PathOp.FeatureBasePanels

    def initAreaOp(self, obj):
        '''initAreaOp(obj) ... adds properties for hole, circle and perimeter processing.'''
        # Face specific Properties
        obj.addProperty("App::PropertyBool", "processHoles", "Profile", QtCore.QT_TRANSLATE_NOOP("App::Property", "Profile holes as well as the outline"))
        obj.addProperty("App::PropertyBool", "processPerimeter", "Profile", QtCore.QT_TRANSLATE_NOOP("App::Property", "Profile the outline"))
        obj.addProperty("App::PropertyBool", "processCircles", "Profile", QtCore.QT_TRANSLATE_NOOP("App::Property", "Profile round holes"))

        if not hasattr(obj, 'ReverseDirection'):
            obj.addProperty('App::PropertyBool', 'ReverseDirection', 'Rotation', QtCore.QT_TRANSLATE_NOOP('App::Property', 'Reverse direction of pocket operation.'))
        if not hasattr(obj, 'InverseAngle'):
            obj.addProperty('App::PropertyBool', 'InverseAngle', 'Rotation', QtCore.QT_TRANSLATE_NOOP('App::Property', 'Inverse the angle. Example: -22.5 -> 22.5 degrees.'))
        if not hasattr(obj, 'B_AxisErrorOverride'):
            obj.addProperty('App::PropertyBool', 'B_AxisErrorOverride', 'Rotation', QtCore.QT_TRANSLATE_NOOP('App::Property', 'Match B rotations to model (error in FreeCAD rendering).'))
        if not hasattr(obj, 'AttemptInverseAngle'):
            obj.addProperty('App::PropertyBool', 'AttemptInverseAngle', 'Rotation', QtCore.QT_TRANSLATE_NOOP('App::Property', 'Attempt the inverse angle for face access if original rotation fails.'))

        if not hasattr(obj, 'HandleMultipleFeatures'):
            obj.addProperty('App::PropertyEnumeration', 'HandleMultipleFeatures', 'Profile', QtCore.QT_TRANSLATE_NOOP('PathPocket', 'Choose how to process multiple Base Geometry features.'))
        obj.HandleMultipleFeatures = ['Collectively', 'Individually']

        self.baseObject().initAreaOp(obj)

    def areaOpShapes(self, obj):
        '''areaOpShapes(obj) ... returns envelope for all base shapes or wires for Arch.Panels.'''
        PathLog.track()

        if obj.UseComp:
            self.commandlist.append(Path.Command("(Compensated Tool Path. Diameter: " + str(self.radius * 2) + ")"))
        else:
            self.commandlist.append(Path.Command("(Uncompensated Tool Path)"))

        shapes = []
        self.profileshape = [] # pylint: disable=attribute-defined-outside-init

        baseSubsTuples = []
        subCount = 0
        allTuples = []

        if obj.Base:  # The user has selected subobjects from the base.  Process each.
            if obj.EnableRotation != 'Off':
                for p in range(0, len(obj.Base)):
                    (base, subsList) = obj.Base[p]
                    for sub in subsList:
                        subCount += 1
                        shape = getattr(base.Shape, sub)
                        if isinstance(shape, Part.Face):
                            rtn = False
                            (norm, surf) = self.getFaceNormAndSurf(shape)
                            (rtn, angle, axis, praInfo) = self.faceRotationAnalysis(obj, norm, surf) # pylint: disable=unused-variable
                            if rtn is True:
                                (clnBase, angle, clnStock, tag) = self.applyRotationalAnalysis(obj, base, angle, axis, subCount)
                                # Verify faces are correctly oriented - InverseAngle might be necessary
                                faceIA = getattr(clnBase.Shape, sub)
                                (norm, surf) = self.getFaceNormAndSurf(faceIA)
                                (rtn, praAngle, praAxis, praInfo) = self.faceRotationAnalysis(obj, norm, surf) # pylint: disable=unused-variable
                                if rtn is True:
                                    PathLog.error(translate("Path", "Face appears misaligned after initial rotation."))
                                    if obj.AttemptInverseAngle is True and obj.InverseAngle is False:
                                        (clnBase, clnStock, angle) = self.applyInverseAngle(obj, clnBase, clnStock, axis, angle)
                                    else:
                                        msg = translate("Path", "Consider toggling the 'InverseAngle' property and recomputing.")
                                        PathLog.error(msg)
                                else:
                                    PathLog.debug("Face appears to be oriented correctly.")

                                tup = clnBase, sub, tag, angle, axis, clnStock
                            else:
                                if self.warnDisabledAxis(obj, axis) is False:
                                    PathLog.debug(str(sub) + ": No rotation used")
                                axis = 'X'
                                angle = 0.0
                                tag = base.Name + '_' + axis + str(angle).replace('.', '_')
                                stock = PathUtils.findParentJob(obj).Stock
                                tup = base, sub, tag, angle, axis, stock
                            allTuples.append(tup)
                if subCount > 1:
                    msg = translate('Path', "Multiple faces in Base Geometry.") + "  "
                    msg += translate('Path', "Depth settings will be applied to all faces.")
                    PathLog.warning(msg)
                (Tags, Grps) = self.sortTuplesByIndex(allTuples, 2)  # return (TagList, GroupList)
                subList = []
                for o in range(0, len(Tags)):
                    subList = []
                    for (base, sub, tag, angle, axis, stock) in Grps[o]:
                        subList.append(sub)
                    pair = base, subList, angle, axis, stock
                    baseSubsTuples.append(pair)
                # Efor
            else:
                PathLog.debug(translate("Path", "EnableRotation property is 'Off'."))
                stock = PathUtils.findParentJob(obj).Stock
                for (base, subList) in obj.Base:
                    baseSubsTuples.append((base, subList, 0.0, 'X', stock))

            # for base in obj.Base:
            finish_step = obj.FinishDepth.Value if hasattr(obj, "FinishDepth") else 0.0
            for (base, subsList, angle, axis, stock) in baseSubsTuples:
                holes = []
                faces = []
                faceDepths = []
                startDepths = []

                for sub in subsList:
                    shape = getattr(base.Shape, sub)
                    if isinstance(shape, Part.Face):
                        faces.append(shape)
                        if numpy.isclose(abs(shape.normalAt(0, 0).z), 1):  # horizontal face
                            for wire in shape.Wires[1:]:
                                holes.append((base.Shape, wire))
                        # Add face depth to list
                        faceDepths.append(shape.BoundBox.ZMin)
                    else:
                        ignoreSub = base.Name + '.' + sub
                        msg = translate('Path', "Found a selected object which is not a face. Ignoring: {}".format(ignoreSub))
                        PathLog.error(msg)
                        FreeCAD.Console.PrintWarning(msg)

                # Raise FinalDepth to lowest face in list on Inside profile ops
                finDep = obj.FinalDepth.Value

                strDep = obj.StartDepth.Value
                if strDep > stock.Shape.BoundBox.ZMax:
                    strDep = stock.Shape.BoundBox.ZMax
                startDepths.append(strDep)

                # Recalculate depthparams
                self.depthparams = PathUtils.depth_params( # pylint: disable=attribute-defined-outside-init
                    clearance_height=obj.ClearanceHeight.Value,
                    safe_height=obj.SafeHeight.Value,
                    start_depth=strDep,  # obj.StartDepth.Value,
                    step_down=obj.StepDown.Value,
                    z_finish_step=finish_step,
                    final_depth=finDep,  # obj.FinalDepth.Value,
                    user_depths=None)

                for shape, wire in holes:
                    f = Part.makeFace(wire, 'Part::FaceMakerSimple')
                    drillable = PathUtils.isDrillable(shape, wire)
                    if (drillable and obj.processCircles) or (not drillable and obj.processHoles):
                        env = PathUtils.getEnvelope(shape, subshape=f, depthparams=self.depthparams)
                        tup = env, True, 'pathProfileFaces', angle, axis, strDep, finDep
                        shapes.append(tup)

                if len(faces) > 0:
                    profileshape = Part.makeCompound(faces)
                    self.profileshape.append(profileshape)

                if obj.processPerimeter:
                    if obj.HandleMultipleFeatures == 'Collectively':
                        try:
                            env = PathUtils.getEnvelope(base.Shape, subshape=profileshape, depthparams=self.depthparams)
                        except Exception: # pylint: disable=broad-except
                            # PathUtils.getEnvelope() failed to return an object.
                            PathLog.error(translate('Path', 'Unable to create path for face(s).'))
                        else:
                            tup = env, False, 'pathProfileFaces', angle, axis, strDep, finDep
                            shapes.append(tup)
                    elif obj.HandleMultipleFeatures == 'Individually':
                        for shape in faces:
                            profShape = Part.makeCompound([shape])
                            finalDep = obj.FinalDepth.Value
                            custDepthparams = self.depthparams
                            if obj.Side == 'Inside':
                                if finalDep < shape.BoundBox.ZMin:
                                    # Recalculate depthparams
                                    finalDep = shape.BoundBox.ZMin
                                    custDepthparams = PathUtils.depth_params(
                                        clearance_height=obj.ClearanceHeight.Value,
                                        safe_height=obj.SafeHeight.Value,
                                        start_depth=strDep,  # obj.StartDepth.Value,
                                        step_down=obj.StepDown.Value,
                                        z_finish_step=finish_step,
                                        final_depth=finalDep,  # obj.FinalDepth.Value,
                                        user_depths=None)
                            env = PathUtils.getEnvelope(base.Shape, subshape=profShape, depthparams=custDepthparams)
                            tup = env, False, 'pathProfileFaces', angle, axis, strDep, finalDep
                            shapes.append(tup)

            # Lower high Start Depth to top of Stock
            startDepth = max(startDepths)
            if obj.StartDepth.Value > startDepth:
                obj.StartDepth.Value = startDepth
        else:  # Try to build targets from the job base
            if 1 == len(self.model):
                if hasattr(self.model[0], "Proxy"):
                    PathLog.info("hasattr() Proxy")

        self.removalshapes = shapes # pylint: disable=attribute-defined-outside-init
        PathLog.debug("%d shapes" % len(shapes))
        return shapes

    def areaOpSetDefaultValues(self, obj, job):
        '''areaOpSetDefaultValues(obj, job) ... sets default values for hole, circle and perimeter processing.'''
        self.baseObject().areaOpSetDefaultValues(obj, job)

        obj.processHoles = False
        obj.processCircles = False
        obj.processPerimeter = True
        obj.ReverseDirection = False
        obj.InverseAngle = False
        obj.AttemptInverseAngle = True
        obj.B_AxisErrorOverride = False
        obj.HandleMultipleFeatures = 'Collectively'


def SetupProperties():
    setup = PathProfileBase.SetupProperties()
    setup.append("processHoles")
    setup.append("processPerimeter")
    setup.append("processCircles")
    setup.append("ReverseDirection")
    setup.append("InverseAngle")
    setup.append("B_AxisErrorOverride")
    setup.append("AttemptInverseAngle")
    setup.append("HandleMultipleFeatures")
    return setup


def Create(name, obj=None):
    '''Create(name) ... Creates and returns a Profile based on faces operation.'''
    if obj is None:
        obj = FreeCAD.ActiveDocument.addObject("Path::FeaturePython", name)
    obj.Proxy = ObjectProfile(obj, name)
    return obj
