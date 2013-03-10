###############################################################################
# Generates a build system.
# __GENERATOR_NAME  - name of generators, e.g. "NMake Makefiles" or "Unix Makefiles";
# __BUILD_TYPE      - name of building configuration (debug, release_static);
# __BUILD_TREE_PATH - path where cmake will produce all its stuff including Makefiles;
# __TEST            - ON: builds and runs tests, OFF: build only carousel library;
# __BUILD_RESULT    - returns 0 if generating has finished succesfuly. Otherwise, return 1.
function(crsl_generate_project __GENERATOR_NAME __BUILD_TYPE __BUILD_TREE_PATH __TEST __BUILD_RESULT )
  set(BUILD_RESULT 0)
  execute_process(COMMAND 
    ${CMAKE_COMMAND} -G 
	${__GENERATOR_NAME} ".." "-DCMAKE_BUILD_TYPE=${__BUILD_TYPE}"  "-DCRSL_TEST=${__TEST}" 
	WORKING_DIRECTORY ${__BUILD_TREE_PATH} 
	RESULT_VARIABLE BUILD_RESULT)

  set(${__BUILD_RESULT} ${BUILD_RESULT} PARENT_SCOPE)
endfunction(crsl_generate_project)

###############################################################################
# Generates projects for building.
# __BUILD_TYPE      - name of building configuration (debug, release_static);
# __BUILD_TREE_PATH - path where Makefiles or other projects have been generated;
function(crsl_build_project __BUILD_TYPE __BUILD_TREE_PATH)
  message(STATUS "Build type: " ${__BUILD_TYPE})
  execute_process(COMMAND ${CMAKE_COMMAND}
    --build .  
    --config ${__BUILD_TYPE}
    WORKING_DIRECTORY ${__BUILD_TREE_PATH})
  
endfunction(crsl_build_project)
