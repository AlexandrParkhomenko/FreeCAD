# FreeCAD test module
# (c) 2002 Juergen Riegel
#
# Testing the function of the base system and run
# (if existing) the test function of the modules
#

#***************************************************************************
#*   (c) Juergen Riegel (juergen.riegel@web.de) 2002                       *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
#*   Juergen Riegel 2002                                                   *
#***************************************************************************/


Log ("FreeCAD test running...\n\n")

import sys

import FreeCAD
import TestApp

testCase = FreeCAD.ConfigGet("TestCase")

testResult = TestApp.TestText(testCase)

Log ("FreeCAD test done\n")

sys.exit(0 if testResult.wasSuccessful() else 1)
