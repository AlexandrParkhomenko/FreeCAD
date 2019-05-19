include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${Python3_INCLUDE_DIRS}
    ${XercesC_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIR}
    ${PYCXX_INCLUDE_DIR}
)

    set(FreeCADBase_LIBS
        ${Python3_LIBRARIES}
        ${XercesC_LIBRARIES}
        ${Boost_LIBRARIES}
        ${ZLIB_LIBRARIES}
    )

    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
    )
    list(APPEND FreeCADBase_LIBS ${Qt5Core_LIBRARIES})
    
    list(APPEND FreeCADBase_LIBS -lstdc++fs) # filesystem
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux") #OSDEPENDENT
    list(APPEND FreeCADBase_LIBS -lutil -ldl)
endif()

generate_from_xml(BaseClassPy)
generate_from_xml(BoundBoxPy)
generate_from_xml(CoordinateSystemPy)
generate_from_xml(PersistencePy)
generate_from_xml(VectorPy)
generate_from_xml(MatrixPy)
generate_from_xml(RotationPy)
generate_from_xml(PlacementPy)
generate_from_xml(AxisPy)
generate_from_xml(UnitPy)
generate_from_xml(QuantityPy)

if(SWIG_FOUND)
    # Create the file swigpyrun.hh and then compare with the file swigpyrun.h.
    # If the files are different or if swigpyrun.h doesn't exist then copy swigpyrun.hh.
    # This is to avoid to having to build the target each time cmake configure is executed.
    execute_process(COMMAND ${SWIG_EXECUTABLE} -python -external-runtime ${CMAKE_CURRENT_BINARY_DIR}/swigpyrun.hh)

    fc_copy_file_if_different(
        "${CMAKE_CURRENT_BINARY_DIR}/swigpyrun.hh"
        "${CMAKE_CURRENT_BINARY_DIR}/swigpyrun.h"
    )
    add_definitions(-DHAVE_SWIG=1)
endif(SWIG_FOUND)

SOURCE_GROUP("pycxx" FILES ${PYCXX_SOURCES})

SET(FreeCADBase_XML_SRCS
    AxisPy.xml
    BaseClassPy.xml
    BoundBoxPy.xml
    CoordinateSystemPy.xml
    MatrixPy.xml
    PersistencePy.xml
    PlacementPy.xml
    RotationPy.xml
    VectorPy.xml
    QuantityPy.xml
    UnitPy.xml
)
SOURCE_GROUP("XML" FILES ${FreeCADBase_XML_SRCS})

set(FreeCADBase_MOC_HDRS
#    Debugger.h
    FutureWatcherProgress.h
)

fc_wrap_cpp(FreeCADBase_MOC_SRCS ${FreeCADBase_MOC_HDRS})

SET(FreeCADBase_UNITAPI_SRCS
    UnitsApi.cpp
    UnitsApiPy.cpp
    UnitsApi.h
    UnitsSchema.h
    UnitsSchema.cpp
    UnitsSchemaInternal.h
    UnitsSchemaInternal.cpp
    UnitsSchemaMKS.h
    UnitsSchemaMKS.cpp
    UnitsSchemaImperial1.h
    UnitsSchemaImperial1.cpp
    UnitsSchemaCentimeters.h
    UnitsSchemaCentimeters.cpp
    UnitsSchemaMmMin.h
    UnitsSchemaMmMin.cpp
    Quantity.h
    Quantity.cpp
    QuantityPyImp.cpp
    QuantityParser.l
    QuantityParser.y
    Unit.h
    Unit.cpp
    UnitPyImp.cpp
    
)
SOURCE_GROUP("Units" FILES ${FreeCADBase_UNITAPI_SRCS})

SET(SWIG_SRCS
    swigpyrun.cpp
)

SET(FreeCADBase_CPP_SRCS
    Axis.cpp
    AxisPyImp.cpp
    BaseClass.cpp
    BaseClassPyImp.cpp
    BoundBoxPyImp.cpp
    Builder3D.cpp
    Console.cpp
    CoordinateSystem.cpp
    CoordinateSystemPyImp.cpp
#    Debugger.cpp
    Exception.cpp
    ExceptionFactory.cpp
    Factory.cpp
    FileInfo.cpp
    FileTemplate.cpp
    FutureWatcherProgress.cpp
#    gzstream.cpp
#    gzstream.h
    GeometryPyCXX.cpp
    Handle.cpp
    InputSource.cpp
    Interpreter.cpp
    Matrix.cpp
    MatrixPyImp.cpp
    Parameter.cpp
    ParameterPy.cpp
    Persistence.cpp
    PersistencePyImp.cpp
    Placement.cpp
    PlacementPyImp.cpp
    PyExport.cpp
    PyObjectBase.cpp
    Reader.cpp
    Rotation.cpp
    RotationPyImp.cpp
    Sequencer.cpp
    Stream.cpp
    Swap.cpp
    ${SWIG_SRCS}
    TimeInfo.cpp
    Tools.cpp
    Tools2D.cpp
    Translate.cpp
    Type.cpp
    Uuid.cpp
    Vector3D.cpp
    VectorPyImp.cpp
    ViewProj.cpp
    Writer.cpp
    XMLTools.cpp
)

SET(SWIG_HEADERS
    swigpyrun.inl
)

SET(FreeCADBase_HPP_SRCS
    Axis.h
    BaseClass.h
    BoundBox.h
    Builder3D.h
    Console.h
    CoordinateSystem.h
#    Debugger.h
    Exception.h
    ExceptionFactory.h
    Factory.h
    FileInfo.h
    FileTemplate.h
    FutureWatcherProgress.h
#    fdstream.hpp
#    gzstream.h
    GeometryPyCXX.h
    Handle.h
    InputSource.h
    Interpreter.h
    Matrix.h
    Observer.h
    Parameter.h
    Persistence.h
    Placement.h
    PyExport.h
    PyObjectBase.h
    Reader.h
    Rotation.h
    Sequencer.h
    Stream.h
    Swap.h
    ${SWIG_HEADERS}
    TimeInfo.h
    Tools.h
    Tools2D.h
    Translate.h
    Type.h
    Uuid.h
    Vector3D.h
    ViewProj.h
    Writer.h
    XMLTools.h
)

SET(FreeCADBase_SRCS
    ${PYCXX_SOURCES}
    ${FreeCADBase_CPP_SRCS}
    ${FreeCADBase_HPP_SRCS}
    ${FreeCADBase_XML_SRCS}
    ${FreeCADBase_UNITAPI_SRCS}
    PyTools.c
    PyTools.h
)

add_library(FreeCADBase SHARED ${FreeCADBase_SRCS})

target_link_libraries(FreeCADBase ${FreeCADBase_LIBS})

SET_BIN_DIR(FreeCADBase FreeCADBase)

INSTALL(TARGETS FreeCADBase
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
