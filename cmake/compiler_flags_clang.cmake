###############################################################################
# __APPLE__    This macro is defined in any Apple computer, so we skip it
# -W3          Sets warning level. Seems, that it is not implemented in CLang yet.
set(CRSL_CXX_FLAGS_COMMON "-DUNICODE -D_UNICODE -std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7")

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
set(CRSL_LINKER_FLAGS_COMMON "-std=c++11 -stdlib=libc++ -mmacosx-version-min=10.7 -framework CoreFoundation -lc++ -lc++abi")

###############################################################################
set(CRSL_LINKER_FLAGS_DEBUG "")
set(CRSL_LINKER_FLAGS_RELEASE "")
