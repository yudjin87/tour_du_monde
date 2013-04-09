###############################################################################
# This module contains a couple of subroutines such as determining 
# target platform bits, output directories setting and other.
# This module does not export any variables to the parent scope.

###############################################################################
# Returns platform bit to __RESULT in string representation
# to use it as appendix (e.g. win32)
function(crsl_get_target_platform_bits __RESULT)
  if("${CMAKE_SIZEOF_VOID_P}" GREATER 4)
    set(${__RESULT} "64" PARENT_SCOPE)
  else()
    if(WIN32)
      # Set to true when using the 64 bit cl compiler from Microsoft.
      if(${CMAKE_CL_64})
        set(${__RESULT} "64" PARENT_SCOPE)
      else()
        set(${__RESULT} "32" PARENT_SCOPE)
      endif(${CMAKE_CL_64})
    else()
      set(${__RESULT} "32" PARENT_SCOPE)
    endif(WIN32)
  endif()
endfunction(crsl_get_target_platform_bits)

###############################################################################
# Returns short name of target operation system to __RESULT,
# used some empirical tests. It used for the binaries
# outputs.
function(crsl_get_target_os __RESULT)
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(${__RESULT} "osx" PARENT_SCOPE)
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if(MINGW)
      set(${__RESULT} "mingw" PARENT_SCOPE)
    else()
      set(${__RESULT} "win" PARENT_SCOPE)
    endif()
  elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
   set(${__RESULT} "linux" PARENT_SCOPE)
  else()
        set(${__RESULT} "Unknown OS" PARENT_SCOPE)
        message(FATAL_ERROR "Unknown operation system :" ${CMAKE_SYSTEM_NAME})
  endif()
endfunction(crsl_get_target_os)

###############################################################################
# Returns short name of the compiler to __RESULT .It used for the binaries
# outputs.
function(crsl_get_compiler __RESULT)
  string(TOLOWER ${CMAKE_CXX_COMPILER_ID} __CMPLR)

  if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if("${CMAKE_CXX_COMPILER_VERSION}" STREQUAL "")
      message(FATAL_ERROR "Undefined compiler version. Use cmake 2.8.10 or higher.")
    endif()

    set(__SUFIX "")
    # Unfortunately, I couldnot use \\d or even {0,2} to get NNN.NNN pattern
    # string(REGEX MATCH "(([0-9]+)\\.*)(([0-9]+))" __VERSION ${CMAKE_CXX_COMPILER_VERSION})
    string(REGEX MATCH "([0-9]+)" __VERSION ${CMAKE_CXX_COMPILER_VERSION})
    if(${__VERSION} EQUAL 17)
      set(__SUFIX "11")
    elseif(${__VERSION} EQUAL 16)
      set(__SUFIX "10")
    elseif()
      set(__SUFIX "-undefined-version")
    endif()
  endif()

  set(${__RESULT} "${__CMPLR}${__SUFIX}" PARENT_SCOPE)
endfunction(crsl_get_compiler)

###############################################################################
# Forms and sets up default pathes for the runtime binaries and 
# libraries outputs.
# This function set up as default CMAKE_<TYPE>_OUTPUT_DIRECTORY'es
# variables and configuration-dependent variables for the MSVC
# generators.
macro(crsl_use_default_project_output_path __TARGET_NAME __ROOT __COMPILER __BITS __BUILD __PREFIX)
  set(__OUTPUT_DIR ${__ROOT}/${__COMPILER}${__BITS}-${__BUILD}/${__PREFIX})
  set(__LIBRARIES_DIR ${__ROOT}/${__COMPILER}${__BITS}-${__BUILD}/${__PREFIX})

  #message(STATUS "${__BUILD} output: ${__BUILD}")
  message(STATUS "${__TARGET_NAME} output: ${__OUTPUT_DIR}")
  set_target_properties(${__TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${__OUTPUT_DIR})
  set_target_properties(${__TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${__LIBRARIES_DIR})
  set_target_properties(${__TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${__OUTPUT_DIR})
	
  # For Visual Studio we need to specify output pathes for all
  # configurations. CMake expects that thise variables will be in
  # upper case.
  foreach(CONF ${CMAKE_CONFIGURATION_TYPES})
    set(__MS_VC_OUTPUT_DIR ${__ROOT}/${__COMPILER}${__BITS}-${CONF}/${__PREFIX})
    set(__MS_VC_LIBRARIES_DIR ${__ROOT}/${__COMPILER}${__BITS}-${CONF}/${__PREFIX})

    string(TOUPPER ${CONF} CONF)
    set_target_properties(${__TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${CONF} ${__MS_VC_OUTPUT_DIR})
    set_target_properties(${__TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${CONF} ${__MS_VC_LIBRARIES_DIR})
    set_target_properties(${__TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${CONF} ${__MS_VC_OUTPUT_DIR})
  endforeach(CONF)	
endmacro(crsl_use_default_project_output_path)

###############################################################################
# Copies a list of files __FILES into the specified __DIRECTORY right after
# __TARGET will be build.
function(crsl_copy_extra_files __TARGET __FILES __DIRECTORY)
  foreach(__FILE ${__FILES})
    set(__FILE_NAME "")
    get_filename_component(__FILE_NAME ${__FILE} NAME)
    add_custom_command(
      TARGET ${__TARGET}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${__FILE} ${__DIRECTORY}/${__FILE_NAME}
      COMMENT "Copying ${__FILE} to ${__DIRECTORY}/${__FILE_NAME}"
    )
  endforeach(__FILE)
endfunction(crsl_copy_extra_files)
