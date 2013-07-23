###############################################################################
# utils project
set(CRSL_PROJECT_NAME "org.carousel.JsScripting")
set(CRSL_TARGET_TYPE "components")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/JsScriptingComponent.cpp 
    ${CRSL_TARGET_SOURCES}/JsScriptingInteractiveExtension.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptConsole.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptService.cpp 
    ${CRSL_TARGET_SOURCES}/ServiceLocatorWrapper.cpp 
)
	
######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/IScriptService.h 
    ${CRSL_TARGET_HEADERS}/jsscripting_global.h 
    ${CRSL_TARGET_HEADERS}/JsScriptingComponent.h 
    ${CRSL_TARGET_HEADERS}/JsScriptingInteractiveExtension.h 
    ${CRSL_TARGET_HEADERS}/ScriptConsole.h 
    ${CRSL_TARGET_HEADERS}/ScriptService.h 
    ${CRSL_TARGET_HEADERS}/ServiceLocatorWrapper.h 
)

######################################################################
# Forms
set(__FORMS
    ${CRSL_TARGET_SOURCES}/ScriptConsole.ui 
)

######################################################################
# Resources
set(__RESOURCES
    ${CRSL_TARGET_SOURCES}/jsscripting.qrc 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/org.carousel.JsScripting.definition 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})
qt5_wrap_ui(__UI_HEADERS ${__FORMS})
qt5_add_resources(__GENERATED_RESOURCES ${__RESOURCES})

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS})
source_group("moc" FILES ${__HEADERS_MOC})
source_group("forms" FILES ${__UI_HEADERS} ${__FORMS})
source_group("res" FILES ${__GENERATED_RESOURCES} ${__RESOURCES})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__OTHER_FILES} ${__FORMS} ${__UI_HEADERS} ${__RESOURCES} ${__GENERATED_RESOURCES} )

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} org.carousel.Interactivity)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core Widgets Script)

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)
