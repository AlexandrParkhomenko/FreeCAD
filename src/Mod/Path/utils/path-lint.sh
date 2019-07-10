#!/bin/bash
#
# ***************************************************************************
# *                                                                         *
# *   Copyright (c) 2017 sliptonic <shopinthewoods@gmail.com>               *
#*   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
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

EXTERNAL_MODULES+=' Draft'
EXTERNAL_MODULES+=' DraftGeomUtils'
EXTERNAL_MODULES+=' DraftVecUtils'
EXTERNAL_MODULES+=' FreeCAD'
EXTERNAL_MODULES+=' FreeCADGui'
EXTERNAL_MODULES+=' Mesh'
EXTERNAL_MODULES+=' MeshPart'
EXTERNAL_MODULES+=' Part'
EXTERNAL_MODULES+=' Path'
EXTERNAL_MODULES+=' PySide.QtCore'
EXTERNAL_MODULES+=' PySide.QtGui'
EXTERNAL_MODULES+=' importlib'

ARGS+=" --errors-only"
ARGS+=" --ignored-modules=$(echo ${EXTERNAL_MODULES} | tr ' ' ',')"
ARGS+=" --jobs=4"

if [ -z "$(which pylint)" ]; then
  echo "Cannot find pylint, please install and try again!"
  exit 1
fi

#pylint ${ARGS} PathScripts/ PathTests/
pylint ${ARGS} PathScripts/
