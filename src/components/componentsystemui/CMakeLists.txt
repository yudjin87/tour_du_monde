###############################################################################
# componentsystemui project
set(CRSL_PROJECT_NAME "org.carousel.ComponentSystemUI")
set(CRSL_TARGET_TYPE "components")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/ComponentDefinitionsModel.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentsDialog.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentSystemUIComponent.cpp 
    ${CRSL_TARGET_SOURCES}/EnableComponentCommand.cpp 
    ${CRSL_TARGET_SOURCES}/InstallComponentsCommand.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/ComponentDefinitionsModel.h 
    ${CRSL_TARGET_HEADERS}/ComponentsDialog.h 
    ${CRSL_TARGET_HEADERS}/componentsystem_ui_global.h 
    ${CRSL_TARGET_HEADERS}/ComponentSystemUIComponent.h 
    ${CRSL_TARGET_HEADERS}/EnableComponentCommand.h 
    ${CRSL_TARGET_HEADERS}/InstallComponentsCommand.h 
)

######################################################################
# Forms
set(__FORMS
    ${CRSL_TARGET_SOURCES}/ComponentsDialog.ui 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/org.carousel.ComponentSystemUI.definition 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})
qt5_wrap_ui(__UI_HEADERS ${__FORMS})

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS} ${__OTHER_FILES})
source_group("moc" FILES ${__HEADERS_MOC})
source_group("forms" FILES ${__UI_HEADERS} ${__FORMS})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__FORMS} ${__UI_HEADERS} ${__OTHER_FILES})

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} ComponentSystem Framework org.carousel.Interactivity)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core Widgets)

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)
