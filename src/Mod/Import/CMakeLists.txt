# Utilities to import various file formats using OpenCasCade OCAF

add_subdirectory(App)
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)

set(Import_Scripts
    Init.py
    gzip_utf8.py
    stepZ.py
)

if(BUILD_GUI)
    list (APPEND Import_Scripts InitGui.py)
endif(BUILD_GUI)

add_custom_target(ImportScripts ALL
    SOURCES ${Import_Scripts}
)

fc_target_copy_resource(ImportScripts
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}/Mod/Import
    ${Import_Scripts}
)

INSTALL(
    FILES
        ${Import_Scripts}
    DESTINATION
        Mod/Import
)

