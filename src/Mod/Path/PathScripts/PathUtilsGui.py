################################################################################
#  Copyright (c) 2019 sliptonic <shopinthewoods@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import FreeCADGui
import PathScripts
import PathScripts.PathJobCmd as PathJobCmd
import PathScripts.PathUtils as PathUtils

class PathUtilsUserInput(object):

    def selectedToolController(self):
        tc = None
        # check if a user has selected a tool controller in the tree.
        # Return the first one and remove all from selection
        for sel in FreeCADGui.Selection.getSelectionEx():
            if hasattr(sel.Object, 'Proxy'):
                if isinstance(sel.Object.Proxy, PathScripts.PathToolController.ToolController):
                    if tc is None:
                        tc = sel.Object
                    FreeCADGui.Selection.removeSelection(sel.Object)
        return tc

    def chooseToolController(self, controllers):
        form = FreeCADGui.PySideUic.loadUi(":/panels/DlgTCChooser.ui")
        mylist = [i.Label for i in controllers]
        form.uiToolController.addItems(mylist)
        r = form.exec_()
        if not r:
            return None
        return [i for i in controllers if i.Label == form.uiToolController.currentText()][0]

    def chooseJob(self, jobs):
        job = None
        selected = FreeCADGui.Selection.getSelection()
        if 1 == len(selected) and selected[0] in jobs:
            job = selected[0]
        else:
            modelSelected = []
            for job in jobs:
                if all([o in job.Model.Group for o in selected]):
                    modelSelected.append(job)
            if 1 == len(modelSelected):
                job = modelSelected[0]
            else:
                modelObjectSelected = []
                for job in jobs:
                    if all([o in job.Proxy.baseObjects(job) for o in selected]):
                        modelObjectSelected.append(job)
                if 1 == len(modelObjectSelected):
                    job = modelObjectSelected[0]
                else:
                    form = FreeCADGui.PySideUic.loadUi(":/panels/DlgJobChooser.ui")
                    if modelObjectSelected:
                        mylist = [j.Label for j in modelObjectSelected]
                    else:
                        mylist = [j.Label for j in jobs]
                    form.cboProject.addItems(mylist)
                    r = form.exec_()
                    if r is False or r == 0:
                        return None
                    else:
                        job = [j for j in jobs if j.Label == form.cboProject.currentText()][0]
        return job

    def createJob(self):
        return PathJobCmd.CommandJobCreate().Activated()


PathUtils.UserInput = PathUtilsUserInput()

