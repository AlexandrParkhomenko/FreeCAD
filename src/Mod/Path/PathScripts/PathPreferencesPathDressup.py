################################################################################
#  Copyright (c) 2016 sliptonic <shopinthewoods@gmail.com>
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
from PySide2 import QtCore, QtGui, QtWidgets

# Qt translation handling
def translate(context, text, disambig=None):
    return QtCore.QCoreApplication.translate(context, text, disambig)

_dressups = []

def RegisterDressup(dressup):
    _dressups.append(dressup)

class DressupPreferencesPage:
    def __init__(self, parent=None):
        # pylint: disable=unused-argument
        self.form = QtWidgets.QToolBox()
        self.form.setWindowTitle(translate("Path_PreferencesPathDressup", 'Dressups'))
        pages = []
        for dressup in _dressups:
            page = dressup.preferencesPage()
            if hasattr(page, 'icon') and page.icon:
                self.form.addItem(page.form, page.icon, page.label)
            else:
                self.form.addItem(page.form, page.label)
            pages.append(page)
        self.pages = pages

    def saveSettings(self):
        for page in self.pages:
            page.saveSettings()

    def loadSettings(self):
        for page in self.pages:
            page.loadSettings()

