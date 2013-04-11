###############################################################################
# This is a top-level solution folder that groups
# concrete projects together
project(sources CXX)

###############################################################################
# Add concrete projects to the group
add_subdirectory(booting)
add_subdirectory(componentsystem)
add_subdirectory(componentsystemui)
add_subdirectory(framework)
add_subdirectory(interactivity)
add_subdirectory(logging)
add_subdirectory(utils)

###############################################################################
# Specify dependencies for correct build order
add_dependencies(Booting Logging Utils ComponentSystem)
add_dependencies(Interactivity Logging Utils ComponentSystem)
add_dependencies(ComponentSystem Logging Utils)

###############################################################################
# Organize projects into folders/filters (for MSVC, xCode)
set_property(TARGET Booting PROPERTY FOLDER "src")
set_property(TARGET ComponentSystem PROPERTY FOLDER "src")
set_property(TARGET ComponentSystemUI PROPERTY FOLDER "src")
set_property(TARGET Framework PROPERTY FOLDER "src")
set_property(TARGET Interactivity PROPERTY FOLDER "src")
set_property(TARGET Logging PROPERTY FOLDER "src")
set_property(TARGET Utils PROPERTY FOLDER "src")
