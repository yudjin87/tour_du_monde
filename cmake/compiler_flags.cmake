###############################################################################
# This module determines which compiler/linker flags and defines should
# be loaded according to the system.
# Following included modules export variables to the parent scope.

# True when using some Microsoft Visual C compiler
if(MSVC)
  include(cmake/compiler_flags_msvc.cmake)
  message(STATUS "Use compiler/linker flags for the MSVC.")
elseif(MINGW)
  include(cmake/compiler_flags_gnu.cmake)
  message(STATUS "Use compiler/linker flags for the MinGW.")
# True when using some Xcode generator
elseif(XCODE_VERSION)
  include(cmake/compiler_flags_clang.cmake)
  message(STATUS "Use compiler/linker flags for the Xcode (Clang).")
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  include(cmake/compiler_flags_clang.cmake)
  message(STATUS "Use compiler/linker flags for the Clang.")
elseif(${CMAKE_GENERATOR} MATCHES "Unix Makefiles")
  include(cmake/compiler_flags_gnu.cmake)
  message(STATUS "Use compiler/linker flags for the Unix Makefiles.")
endif()

message(STATUS "Cmake Generator: " ${CMAKE_GENERATOR})
