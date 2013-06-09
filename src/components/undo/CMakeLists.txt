###############################################################################
# utils project
set(CRSL_PROJECT_NAME "Undo")
set(CRSL_TARGET_TYPE "components")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/RedoOperation.cpp 
    ${CRSL_TARGET_SOURCES}/UndoComponent.cpp 
    ${CRSL_TARGET_SOURCES}/UndoInteractiveExtension.cpp 
    ${CRSL_TARGET_SOURCES}/UndoOperation.cpp 
)
	
######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/RedoOperation.h 
    ${CRSL_TARGET_HEADERS}/undo_global.h 
    ${CRSL_TARGET_HEADERS}/UndoComponent.h 
    ${CRSL_TARGET_HEADERS}/UndoInteractiveExtension.h 
    ${CRSL_TARGET_HEADERS}/UndoOperation.h 
)

######################################################################
# Resources
set(__RESOURCES
    ${CRSL_TARGET_SOURCES}/undo.qrc 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/Undo.definition 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})
qt5_add_resources(__GENERATED_RESOURCES ${__RESOURCES})

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
target_link_libraries(${CRSL_PROJECT_NAME} Interactivity Framework ComponentSystem)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core Widgets)

target_link_libraries(${CRSL_PROJECT_NAME} ${Qt5Core})
target_link_libraries(${CRSL_PROJECT_NAME} ${Qt5Widgets})

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)
