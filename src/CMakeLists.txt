#add_subdirectory(3rdParty) # need for mesh src/Mod/Mesh/App/Core/KDTree.cpp
if(BUILD_GUI)
    add_subdirectory(Gui)
endif(BUILD_GUI)
add_subdirectory(Base)
add_subdirectory(App)
add_subdirectory(Main)
add_subdirectory(Mod)
add_subdirectory(Ext)

