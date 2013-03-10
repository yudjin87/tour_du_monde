cmake_minimum_required(VERSION 2.8)

###############################################################################
# This is a top-level solution folder that groups
# concrete projects together
project(testingLibraries CXX)

###############################################################################
# Add concrete projects to the group
add_subdirectory(exportBothFuncs)
add_subdirectory(exportCreateFuncOnly)
add_subdirectory(exportDelFuncOnly)
add_subdirectory(testComponent1)
add_subdirectory(testComponent2)

###############################################################################
# Specify dependencies for correct build order
add_dependencies(exportBothFuncs ComponentSystem)
add_dependencies(exportCreateFuncOnly ComponentSystem)
add_dependencies(exportDelFuncOnly ComponentSystem)
add_dependencies(TestComponent1 ComponentSystem)
add_dependencies(TestComponent2 ComponentSystem)

###############################################################################
# Organize projects into folders/filters (for MSVC, xCode)
set_property(TARGET exportBothFuncs PROPERTY FOLDER "tests/libs")
set_property(TARGET exportCreateFuncOnly PROPERTY FOLDER "tests/libs")
set_property(TARGET exportDelFuncOnly PROPERTY FOLDER "tests/libs")
set_property(TARGET TestComponent1 PROPERTY FOLDER "tests/components")
set_property(TARGET TestComponent2 PROPERTY FOLDER "tests/components")

