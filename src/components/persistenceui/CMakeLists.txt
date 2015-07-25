###############################################################################
# PersistenceUI project
set(CRSL_PROJECT_NAME "org.carousel.PersistenceUI")
set(CRSL_TARGET_TYPE "components")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/LoadOperation.cpp 
    ${CRSL_TARGET_SOURCES}/PersistenceUIComponent.cpp 
    ${CRSL_TARGET_SOURCES}/PersistenceUIInteractiveExtension.cpp 
    ${CRSL_TARGET_SOURCES}/SaveOperation.cpp 
)
	
######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/LoadOperation.h 
    ${CRSL_TARGET_HEADERS}/persistenceUI_api.h 
    ${CRSL_TARGET_HEADERS}/PersistenceUIComponent.h 
    ${CRSL_TARGET_HEADERS}/PersistenceUIInteractiveExtension.h 
    ${CRSL_TARGET_HEADERS}/SaveOperation.h 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/org.carousel.PersistenceUI.definition 
)

######################################################################
# Resources
set(__RESOURCES
    ${CRSL_TARGET_SOURCES}/persistenceui.qrc 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})
qt5_add_resources(__GENERATED_RESOURCES ${__RESOURCES})

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS})
source_group("moc" FILES ${__HEADERS_MOC})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__OTHER_FILES} ${__RESOURCES} ${__GENERATED_RESOURCES})

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} org.carousel.Interactivity org.carousel.Persistence)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core Widgets)

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)
