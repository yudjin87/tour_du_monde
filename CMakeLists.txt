###############################################################################
# Read the BUILD.txt to generate MSVC/Xcode solutions using cmake.
#
# For more information about cmake use Ctrl+F at the page
# http://www.cmake.org/cmake/help/v2.8.8/cmake.html
###############################################################################
cmake_minimum_required(VERSION 2.8)

###############################################################################
# Add module contains a couple of subroutines such as determining 
# target platform bits, output directories setting , etc.
include(cmake/utils.cmake)

###############################################################################
# Set a default build type which will be applied if cmake is runned without
# any specific one. For some generators cmake can set up 'Debug' build type,
# so we need to lower it.
set(CRSL_DEFAULT_BUILD_TYPE "debug_static")
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE ${CRSL_DEFAULT_BUILD_TYPE})
  message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}' as none was specified")
else()
  string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
  message(STATUS "Build type is '${CMAKE_BUILD_TYPE}'")  
endif()

###############################################################################
# Define building configurations: debug, release and so on. For all
# configurations we also should define static ones. Static configurations 
# are used at least for the unit tests.
set(__SHARED_CONFIGS "debug" "release")
foreach(__CONF ${__SHARED_CONFIGS})
  list(APPEND __STATIC_CONFIGS "${__CONF}_static")
endforeach(__CONF)	

###############################################################################
# Determine whether the user specify static or shared configurations
# and set up specified configuration set.
# 
# Due to the bug #6788 we have to set CMAKE_CONFIGURATION_TYPES before
# project command. Otherwise, MSVC generator will ignore defined
# configurations.
if(CMAKE_BUILD_TYPE MATCHES "static")
  set(BUILD_SHARED_LIBS OFF)
  set(CRSL_LIB_TYPE STATIC)
  set(CRSL_CONFIG_APPENDIX "_STATIC")
  set(CRSL_CONFIGS ${__STATIC_CONFIGS})
  add_definitions(-DSTATIC_BUILD)
else()
  set(BUILD_SHARED_LIBS ON)
  set(CRSL_LIB_TYPE SHARED)
  set(CRSL_CONFIG_APPENDIX "")
  set(CRSL_CONFIGS ${__SHARED_CONFIGS})
endif()

###############################################################################
# Cmake does not know which configurations are supposed to be
# debug, so it treats all of them as 'optimized', so let specify
# debug configuration's global property (its needed to determine
# with which library should link: QtCore_debug.lib, or QtCore.lib)
foreach(__CONF ${CRSL_CONFIGS})
  if(${__CONF} MATCHES "debug")
    list(APPEND __DEBUG_CONFIGURATIONS "${__CONF};")
  endif()
endforeach(__CONF)
set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS ${__DEBUG_CONFIGURATIONS})

###############################################################################
# We have to pass variable into the cache for the MSVC generator.
set(CMAKE_CONFIGURATION_TYPES ${CRSL_CONFIGS} CACHE INTERNAL "")

###############################################################################
# Check specified build type if any. 
# Abort generation in case of configurations does not have
# passed build type.
if(NOT (CMAKE_CONFIGURATION_TYPES MATCHES ${CMAKE_BUILD_TYPE}))
  message(FATAL_ERROR "Unknown build type: "${CMAKE_BUILD_TYPE})
endif()

option(CRSL_TEST "Create testing project" ON)
###############################################################################
# carousel is a solution (in MSVC terminology) for the following
# projects, listed in "Top-level filters" section. This project
# sets up such base entities as output directories, building
# type (static or shared) and configurations, OS, compile flags
# and other key concepts shared between inner projects.
if(CRSL_TEST)
  set(CRSL_PROJECT_NAME "carousel_with_tests")
  message(STATUS "Testing project.")
else()
  set(CRSL_PROJECT_NAME "carousel")
endif()

project(${CRSL_PROJECT_NAME} CXX)
message(STATUS "Project name: ${CRSL_PROJECT_NAME}" )

###############################################################################
# Specify target platform's bit and operation system
crsl_get_target_platform_bits(CRSL_TARGET_PLATFORM_BITS)
crsl_get_target_os(CRSL_TARGET_OS)
message(STATUS "Target system: " ${CRSL_TARGET_OS}${CRSL_TARGET_PLATFORM_BITS})

###############################################################################
# Setup compiler/linker flags and defines for all building configurations.
# CMake expects the CMAKE_<TARGET>_FLAGS_<CONFIGURATION> in upper case, 
# so we have to modify configuration names too. 
# Depending on static/shared configurations CRSL_CONFIG_APPENDIX will
# be '_STATIC' or empty string.
# CRSL_<TARGET>_FLAGS_<CONFIGURATION> variables are imported from the
# included file.
include(cmake/compiler_flags.cmake)

# Set compile flags for static/shared configurations
set(CMAKE_CXX_FLAGS                                ${CRSL_CXX_FLAGS_COMMON}  CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG${CRSL_CONFIG_APPENDIX}   ${CRSL_CXX_FLAGS_DEBUG}   CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE${CRSL_CONFIG_APPENDIX} ${CRSL_CXX_FLAGS_RELEASE} CACHE INTERNAL "" FORCE)

# Set linker flags for static/shared/exe configurations
set(CMAKE_EXE_LINKER_FLAGS                                   ${CRSL_LINKER_FLAGS_COMMON}  CACHE INTERNAL "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG${CRSL_CONFIG_APPENDIX}      ${CRSL_LINKER_FLAGS_DEBUG}   CACHE INTERNAL "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE${CRSL_CONFIG_APPENDIX}    ${CRSL_LINKER_FLAGS_RELEASE} CACHE INTERNAL "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG${CRSL_CONFIG_APPENDIX}   ${CRSL_LINKER_FLAGS_DEBUG}   CACHE INTERNAL "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE${CRSL_CONFIG_APPENDIX} ${CRSL_LINKER_FLAGS_RELEASE} CACHE INTERNAL "" FORCE)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} (${CMAKE_CXX_COMPILER})")

if(CMAKE_BUILD_TYPE MATCHES "debug")
  message(STATUS "Compiler flags: ${CMAKE_CXX_FLAGS} ${CRSL_CXX_FLAGS_DEBUG}")
  message(STATUS "Linker flags: ${CMAKE_EXE_LINKER_FLAGS} ${CRSL_LINKER_FLAGS_DEBUG}")
else()
  message(STATUS "Compiler flags: ${CMAKE_CXX_FLAGS} ${CRSL_CXX_FLAGS_RELEASE}")
  message(STATUS "Linker flags: ${CMAKE_EXE_LINKER_FLAGS} ${CRSL_LINKER_FLAGS_RELEASE}")
endif()	

###############################################################################
# Define common directory pathes (for outputs, includes)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/")
set(CAROUSEL_WD ${CMAKE_CURRENT_SOURCE_DIR})
set(HPP_SOURCE_TREE ${CAROUSEL_WD}/include)
set(CPP_SOURCE_TREE ${CAROUSEL_WD}/src)

###############################################################################
# Configure the Qt stuff
find_package(Qt4 REQUIRED)
set(QT_DONT_USE_QTGUI TRUE)
include(${QT_USE_FILE})

message(STATUS "Used Qt version: ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}")

###############################################################################
# ... and specify them as pathes in which the linker will look for libraries
if(WIN32)
  link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
endif()
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
 
###############################################################################
# Turn ON ability to organize projects into folders/filters (for MSVC, xCode)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

###############################################################################
# Add sources
add_subdirectory(src)

if(CRSL_TEST)  
  message(STATUS "Create testing projects")
  add_subdirectory(tests) 
endif()
