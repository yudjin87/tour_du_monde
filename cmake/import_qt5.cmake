########################################################################################
# Finds Qt5 include directories, plugins and libraries

string(TOUPPER ${CRSL_COMPILER}-x${CRSL_TARGET_PLATFORM_BITS} __COMPILER)
message(STATUS "Qt directory: " ${__COMPILER})
set(__QT_ROOT_DIR ${QT_ROOT_LOCATION_${__COMPILER}})

if(WIN32)
    set(__DEBUG_SUFFIX "d")
    set(__PLATFORM_PLUGIN "qwindows")
elseif(APPLE)
    set(__DEBUG_SUFFIX "_debug")
    set(__PLATFORM_PLUGIN "qcocoa")
endif(WIN32)

set(ENV{CMAKE_PREFIX_PATH} ${__QT_ROOT_DIR})
set(ENV{QTDIR} ${__QT_ROOT_DIR})
message(STATUS "Qt directory: " $ENV{__QT_ROOT_DIR})

########################################################################################
# Find runtime libraries which will be copied during install.
# I don't use qt5_use_modules() function because I have to
# handle Qt runtime libraries manualy, copying them to the output directory.
# It allows to run executables right from the directory at least for Windows.
# For MacOS you still have to set up Working Directory.
set(__LIBRARIES_BASENAME
    Core
    Gui
    Widgets
    Test
    Xml)

foreach(__LIB_BASENAME ${__LIBRARIES_BASENAME})
  find_package(Qt5${__LIB_BASENAME} REQUIRED)
  #if(Qt5${__LIB_BASENAME} STREQUAL "NOTFOUND"

  # map debug-static and release-static configurations
  set_target_properties(Qt5::${__LIB_BASENAME} PROPERTIES MAP_IMPORTED_CONFIG_RELEASE-STATIC "RELEASE")
  set_target_properties(Qt5::${__LIB_BASENAME} PROPERTIES MAP_IMPORTED_CONFIG_DEBUG-STATIC "DEBUG")

  # get run-time libraries path (they will be copied for Windows and for MacOS bundle)
  get_target_property(Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG Qt5::${__LIB_BASENAME} "IMPORTED_LOCATION_DEBUG")
  get_target_property(Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE Qt5::${__LIB_BASENAME} "IMPORTED_LOCATION_RELEASE")

  # get full path
  get_filename_component(Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG ${Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG} REALPATH)
  get_filename_component(Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE ${Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE} REALPATH)

  if(DEBUG_VERBOSITY)
    message(STATUS "Qt${__LIB_BASENAME}: " ${Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG})
    message(STATUS "Qt${__LIB_BASENAME}: " ${Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE})
  endif()

  list(APPEND __Qt5_all_RUNTIMES_DEBUG ${Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG})
  list(APPEND __Qt5_all_RUNTIMES_RELEASE ${Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE})
endforeach()

########################################################################################
# Set include path
set(Qt5_RUNTIME_LIBRARY_DIRS "${__QT_ROOT_DIR}/lib")
set(Qt5_INCLUDE_DIRS "${__QT_ROOT_DIR}/include")
set(Qt5_PLUGINS_DIRS "${__QT_ROOT_DIR}/plugins")
if(DEBUG_VERBOSITY)
  message(STATUS "Qt includes: " ${Qt5_INCLUDE_DIRS})
endif()

#########################################################################################
# Copy DLLs to be enable start executables right from directory (if QTDIR
if(QT_COPY_LIBRARIES)
    ########################################################################################
    # Find plugins which will be copied during install
    set(__Qt5_PLUGINS_DEBUG
        ${Qt5_PLUGINS_DIRS}/platforms/${CMAKE_SHARED_LIBRARY_PREFIX}${__PLATFORM_PLUGIN}${__DEBUG_SUFFIX}${CMAKE_SHARED_LIBRARY_SUFFIX})

    set(__Qt5_PLUGINS_RELEASE
        ${Qt5_PLUGINS_DIRS}/platforms/${CMAKE_SHARED_LIBRARY_PREFIX}${__PLATFORM_PLUGIN}${CMAKE_SHARED_LIBRARY_SUFFIX})

    ########################################################################################
    # macdeployqt is used on Apple to copy all Qt libraries
    if(NOT APPLE)
        crsl_set_files_to_copy_on_install("${__Qt5_all_RUNTIMES_DEBUG}" "${__Qt5_all_RUNTIMES_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" bin)
        crsl_set_files_to_copy_on_install("${__Qt5_PLUGINS_DEBUG}" "${__Qt5_PLUGINS_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" bin/platforms)

        # Copy to unit tests
        crsl_set_files_to_copy_on_install("${__Qt5_all_RUNTIMES_DEBUG}" "${__Qt5_all_RUNTIMES_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" unittest)
        crsl_set_files_to_copy_on_install("${__Qt5_PLUGINS_DEBUG}" "${__Qt5_PLUGINS_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" unittest/platforms)
    endif()
endif()

message(STATUS "Qt5: Found.")
