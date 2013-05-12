###############################################################################
# utils project
set(CRSL_PROJECT_NAME "JsScripting")
include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/JsScriptingComponent.cpp 
)
	
######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/jsscripting_global.h 
    ${CRSL_TARGET_HEADERS}/JsScriptingComponent.h 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/JsScripting.definition 
)

######################################################################
# Qt generated files
qt4_wrap_cpp(__HEADERS_MOC ${__HEADERS})
qt4_add_resources(__GENERATED_RESOURCES ${__RESOURCES})

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS})
source_group("moc" FILES ${__HEADERS_MOC})
source_group("res" FILES ${__GENERATED_RESOURCES} ${__RESOURCES})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__OTHER_FILES} ${__RESOURCES} ${__GENERATED_RESOURCES} )

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} Interactivity)

###############################################################################
# Qt dependencies
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTCORE_LIBRARY})
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTGUI_LIBRARY})

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)