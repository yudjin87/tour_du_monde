###############################################################################
# This module finds Qt5 stuff depending on the platform, because Qt5 has different
# structure for different platforms. E.g., it is possible to build both debug
# and release build of Qt5 on MacOS and Windows, but not on Linux. On Linux you
# should build debug and release in the separate directories, because Qt5 CMake files
# for release and for debug will be different on Linux, e.g. on Windows there are two
# configurations (Qt5CoreConfig.cmake):
#     _populate_imported_target_properties(DEBUG "Qt5Cored.dll" "Qt5Cored.lib" )
#     _populate_imported_target_properties(RELEASE "Qt5Core.dll" "Qt5Core.lib" )
# but on Linux only one:
#     _populate_imported_target_properties(DEBUG "Qt5Core.5.0.so")
# or
#     _populate_imported_target_properties(RELEASE "Qt5Core.5.0.so")

########################################################################################
# List of Qt5 modules carousel is dependent on
set(__LIBRARIES_BASENAME
    Core
    Gui
    Widgets
    Test
    Xml)

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

########################################################################################
# Shared functions that are used for all platforms:

function(crsl_qt5_setup_paths)
    set(Qt5_RUNTIME_LIBRARY_DIRS "${__QT_ROOT_DIR}/lib" PARENT_SCOPE)
    set(Qt5_INCLUDE_DIRS "${__QT_ROOT_DIR}/include" PARENT_SCOPE)
    set(Qt5_PLUGINS_DIRS "${__QT_ROOT_DIR}/plugins" PARENT_SCOPE)
    if(DEBUG_VERBOSITY)
        message(STATUS "Qt runtime directory: ${__QT_ROOT_DIR}/lib")
        message(STATUS "Qt includes: ${__QT_ROOT_DIR}/include")
        message(STATUS "Qt plugin directory: ${__QT_ROOT_DIR}/plugins")
    endif()
endfunction(crsl_qt5_setup_paths)

########################################################################################
# Determine build platform
if(MSVC)
  message(STATUS "Import Qt5 for the MSVC compiler...")
  include(cmake/import_qt5_msvc.cmake)
elseif(MINGW)
  message(STATUS "Import Qt5 for the MinGW compiler...")
  include(cmake/import_qt5_mingw.cmake)
elseif(XCODE_VERSION)
  message(STATUS "Import Qt5 for the Clang compiler...")
  include(cmake/import_qt5_clang.cmake)
elseif(${CMAKE_GENERATOR} MATCHES "Unix Makefiles")
  message(STATUS "Import Qt5 for the GNU compiler...")
  include(cmake/import_qt5_gnu.cmake)
endif()

