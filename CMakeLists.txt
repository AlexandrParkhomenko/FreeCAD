cmake_minimum_required(VERSION 3.12 FATAL_ERROR) #https://cmake.org/cmake/help/v3.12/module/FindPython3.html#module:FindPython3
#name
project(FreeCAD)
set(PACKAGE_VERSION_NAME "FreeCAD.0.19.Path")
configure_file(${CMAKE_SOURCE_DIR}/src/Version.h.cmake ${CMAKE_SOURCE_DIR}/src/Version.h)
#compilator
set(CMAKE_CXX_STANDARD 20) #CXX_STANDARD_REQUIRED YES  #CXX_EXTENSIONS NO
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-write-strings ${CMAKE_CXX_FLAGS}") #-Werror -Wno-deprecated -pedantic-errors
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")  # get linker errors

include(AddFileDependencies)
include(${CMAKE_SOURCE_DIR}/Macros.cmake)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Output directories for install target
SET(CMAKE_INSTALL_PREFIX "/usr/lib/freecad" CACHE PATH "Installation root directory")
SET(CMAKE_INSTALL_DATADIR data CACHE PATH "Output directory for data and resource files")
SET(CMAKE_INSTALL_INCLUDEDIR include CACHE PATH "Output directory for header files")
# Don't set it without manual adaption of LibDir variable in src/App/FreeCADInit.py
SET(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")
if(NOT IS_ABSOLUTE ${CMAKE_INSTALL_LIBDIR})
  SET(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
endif(NOT IS_ABSOLUTE ${CMAKE_INSTALL_LIBDIR})
# used as compiler defines
SET(RESOURCEDIR "${CMAKE_INSTALL_DATADIR}")

MESSAGE(STATUS "prefix: ${CMAKE_INSTALL_PREFIX}")
MESSAGE(STATUS "datadir: ${CMAKE_INSTALL_DATADIR}")
MESSAGE(STATUS "includedir: ${CMAKE_INSTALL_INCLUDEDIR}")
MESSAGE(STATUS "libdir: ${CMAKE_INSTALL_LIBDIR}")

#OPTION(BUILD_QT5_WEBKIT "Build with Qt5." OFF)
OPTION(BUILD_GUI "Build FreeCAD Gui. Otherwise you have only the command line and the Python import module." ON)
#OPTION(FREECAD_MAINTAINERS_BUILD "Build FreeCAD for Maintainers, with Docu and 3rd party libs. On Windows the Installer is built." OFF)
OPTION(FREECAD_USE_EXTERNAL_ZIPIOS "Use system installed zipios++ instead of the bundled." OFF)
OPTION(FREECAD_USE_EXTERNAL_SMESH "Use system installed smesh instead of the bundled." OFF)
#OPTION(FREECAD_USE_EXTERNAL_KDL "Use system installed orocos-kdl instead of the bundled." OFF)
#OPTION(FREECAD_USE_FREETYPE "Builds the features using FreeType libs" ON)
#OPTION(FREECAD_BUILD_DEBIAN "Prepare for a build of a Debian package" OFF)
OPTION(FREECAD_USE_QT_FILEDIALOG "Use Qt's file dialog instead of the native one." ON)

OPTION(FREECAD_USE_QTOPENGL_WIDGET "Replace QGLWidget with QOpenGLWidget." ON)
if (FREECAD_USE_QTOPENGL_WIDGET)
  set(HAVE_QT5_OPENGL 1)
endif()
configure_file(${CMAKE_SOURCE_DIR}/src/QtOpenGL.h.cmake ${CMAKE_BINARY_DIR}/src/QtOpenGL.h)

OPTION(BUILD_FEM "Build the FreeCAD FEM module" OFF)
OPTION(BUILD_SANDBOX "Build the FreeCAD Sandbox module which is only for testing purposes" OFF)
OPTION(BUILD_TEMPLATE "Build the FreeCAD template module which is only for testing purposes" OFF)
OPTION(BUILD_ADDONMGR "Build the FreeCAD addon manager module" OFF)
OPTION(BUILD_ARCH "Build the FreeCAD Architecture module" OFF)
OPTION(BUILD_ASSEMBLY "Build the FreeCAD Assembly module" OFF)
OPTION(BUILD_COMPLETE "Build the FreeCAD complete module" OFF)
OPTION(BUILD_DRAFT "Build the FreeCAD draft module" ON)
OPTION(BUILD_DRAWING "Build the FreeCAD drawing module" OFF)
OPTION(BUILD_IDF "Build the FreeCAD idf module" OFF)
OPTION(BUILD_IMAGE "Build the FreeCAD image module" OFF)
OPTION(BUILD_IMPORT "Build the FreeCAD import module" ON)
OPTION(BUILD_INSPECTION "Build the FreeCAD inspection module" OFF)
OPTION(BUILD_JTREADER "Build the FreeCAD jt reader module" OFF)
OPTION(BUILD_MATERIAL "Build the FreeCAD material module" OFF)
OPTION(BUILD_MESH "Build the FreeCAD mesh module" ON)
OPTION(BUILD_MESH_PART "Build the FreeCAD mesh part module" ON)
OPTION(BUILD_OPENSCAD "Build the FreeCAD openscad module" OFF)
OPTION(BUILD_PART "Build the FreeCAD part module" ON)
OPTION(BUILD_PART_DESIGN "Build the FreeCAD part design module" OFF)
OPTION(BUILD_PATH "Build the FreeCAD path module" ON)
OPTION(BUILD_PLOT "Build the FreeCAD plot module. Use Matplotlib!" OFF)
OPTION(BUILD_POINTS "Build the FreeCAD points module" ON)
OPTION(BUILD_RAYTRACING "Build the FreeCAD ray tracing module" OFF)
OPTION(BUILD_REVERSEENGINEERING "Build the FreeCAD reverse engineering module" OFF)
OPTION(BUILD_ROBOT "Build the FreeCAD robot module" OFF)
OPTION(BUILD_SHIP "Build the FreeCAD ship module" OFF)
OPTION(BUILD_SHOW "Build the FreeCAD Show module (helper module for visibility automation)" ON)
OPTION(BUILD_SKETCHER "Build the FreeCAD sketcher module" ON)
OPTION(BUILD_SPREADSHEET "Build the FreeCAD spreadsheet module" OFF)
OPTION(BUILD_START "Build the FreeCAD start module" OFF)
OPTION(BUILD_TEST "Build the FreeCAD test module" OFF)
OPTION(BUILD_TECHDRAW "Build the FreeCAD Technical Drawing module" OFF)
OPTION(BUILD_TUX "Build the FreeCAD Tux module" OFF)
OPTION(BUILD_WEB "Build the FreeCAD web module" OFF)
OPTION(BUILD_SURFACE "Build the FreeCAD surface module" OFF)

OPTION(FREECAD_USE_PCL "Build the features that use PCL libs" OFF)
if(FREECAD_USE_PCL)
  find_package(PCL REQUIRED COMPONENTS common kdtree features surface io filters segmentation sample_consensus) #ACHTUNG:may double kdtree
endif(FREECAD_USE_PCL)

#inter-module dependencies
# Takes a dependent module followed by a variable-length list of prerequisite
# modules.  Warns if any of the prerequisite modules are disabled.
function(REQUIRES_MODS dependent)
  if(${dependent})
    foreach(prerequisite ${ARGN})
      if(NOT ${prerequisite})
        message(WARNING
            "${dependent} requires ${ARGN} each be ON, but "
            "${prerequisite} is \"${${prerequisite}}\"")
      endif(NOT ${prerequisite})
    endforeach()
  endif(${dependent})
endfunction(REQUIRES_MODS)

REQUIRES_MODS(BUILD_ARCH         BUILD_PART BUILD_MESH BUILD_DRAFT)
REQUIRES_MODS(BUILD_DRAFT        BUILD_SKETCHER)
REQUIRES_MODS(BUILD_DRAWING      BUILD_PART BUILD_SPREADSHEET)
REQUIRES_MODS(BUILD_FEM          BUILD_PART)
REQUIRES_MODS(BUILD_IDF          BUILD_PART)
REQUIRES_MODS(BUILD_IMPORT       BUILD_PART)
REQUIRES_MODS(BUILD_INSPECTION   BUILD_MESH BUILD_POINTS BUILD_PART)
REQUIRES_MODS(BUILD_JTREADER     BUILD_MESH)
REQUIRES_MODS(BUILD_MESH_PART    BUILD_PART BUILD_MESH) # BUILD_SMESH
REQUIRES_MODS(BUILD_OPENSCAD     BUILD_MESH_PART BUILD_DRAFT)
REQUIRES_MODS(BUILD_PART_DESIGN  BUILD_SKETCHER)
REQUIRES_MODS(BUILD_PATH         BUILD_PART)# BUILD_ROBOT
REQUIRES_MODS(BUILD_RAYTRACING   BUILD_PART)
REQUIRES_MODS(BUILD_REVERSEENGINEERING BUILD_PART BUILD_MESH)
REQUIRES_MODS(BUILD_ROBOT        BUILD_PART)
REQUIRES_MODS(BUILD_SANDBOX      BUILD_PART BUILD_MESH)
REQUIRES_MODS(BUILD_SHIP         BUILD_PART BUILD_PLOT BUILD_IMAGE)
REQUIRES_MODS(BUILD_SKETCHER     BUILD_PART)
REQUIRES_MODS(BUILD_SPREADSHEET  BUILD_DRAFT)
REQUIRES_MODS(BUILD_START        BUILD_WEB)
REQUIRES_MODS(BUILD_TECHDRAW     BUILD_PART BUILD_SPREADSHEET BUILD_DRAWING)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

find_package(Boost COMPONENTS filesystem program_options regex system thread REQUIRED)
find_package(XercesC REQUIRED)
find_package(ZLIB REQUIRED)
set(PYCXX_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src" CACHE PATH "Path to the directory containing PyCXX's CXX/Config.hxx")
set(PYCXX_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/CXX" CACHE PATH "Path to the directory containing PyCXX's cxxextensions.c")
set(PYCXX_SOURCES
  ${PYCXX_SOURCE_DIR}/cxxextensions.c
  ${PYCXX_SOURCE_DIR}/cxx_extensions.cxx
  ${PYCXX_SOURCE_DIR}/cxxsupport.cxx
  ${PYCXX_SOURCE_DIR}/IndirectPythonInterface.cxx
)

find_package(OpenCASCADE REQUIRED)
set(OCC_INCLUDE_DIR ${OpenCASCADE_INCLUDE_DIR})
set(OCC_LIBRARY_DIR ${OpenCASCADE_LIBRARY_DIR})
set(OCC_LIBRARIES 
  ${OpenCASCADE_FoundationClasses_LIBRARIES}
  ${OpenCASCADE_ModelingData_LIBRARIES}
  ${OpenCASCADE_ModelingAlgorithms_LIBRARIES}
  ${OpenCASCADE_DataExchange_LIBRARIES}
  #${OpenCASCADE_Draw_LIBRARIES}
  GLESv2 EGL
)
set(OCC_OCAF_LIBRARIES ${OpenCASCADE_ApplicationFramework_LIBRARIES}) 

find_package(SWIG REQUIRED) # pivy <- Draft
find_package(Eigen3 REQUIRED)
find_package(Freetype REQUIRED)

if(BUILD_GUI)
  set(OpenGL_GL_PREFERENCE "LEGACY") # or "GLVND"
  find_package(OpenGL REQUIRED)

  find_package(Coin REQUIRED)
    set(COIN3D_INCLUDE_DIRS ${Coin_INCLUDE_DIRS})
    set(COIN3D_LIBRARIES ${Coin_LIBRARIES})
    set(COIN3D_INCLUDE_DIR ${Coin_INCLUDE_DIR})
    set(COIN3D_LIB_DIR ${Coin_LIB_DIR})
    set(COIN3D_VERSION ${Coin_VERSION})

find_package(
  Qt5 #5.12
  COMPONENTS
  Core Network Xml
  Widgets PrintSupport OpenGL Svg UiTools Concurrent
  REQUIRED
)
    # This is a special version of the built in macro qt5_wrap_cpp
    # It is required since moc'ed files are now included instead of being added to projects directly
    # It adds a reverse dependency to solve this
    # This has the unfortunate side effect that some files are always rebuilt
    # There is probably a cleaner solution than this
    macro(fc_wrap_cpp outfiles )
      # get include dirs
      qt5_get_moc_flags(moc_flags)
      set(moc_files ${ARGN})

      foreach(it ${moc_files})
        get_filename_component(it ${it} ABSOLUTE)
        qt5_make_output_file(${it} moc_ cpp outfile)
        qt5_create_moc_command(${it} ${outfile} "${moc_flags}" "${moc_options}" "${moc_target}" "${moc_depends}")
        set(${outfiles} ${${outfiles}} ${outfile})
        add_file_dependencies(${it} ${outfile})
      endforeach(it)
    endmacro(fc_wrap_cpp)

find_package(Shiboken2 REQUIRED)
find_package(PySide2 REQUIRED)
MESSAGE(STATUS "PySide2_DIR: ${PySide2_DIR}")
FIND_PROGRAM(PYSIDE2UICBINARY NAMES pyside2-uic)
FIND_PROGRAM(PYSIDE2RCCBINARY NAMES pyside2-rcc)

    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Ext/PySide)
    file(WRITE ${CMAKE_BINARY_DIR}/Ext/PySide/__init__.py "# PySide wrapper\n"
                                "from PySide2 import __version__\n"
                                "from PySide2 import __version_info__\n")
    file(WRITE ${CMAKE_BINARY_DIR}/Ext/PySide/QtCore.py "from PySide2.QtCore import *\n\n"
                              "#QCoreApplication.CodecForTr=0\n"
                              "#QCoreApplication.UnicodeUTF8=1\n")
    file(WRITE ${CMAKE_BINARY_DIR}/Ext/PySide/QtGui.py  "from PySide2.QtGui import *\n"
                              "from PySide2.QtWidgets import *\n"
                              "QHeaderView.setResizeMode = QHeaderView.setSectionResizeMode\n")
    file(WRITE ${CMAKE_BINARY_DIR}/Ext/PySide/QtSvg.py  "from PySide2.QtSvg import *\n")
    file(WRITE ${CMAKE_BINARY_DIR}/Ext/PySide/QtUiTools.py  "from PySide2.QtUiTools import *\n")

      INSTALL(
      DIRECTORY  
          ${CMAKE_BINARY_DIR}/Ext/PySide
        DESTINATION
          Ext
      )

#grep -lr PYSIDE_WRAP_RC
#Mod/Draft/CMakeLists.txt
#Tools/_TEMPLATEPY_/CMakeLists.txt
MACRO(PYSIDE_WRAP_RC outfiles)
  FOREACH(it ${ARGN})
  GET_FILENAME_COMPONENT(outfile ${it} NAME_WE)
  GET_FILENAME_COMPONENT(infile ${it} ABSOLUTE)
  SET(outfile "${CMAKE_CURRENT_BINARY_DIR}/${outfile}_rc.py")
    # Especially on Open Build Service we don't want changing date like
    # pyside-rcc generates in comments at beginning, which is why
    # we follow the tool command with in-place sed.
    ADD_CUSTOM_COMMAND(OUTPUT "${outfile}"
      COMMAND "${PYSIDE2RCCBINARY}" "${infile}" ${PY_ATTRIBUTE} -o "${outfile}"
      COMMAND sed -i "/^# /d" "${outfile}"
      MAIN_DEPENDENCY "${infile}"
    )
  list(APPEND ${outfiles} ${outfile})
  ENDFOREACH(it)
ENDMACRO (PYSIDE_WRAP_RC)

endif (BUILD_GUI)

include_directories(${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src)
add_subdirectory(src)
