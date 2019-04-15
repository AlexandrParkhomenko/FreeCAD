add_definitions(-DHAVE_LIMITS_H -DHAVE_CONFIG_H)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-fext-numeric-literals) #fix for gcc and qt5
endif()

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${OCC_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}
    ${Python3_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${XercesC_INCLUDE_DIRS}
)
link_directories(${OCC_LIBRARY_DIR})

set(Path_LIBS
#   Robot
    Part
    area-native
    FreeCADApp
)

generate_from_xml(CommandPy)
generate_from_xml(PathPy)
generate_from_xml(ToolPy)
generate_from_xml(TooltablePy)
generate_from_xml(FeaturePathCompoundPy)
generate_from_xml(AreaPy)
generate_from_xml(FeatureAreaPy)

SET(Python_SRCS
    CommandPy.xml
    CommandPyImp.cpp
    PathPy.xml
    PathPyImp.cpp
    ToolPy.xml
    TooltablePy.xml
    TooltablePyImp.cpp
    FeaturePathCompoundPy.xml
    FeaturePathCompoundPyImp.cpp
    AreaPy.xml
    AreaPyImp.cpp
    FeatureAreaPy.xml
    FeatureAreaPyImp.cpp
)

SET(Mod_SRCS
    AppPath.cpp
    AppPathPy.cpp
)

SET(Path_SRCS
    Command.cpp
    Command.h
    Path.cpp
    Path.h
    Tooltable.cpp
    Tooltable.h
    PropertyPath.cpp
    PropertyPath.h
    FeaturePath.cpp
    FeaturePath.h
    PropertyTool.cpp
    PropertyTool.h
    PropertyTooltable.cpp
    PropertyTooltable.h
    FeaturePathCompound.cpp
    FeaturePathCompound.h
    FeaturePathShape.cpp
    FeaturePathShape.h
    Area.cpp
    Area.h
    AreaParams.h
    ParamsHelper.h
    FeatureArea.cpp
    FeatureArea.h
    ${Mod_SRCS}
    ${Python_SRCS}
)

SOURCE_GROUP("Python" FILES ${Python_SRCS})
SOURCE_GROUP("Module" FILES ${Mod_SRCS})

add_library(Path SHARED ${Path_SRCS})
target_link_libraries(Path ${Path_LIBS})

SET_BIN_DIR(Path Path /Mod/Path)
SET_PYTHON_PREFIX_SUFFIX(Path)

INSTALL(TARGETS Path DESTINATION ${CMAKE_INSTALL_LIBDIR})
