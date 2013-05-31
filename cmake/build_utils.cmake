###############################################################################
# Generates build systems and build them using list of configurations and generator's
# name.
# __CONFIGURATIONS      - names of building configurations (debug, release_static);
# __GENERATOR_NAME      - name of generators, e.g. "NMake Makefiles" or "Unix Makefiles";
# __BUILD_TREE_PATH     - path where cmake will produce all its stuff including Makefiles;
# __NATIVE_PARAMS   - pass remaining options to the native tool.
# __PATH_TO_CMAKE_LISTS - path where CmakeLists.txt root config is;
# Example:
# crsl_build("debug;release" "Visual Studio 11" "../MSVC-x32" "-j4" ..)
function(crsl_build __CONFIGURATIONS __GENERATOR_NAME __BUILD_TREE_PATH __NATIVE_PARAMS __PATH_TO_CMAKE_LISTS)
  file(MAKE_DIRECTORY ${__BUILD_TREE_PATH})

  ##############################################################################
  # Generate a build system and perform building for all configurations.
  foreach(__CONF ${__CONFIGURATIONS})
    message(STATUS "Build type: " ${__CONF})

    set(BUILD_RESULT 0)
    crsl_generate_project(${__GENERATOR_NAME} ${__PATH_TO_CMAKE_LISTS} ${__CONF} ${__BUILD_TREE_PATH} "TRUE" BUILD_RESULT)
  
    if(BUILD_RESULT GREATER 0)
      message(FATAL_ERROR "CMake configuration for generator '${__GENERATOR_NAME}' failed.")   
      return()
    endif()

    crsl_build_project(${__CONF} ${__BUILD_TREE_PATH} "${__NATIVE_PARAMS}" BUILD_RESULT)
    if(BUILD_RESULT GREATER 0)
      message(FATAL_ERROR "Build for configuration '${__CONF}' failed.")   
      return()
    endif()

    crsl_install(${__CONF} ${__BUILD_TREE_PATH})
    crsl_run_tests(${__CONF} ${__BUILD_TREE_PATH})
  endforeach(__CONF)

endfunction(crsl_build)

###############################################################################
# Generates a build system.
# __GENERATOR_NAME  - name of generators, e.g. "NMake Makefiles" or "Unix Makefiles";
# __PATH_TO_CMAKE_LISTS - path where CmakeLists.txt root config is;
# __BUILD_TYPE      - name of building configuration (debug, release_static);
# __BUILD_TREE_PATH - path where cmake will produce all its stuff including Makefiles;
# __TEST            - ON: builds and runs tests, OFF: build only carousel library;
# __BUILD_RESULT    - returns 0 if generating has finished succesfuly. Otherwise, return 1.
function(crsl_generate_project __GENERATOR_NAME __PATH_TO_CMAKE_LISTS __BUILD_TYPE __BUILD_TREE_PATH __TEST __BUILD_RESULT)
  set(BUILD_RESULT 0)

  message(STATUS "Building system: " ${__GENERATOR_NAME})
  message(STATUS "Buil tree path1: " ${__BUILD_TREE_PATH})
  message(STATUS "Configuration: " ${__BUILD_TYPE})
  message(STATUS "Path to root CmakeLists.txt: " ${__PATH_TO_CMAKE_LISTS})
  
  
  execute_process(COMMAND 
    ${CMAKE_COMMAND} 
      -G ${__GENERATOR_NAME} 
      ${__PATH_TO_CMAKE_LISTS}
      "-DCMAKE_BUILD_TYPE=${__BUILD_TYPE}"  "-DCRSL_TEST=${__TEST}" 
	    WORKING_DIRECTORY ${__BUILD_TREE_PATH} 
	    RESULT_VARIABLE BUILD_RESULT)

  set(${__BUILD_RESULT} ${BUILD_RESULT} PARENT_SCOPE)
endfunction(crsl_generate_project)

###############################################################################
# Generates projects for building.
# __BUILD_TYPE      - name of building configuration (debug, release_static);
# __BUILD_TREE_PATH - path where Makefiles or other projects have been generated;
# __NATIVE_PARAMS   - pass remaining options to the native tool.
# __BUILD_RESULT    - returns 0 if build has finished succesfuly. Otherwise, return 1.
function(crsl_build_project __BUILD_TYPE __BUILD_TREE_PATH __NATIVE_PARAMS __BUILD_RESULT)
  message(STATUS "Build type: " ${__BUILD_TYPE})
 
  message(STATUS "Buil tree path: " ${__BUILD_TREE_PATH})
  message(STATUS "Configuration: " ${__BUILD_TYPE})
  message(STATUS "Native parameters: " ${__NATIVE_PARAMS})

  set(BUILD_RESULT 0)

  if ("${__NATIVE_PARAMS}" STREQUAL "")
    execute_process(COMMAND ${CMAKE_COMMAND}
      --build .  
      --config ${__BUILD_TYPE}
      WORKING_DIRECTORY ${__BUILD_TREE_PATH}
      RESULT_VARIABLE BUILD_RESULT)
  else()
      execute_process(COMMAND ${CMAKE_COMMAND}
      --build .  
      --config ${__BUILD_TYPE}
      -- ${__NATIVE_PARAMS}
      WORKING_DIRECTORY ${__BUILD_TREE_PATH}
      RESULT_VARIABLE BUILD_RESULT)
  endif()

  set(${__BUILD_RESULT} ${BUILD_RESULT} PARENT_SCOPE)
  
endfunction(crsl_build_project)

###############################################################################
# Install project (copy dependencies and other)
#
# __BUILD_TYPE      - name of building configuration (debug, release_static);
# __BUILD_TREE_PATH - path where Makefiles or other projects have been generated;
function(crsl_install __BUILD_TYPE __BUILD_TREE_PATH)
    execute_process(COMMAND ${CMAKE_COMMAND}
      --build . 
      --config ${__BUILD_TYPE} 
      --target install
      WORKING_DIRECTORY ${__BUILD_TREE_PATH}
      RESULT_VARIABLE __RESULT)

  if(NOT __RESULT STREQUAL 0)
    message(FATAL_ERROR "Error calling CTest: '${__RESULT}'")
  endif()
endfunction(crsl_install)

###############################################################################
# Runs all tests for the specified configuration
#
# __BUILD_TYPE      - name of building configuration (debug, release_static);
# __BUILD_TREE_PATH - path where Makefiles or other projects have been generated;
function(crsl_run_tests __BUILD_TYPE __BUILD_TREE_PATH)
  message(STATUS "Run tests for configuration: " ${__BUILD_TYPE})
  message(STATUS "Working directory: " ${__BUILD_TREE_PATH})

  execute_process(COMMAND ${CMAKE_CTEST_COMMAND}
        -C "${__BUILD_TYPE}"
        -V
        WORKING_DIRECTORY ${__BUILD_TREE_PATH}
        RESULT_VARIABLE __RESULT)

  if(NOT __RESULT STREQUAL 0)
    message(FATAL_ERROR "Error calling CTest: '${__RESULT}'")
  endif()
endfunction(crsl_run_tests)
