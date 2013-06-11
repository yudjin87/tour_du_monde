########################################################################################
# Finds Qt5 include directories, plugins and libraries for the MSVC compiler

set(__DEBUG_SUFFIX "d")
set(__PLATFORM_PLUGIN "qwindows")

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
# Set paths to plugins, libs, headers
crsl_qt5_setup_paths()

message(STATUS "Qt5: Found.")
