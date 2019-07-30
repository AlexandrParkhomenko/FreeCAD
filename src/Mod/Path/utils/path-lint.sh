#!/bin/bash
#
# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>               *
# *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
# ***************************************************************************

# Script to run pylint on Path. Currently only checks for errors.

if [ 'utils' == $(basename ${PWD}) ]; then
  cd ..
elif [ 'PathScripts' == $(basename ${PWD}) ]; then
  cd ..
elif [ 'PathTests' == $(basename ${PWD}) ]; then
  cd ..
elif [ -d 'src/Mod/Path' ]; then
  cd src/Mod/Path
elif [ -d 'Mod/Path' ]; then
  cd Mod/Path
elif [ -d 'Path' ]; then
  cd Path
fi

if [ ! -d 'PathScripts' ]; then
  echo "Cannot determine source directory, please call from within Path source directory."
  exit 2
fi

#EXTERNAL_MODULES+=' ArchPanel'
EXTERNAL_MODULES+=' Draft'
EXTERNAL_MODULES+=' DraftGeomUtils'
EXTERNAL_MODULES+=' DraftVecUtils'
EXTERNAL_MODULES+=' FreeCAD'
EXTERNAL_MODULES+=' FreeCADGui'
EXTERNAL_MODULES+=' Mesh'
EXTERNAL_MODULES+=' MeshPart'
EXTERNAL_MODULES+=' Part'
EXTERNAL_MODULES+=' Path'
EXTERNAL_MODULES+=' PySide'
EXTERNAL_MODULES+=' PySide.QtCore'
EXTERNAL_MODULES+=' PySide.QtGui'
#EXTERNAL_MODULES+=' TechDraw'
EXTERNAL_MODULES+=' TestSketcherApp'
EXTERNAL_MODULES+=' area'
EXTERNAL_MODULES+=' importlib'
EXTERNAL_MODULES+=' ocl'
EXTERNAL_MODULES+=' pivy'

IGNORE_MODULES+=' grbl_post.py'
IGNORE_MODULES+=' PathSimulatorGui.py'
IGNORE_MODULES+=' PathSurface.py'

#ARGS+=" --errors-only"
ARGS+=" --disable=C,R"
ARGS+=" --ignored-modules=$(echo ${EXTERNAL_MODULES} | tr ' ' ',')"
if [ -n "${IGNORE_MODULES}" ]; then
  ARGS+=" --ignore=$(echo ${IGNORE_MODULES} | tr ' ' ',')"
fi
ARGS+=" --jobs=0"

if [ -z "$(which pylint3)" ]; then
  echo "Cannot find pylint, please install and try again!"
  exit 1
fi

pylint3 ${ARGS} PathScripts/ PathTests/
#pylint3 ${ARGS} PathScripts/
#pylint3 ${ARGS} PathTests/

