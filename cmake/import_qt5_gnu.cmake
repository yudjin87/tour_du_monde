########################################################################################
# Finds Qt5 include directories, plugins and libraries for the GNU compiler

set(__PLATFORM_PLUGIN "qlinuxfb")

if(${CMAKE_BUILD_TYPE} MATCHES "debug")
  set(__BUILD "DEBUG")
else()
  set(__BUILD "RELEASE")  
endif()

########################################################################################
# Format name for the external variable, which contains path to the Qt5 directory.
# See user_settings.cmake.template to find all variables.
string(TOUPPER ${CRSL_COMPILER}-x${CRSL_TARGET_PLATFORM_BITS} __COMPILER)
set(__QT_ROOT_DIR ${QT_ROOT_LOCATION_${__COMPILER}})

if("${QT_ROOT_LOCATION_${__COMPILER}}" STREQUAL "")
    message(STATUS "The QT_ROOT_LOCATION_${__COMPILER} variable was not found, use environment variable QTDIR")
    set(__QT_ROOT_DIR $ENV{QTDIR})
else()
    set(ENV{CMAKE_PREFIX_PATH} ${__QT_ROOT_DIR})
    set(ENV{QTDIR} ${__QT_ROOT_DIR})
endif()

message(STATUS "Qt directory: " ${__QT_ROOT_DIR})

foreach(__LIB_BASENAME ${__LIBRARIES_BASENAME})
  # Reset found path
  set(Qt5${__LIB_BASENAME}_DIR Qt5${__LIB_BASENAME}-NOTFOUND)

  find_package(Qt5${__LIB_BASENAME} REQUIRED)

  if(${Qt5${__LIB_BASENAME}} MATCHES "NOTFOUND")
    message(FATAL_ERROR "Qt5${__LIB_BASENAME} NOT FOUND!")
  endif()

  # map debug/release static configurations
  set_target_properties(Qt5::${__LIB_BASENAME} PROPERTIES MAP_IMPORTED_CONFIG_${__BUILD}-STATIC ${__BUILD})

  # get run-time library paths
  get_target_property(Qt5_${__LIB_BASENAME}_RUNTIME Qt5::${__LIB_BASENAME} "IMPORTED_LOCATION_${__BUILD}")

  message(STATUS "Qt${__LIB_BASENAME}: " ${Qt5_${__LIB_BASENAME}_RUNTIME})

  # get full path
  get_filename_component(Qt5_${__LIB_BASENAME}_RUNTIME ${Qt5_${__LIB_BASENAME}_RUNTIME} REALPATH)

  if(DEBUG_VERBOSITY)
    message(STATUS "Qt${__LIB_BASENAME}: " ${Qt5_${__LIB_BASENAME}_RUNTIME})
  endif()

endforeach()

########################################################################################
# Set paths to plugins, libs, headers
crsl_qt5_setup_paths()

message(STATUS "Qt5: Found.")
