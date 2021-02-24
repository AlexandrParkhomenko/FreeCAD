include_directories(
  ${Boost_INCLUDE_DIRS}
  ${COIN3D_INCLUDE_DIRS} #//GUI
  ${Python3_INCLUDE_DIRS}
  ${XercesC_INCLUDE_DIRS}
  ${ZLIB_INCLUDE_DIR}
  
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5OpenGL_INCLUDE_DIRS}
# ${Qt5PrintSupport_INCLUDE_DIRS}
  ${Qt5Svg_INCLUDE_DIRS}
# ${Qt5Network_INCLUDE_DIRS}
  ${Qt5UiTools_INCLUDE_DIRS}
)
list(APPEND FreeCAD_LIBS
  ${Qt5Core_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
  ${Qt5OpenGL_LIBRARIES}
# ${Qt5PrintSupport_LIBRARIES}
  ${Qt5Svg_LIBRARIES}
# ${Qt5Network_LIBRARIES}
  ${Qt5UiTools_LIBRARIES}
)


SET(FreeCADMainCmd_SRCS
    MainCmd.cpp
)
SET(FreeCADMainCmd_LIBS
    FreeCADApp
)
list(APPEND FreeCADMainCmd_LIBS
  ${Qt5Core_LIBRARIES}
  ${Qt5Xml_LIBRARIES}
)
add_executable(FreeCADMainCmd ${FreeCADMainCmd_SRCS})
target_link_libraries(FreeCADMainCmd ${FreeCADMainCmd_LIBS})
SET_BIN_DIR(FreeCADMainCmd "freecad-path-cmd")
INSTALL(TARGETS FreeCADMainCmd 
  RUNTIME DESTINATION bin
)

SET(FreeCADMainPy_SRCS
  MainPy.cpp
)
add_library(FreeCADMainPy SHARED ${FreeCADMainPy_SRCS})
target_link_libraries(FreeCADMainPy FreeCADApp)
SET_BIN_DIR(FreeCADMainPy "freecad-path")
SET_PYTHON_PREFIX_SUFFIX(FreeCADMainPy)
INSTALL(TARGETS FreeCADMainPy
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#GUI v
SET(FreeCAD_SRCS
  MainGui.cpp
)
SET(FreeCAD_LIBS
  FreeCADGui
)
add_executable(FreeCADMain ${FreeCAD_SRCS})
target_link_libraries(FreeCADMain ${FreeCAD_LIBS})
SET_BIN_DIR(FreeCADMain "freecad-path")
INSTALL(TARGETS FreeCADMain 
  RUNTIME DESTINATION bin
)

SET(FreeCADGuiPy_SRCS
  FreeCADGuiPy.cpp
)
add_library(FreeCADGuiPy SHARED ${FreeCADGuiPy_SRCS})
target_link_libraries(FreeCADGuiPy FreeCADGui)
SET_BIN_DIR(FreeCADGuiPy FreeCADGui)
SET_PYTHON_PREFIX_SUFFIX(FreeCADGuiPy)
INSTALL(TARGETS FreeCADGuiPy
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
