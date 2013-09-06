###############################################################################
# -W3          Sets warning level.
set(CRSL_CXX_FLAGS_COMMON "-DUNICODE -D_UNICODE -std=c++11")

###############################################################################
# -D_DEBUG    Specify debug macros.
# -g          Generates complete debugging information. 
# -fno-inline Controls inline expansion: Don't pay attention to the "inline" keyword.
# -O0         Disables optimization. 
# -Werror     Treats all compiler warnings as errors.
set(CRSL_CXX_FLAGS_DEBUG "-DDEBUG -D_DEBUG -g -fno-inline -O0")

###############################################################################
# -O2         Speed optimization. 
# -DNDEBUG    Specify release macros.
set(CRSL_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
  
###############################################################################
if("${CMAKE_SIZEOF_VOID_P}" GREATER 4)
  set(CRSL_COMMON_LINKER_FLAGS "")
else()
  set(CRSL_COMMON_LINKER_FLAGS "")
endif()

###############################################################################
set(CRSL_LINKER_FLAGS_DEBUG "")
set(CRSL_LINKER_FLAGS_RELEASE "")
