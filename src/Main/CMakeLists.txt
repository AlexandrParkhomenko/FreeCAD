    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5OpenGL_INCLUDE_DIRS}
#        ${Qt5PrintSupport_INCLUDE_DIRS}
        ${Qt5Svg_INCLUDE_DIRS}
#        ${Qt5Network_INCLUDE_DIRS}
        ${Qt5UiTools_INCLUDE_DIRS}
    )
    list(APPEND FreeCAD_LIBS
        ${Qt5Core_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5OpenGL_LIBRARIES}
 #       ${Qt5PrintSupport_LIBRARIES}
        ${Qt5Svg_LIBRARIES}
 #       ${Qt5Network_LIBRARIES}
        ${Qt5UiTools_LIBRARIES}
    )


if(BUILD_GUI)
    include_directories(
        ${Boost_INCLUDE_DIRS}
        ${COIN3D_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIR}
        ${Python3_INCLUDE_DIRS}
        ${XercesC_INCLUDE_DIRS}
    )
else(BUILD_GUI)
    include_directories(
        ${Boost_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIR}
        ${Python3_INCLUDE_DIRS}
        ${XercesC_INCLUDE_DIRS}
    )
endif(BUILD_GUI)

######################## FreeCADMain ########################
if(BUILD_GUI)

    SET(FreeCAD_SRCS
        MainGui.cpp
    )

    SET(FreeCAD_LIBS
        FreeCADGui
    )

    add_executable(FreeCADMain ${FreeCAD_SRCS})
    target_link_libraries(FreeCADMain ${FreeCAD_LIBS})

    SET_BIN_DIR(FreeCADMain FreeCAD)

        INSTALL(TARGETS FreeCADMain 
            RUNTIME DESTINATION bin
        )
endif(BUILD_GUI)
######################## FreeCADMainCmd ########################

SET(FreeCADMainCmd_SRCS
    MainCmd.cpp
)
add_executable(FreeCADMainCmd ${FreeCADMainCmd_SRCS})

SET(FreeCADMainCmd_LIBS
    FreeCADApp
)

    list(APPEND FreeCADMainCmd_LIBS
        ${Qt5Core_LIBRARIES}
        ${Qt5Xml_LIBRARIES}
    )

target_link_libraries(FreeCADMainCmd 
    ${FreeCADMainCmd_LIBS}
)

SET_BIN_DIR(FreeCADMainCmd FreeCADCmd)

    INSTALL(TARGETS FreeCADMainCmd 
        RUNTIME DESTINATION bin
    )

######################## FreeCADMainPy ########################

SET(FreeCADMainPy_SRCS
    MainPy.cpp
)

add_library(FreeCADMainPy SHARED ${FreeCADMainPy_SRCS})

target_link_libraries(FreeCADMainPy FreeCADApp)

SET_BIN_DIR(FreeCADMainPy FreeCAD)
SET_PYTHON_PREFIX_SUFFIX(FreeCADMainPy)

    INSTALL(TARGETS FreeCADMainPy
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

######################## FreeCADGuiPy ########################
if(BUILD_GUI)

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
endif(BUILD_GUI)
