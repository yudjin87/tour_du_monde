###############################################################################
# This module specifies MSVC compiler/linker flags and defines for
# release and debug configurations.
# When this module is included all variables become visible in the parent 
# scope.
# Compiler options: http://msdn.microsoft.com/en-us/library/fwkeyyhe.aspx
# Linker options: http://msdn.microsoft.com/en-us/library/y0zzbyt4(v=vs.71).aspx

###############################################################################
# /DWIN32     Window specific define
# /D_WINDOWS  Window specific define
# /W3         Sets warning level
# /Zm1000     Specifies the precompiled header memory allocation limit.
# /GR         Enables run-time type information (RTTI).
# /EHsc       Specifies the model of exception handling.
# /MP         Causes the compiler to create one or more copies of itself, each in a separate process. 
# /wd4290     MSVC compiler does not implement exception specification.
# /wd4250     MSVC compiler shows this warning, but with virtual inheritance that problem is solved, so just disable it.
set(CRSL_CXX_FLAGS_COMMON "/DUNICODE /D_UNICODE /DWIN32 /D_WINDOWS /W3 /Zm1000 /GR /EHsc /MP4 /wd4290 /wd4250")

###############################################################################
# /D_DEBUG    Specify debug versions of the CRT library.
# /MDd        Creates a debug multithreaded DLL using MSVCRTD.lib.
# /Zi         Generates complete debugging information. 
# /Ob0        Controls inline expansion: disables inline expansion.
# /Od         Disables optimization. 
# /RTC1       Enables run-time error checking.
# /WX         Treats all compiler warnings as errors (WX- does not treats).
set(CRSL_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1 /WX-")  

###############################################################################
# /MD         Creates a multithreaded DLL using MSVCRT.lib.
# /O2         Speed optimization.
# /Ob2        Controls inline expansion: expands functions marked as inline or __inline and any other function that the compiler chooses.  
# /DNDEBUG    Specify release versions of the CRT library.
set(CRSL_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /DNDEBUG")
  
###############################################################################
# /STACK      Sets the size of the stack in bytes.
# /MACHINE    Specifies the target platform for the program.
# /NOLOGO     Prevents display of the copyright message and version number.
if("${CMAKE_SIZEOF_VOID_P}" GREATER 4)
  set(CRSL_LINKER_FLAGS_COMMON "/STACK:10000000 /MACHINE:X64 /NOLOGO")
else()
  set(CRSL_LINKER_FLAGS_COMMON "/STACK:10000000 /MACHINE:X86 /NOLOGO")
endif()

###############################################################################
# /DEBUG       Creates debugging information for the .exe file or DLL.
# /INCREMENTAL Controls how the linker handles incremental linking.
set(CRSL_LINKER_FLAGS_DEBUG "/DEBUG /INCREMENTAL")
set(CRSL_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO")
