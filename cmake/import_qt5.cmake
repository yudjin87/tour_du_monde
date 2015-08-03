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
#     _populate_Core_target_properties(DEBUG "libQt5Core.so.5.0.2")
# or
#     _populate_Core_target_properties(RELEASE "libQt5Core.so.5.0.2")


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
# List of Qt5 modules carousel is dependent on
set(__LIBRARIES_BASENAME
    Core
    Gui
    Script
    Test
    Widgets
    Xml)

########################################################################################
# Include import-script depending on build platform
if(MSVC)
  message(STATUS "Import Qt5 for the MSVC compiler...")
  include(cmake/import_qt5_msvc.cmake)
elseif(MINGW)
  message(STATUS "Import Qt5 for the MinGW compiler...")
  include(cmake/import_qt5_mingw.cmake)
elseif(XCODE_VERSION)
  message(STATUS "Import Qt5 for the Xcode (Clang compiler)...")
  include(cmake/import_qt5_clang.cmake)
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  include(cmake/import_qt5_clang.cmake)
  message(STATUS "Import Qt5 for the Clang compiler...")
elseif(${CMAKE_GENERATOR} MATCHES "Unix Makefiles")
  message(STATUS "Import Qt5 for the GNU compiler...")
  include(cmake/import_qt5_gnu.cmake)
endif()

########################################################################################
# List of Qt5 modules needed for CMake functions (like qt5_wrapp_cpp and qt5_wrapp_ui)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

message(STATUS "Qt5: Found.")
