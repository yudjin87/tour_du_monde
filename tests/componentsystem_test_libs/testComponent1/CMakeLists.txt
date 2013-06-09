###############################################################################
# test project
set(CRSL_PROJECT_NAME "TestComponent1")
include(cmake/target_utils)

######################################################################
# Sources
file(GLOB __SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

######################################################################
# Headers
file(GLOB __HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/TestComponent1.definition
)

# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS} ${__OTHER_FILES})
source_group("moc" FILES ${__HEADERS_MOC})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} SHARED ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__OTHER_FILES})

######################################################################
# Setup output path
crsl_setup_output_path(unittest/components)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} ComponentSystem)

###############################################################################
# Copy test definitions to the output directory, near the test executable
set(__RT_DIRECTORY "")
get_target_property(__RT_DIRECTORY ${CRSL_PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" ${__RT_DIRECTORY})
