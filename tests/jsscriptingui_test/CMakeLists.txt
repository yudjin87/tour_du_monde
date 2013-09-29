###############################################################################
# test project
set(CRSL_PROJECT_NAME "jsscriptingUI_test")
include(cmake/target_utils)

######################################################################
# Sources
file(GLOB __SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

######################################################################
# Headers
file(GLOB __HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)


######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS} ${__HEADERS_FAKES})

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS})
source_group("moc" FILES ${__HEADERS_MOC})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_executable(${CRSL_PROJECT_NAME} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC})

######################################################################
# Setup output path
crsl_setup_output_path(unittest)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} org.carousel.JsScriptingUI Utils)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Test)

###############################################################################
# Copy scripts to the output subdirectory "scripts"
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__SCRIPTS}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>/scripts)
