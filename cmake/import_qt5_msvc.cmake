########################################################################################
# Finds Qt5 include directories, plugins and libraries for the MSVC compiler

set(__DEBUG_SUFFIX "d")
set(__PLATFORM_PLUGIN "qwindows")

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
# Find runtime libraries which will be copied during install.
# I don't use qt5_use_modules() function because I have to
# handle Qt runtime libraries manualy, copying them to the output directory.
# It allows to run executables right from the directory at least for Windows.
# For MacOS you still have to set up Working Directory.

foreach(__LIB_BASENAME ${__LIBRARIES_BASENAME})
  find_package(Qt5${__LIB_BASENAME} REQUIRED)

  # map debug-static and release-static configurations
  set_target_properties(Qt5::${__LIB_BASENAME} PROPERTIES MAP_IMPORTED_CONFIG_RELEASE-STATIC "RELEASE")
  set_target_properties(Qt5::${__LIB_BASENAME} PROPERTIES MAP_IMPORTED_CONFIG_DEBUG-STATIC "DEBUG")

  # get run-time library paths (they will be copied for Windows and for MacOS bundle)
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
# Set paths to plugins, libs, headers
crsl_qt5_setup_paths()

#########################################################################################
# Copy Qt5 DLLs and plugins to be enable start executables right from directory
if(QT_COPY_LIBRARIES)
    ########################################################################################
    # Find plugins which will be copied during install
    set(__Qt5_PLUGINS_DEBUG
        ${Qt5_PLUGINS_DIRS}/platforms/${CMAKE_SHARED_LIBRARY_PREFIX}${__PLATFORM_PLUGIN}${__DEBUG_SUFFIX}${CMAKE_SHARED_LIBRARY_SUFFIX})

    set(__Qt5_PLUGINS_RELEASE
        ${Qt5_PLUGINS_DIRS}/platforms/${CMAKE_SHARED_LIBRARY_PREFIX}${__PLATFORM_PLUGIN}${CMAKE_SHARED_LIBRARY_SUFFIX})

    ########################################################################################
    # Find Qt dependencies

    # TODO: get from the parameters ICU usage. From Qt 5.3 ICU is not mandatory any more, if WebKit is not used
    # TODO: use windeployqt.exe
    # set(__Qt5_DEPS
    #    ${__QT_ROOT_DIR}/bin/icudt51.dll
    #    ${__QT_ROOT_DIR}/bin/icuin51.dll
    #    ${__QT_ROOT_DIR}/bin/icuuc51.dll)

    set(__Qt5_DEPS_DEBUG
        ${__Qt5_DEPS}
        ${__QT_ROOT_DIR}/bin/libEGLd.dll
        ${__QT_ROOT_DIR}/bin/libGLESv2d.dll)

    set(__Qt5_DEPS_RELEASE
        ${__Qt5_DEPS}
        ${__QT_ROOT_DIR}/bin/libEGL.dll
        ${__QT_ROOT_DIR}/bin/libGLESv2.dll)

    message(STATUS "Creating install target for copying Qt5 libraries and plugins...")

    # Copy to the binaries
    crsl_set_files_to_copy_on_install("${__Qt5_all_RUNTIMES_DEBUG}" "${__Qt5_all_RUNTIMES_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" bin)
    crsl_set_files_to_copy_on_install("${__Qt5_DEPS_DEBUG}" "${__Qt5_DEPS_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" bin)
    crsl_set_files_to_copy_on_install("${__Qt5_PLUGINS_DEBUG}" "${__Qt5_PLUGINS_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" bin/platforms)

    # Copy to the unit tests
    crsl_set_files_to_copy_on_install("${__Qt5_all_RUNTIMES_DEBUG}" "${__Qt5_all_RUNTIMES_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" unittest)
    crsl_set_files_to_copy_on_install("${__Qt5_DEPS_DEBUG}" "${__Qt5_DEPS_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" unittest)
    crsl_set_files_to_copy_on_install("${__Qt5_PLUGINS_DEBUG}" "${__Qt5_PLUGINS_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" unittest/platforms)

    # Copy to manual tests
    crsl_set_files_to_copy_on_install("${__Qt5_all_RUNTIMES_DEBUG}" "${__Qt5_all_RUNTIMES_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" manual-test)
    crsl_set_files_to_copy_on_install("${__Qt5_DEPS_DEBUG}" "${__Qt5_DEPS_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" manual-test)
    crsl_set_files_to_copy_on_install("${__Qt5_PLUGINS_DEBUG}" "${__Qt5_PLUGINS_RELEASE}" "${CAROUSEL_WD}/product" "${CRSL_COMPILER}" "-x${CRSL_TARGET_PLATFORM_BITS}" manual-test/platforms)

endif()

message(STATUS "Qt5: Found.")
