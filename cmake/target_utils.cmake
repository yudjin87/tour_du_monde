###############################################################################
# This module defines and exports (when is included) useful variables for the
# target, and adjust some routines.
# It bases on the CRSL_PROJECT_NAME variable.

###############################################################################
# Sets the name of the project with C++ supporting.
string(TOLOWER ${CRSL_PROJECT_NAME} PROJECT_NAME_LOWER)
project(${CRSL_PROJECT_NAME} CXX)

###############################################################################
# Defines pathes to the directories with target's header and source files.
set(CRSL_TARGET_SOURCES ${CPP_SOURCE_TREE}/${PROJECT_NAME_LOWER})
set(CRSL_TARGET_HEADERS ${HPP_SOURCE_TREE}/${PROJECT_NAME_LOWER})

###############################################################################
# Adds the target's headers location to the include path
# and also adds the 'carousel/include' directory to the path.
include_directories(${HPP_SOURCE_TREE})
include_directories(${CRSL_TARGET_HEADERS})

###############################################################################
# Adds preprocessor definition for the symbols exporting.
string(TOUPPER ${CRSL_PROJECT_NAME} PROJECT_NAME_UPPER)
add_definitions(-D${PROJECT_NAME_UPPER}_LIBRARY)

macro(crsl_setup_output_path __PREFIX)
  crsl_use_default_project_output_path(${CRSL_PROJECT_NAME} ${CAROUSEL_WD} ${CRSL_TARGET_OS} ${CRSL_TARGET_PLATFORM_BITS} ${CMAKE_BUILD_TYPE} ${__PREFIX})
endmacro(crsl_setup_output_path)
