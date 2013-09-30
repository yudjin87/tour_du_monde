###############################################################################
# test project
set(CRSL_PROJECT_NAME "exportDelFuncOnly")
include(cmake/target_utils)

######################################################################
# Sources
file(GLOB __SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

######################################################################
# Headers
file(GLOB __HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS})
source_group("moc" FILES ${__HEADERS_MOC})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} SHARED ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC})

######################################################################
# Setup output path
crsl_setup_output_path(unittest/libs)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} Carousel)
