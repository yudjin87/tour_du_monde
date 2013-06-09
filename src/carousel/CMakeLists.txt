###############################################################################
# Add concrete projects to the group
add_subdirectory(booting)
add_subdirectory(componentsystem)
add_subdirectory(framework)
add_subdirectory(logging)
add_subdirectory(utils)

###############################################################################
# Specify dependencies for correct build order
add_dependencies(Booting Logging Utils ComponentSystem)
add_dependencies(ComponentSystem Logging Utils)
add_dependencies(Framework ComponentSystem)

###############################################################################
# Organize projects into folders/filters (for MSVC, xCode)
set_property(TARGET Booting PROPERTY FOLDER "src/carousel")
set_property(TARGET ComponentSystem PROPERTY FOLDER "src/carousel")
set_property(TARGET Framework PROPERTY FOLDER "src/carousel")
set_property(TARGET Logging PROPERTY FOLDER "src/carousel")
set_property(TARGET Utils PROPERTY FOLDER "src/carousel")
