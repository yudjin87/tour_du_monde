###############################################################################
# utils project
set(CRSL_PROJECT_NAME "org.carousel.JsScriptingUI")
set(CRSL_TARGET_TYPE "components")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/CodeHighlighter.cpp 
    ${CRSL_TARGET_SOURCES}/ColorTheme.cpp 
    ${CRSL_TARGET_SOURCES}/JsScriptingUIComponent.cpp 
    ${CRSL_TARGET_SOURCES}/JsScriptingUIInteractiveExtension.cpp 
    ${CRSL_TARGET_SOURCES}/LexemeAppearance.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptCollectionDialog.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptCollectionModel.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptConsoleView.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptUnitView.cpp 
    ${CRSL_TARGET_SOURCES}/ShowScriptsOperation.cpp 
)
	
######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/CodeHighlighter.h 
    ${CRSL_TARGET_HEADERS}/ColorTheme.h 
    ${CRSL_TARGET_HEADERS}/jsscriptingui_global.h 
    ${CRSL_TARGET_HEADERS}/JsScriptingUIComponent.h 
    ${CRSL_TARGET_HEADERS}/JsScriptingUIInteractiveExtension.h 
    ${CRSL_TARGET_HEADERS}/LexemeAppearance.h 
    ${CRSL_TARGET_HEADERS}/ScriptCollectionDialog.h 
    ${CRSL_TARGET_HEADERS}/ScriptCollectionModel.h 
    ${CRSL_TARGET_HEADERS}/ScriptConsoleView.h 
    ${CRSL_TARGET_HEADERS}/ScriptUnitView.h 
    ${CRSL_TARGET_HEADERS}/ShowScriptsOperation.h 
)

######################################################################
# Forms
set(__FORMS
    ${CRSL_TARGET_SOURCES}/ScriptCollectionDialog.ui 
    ${CRSL_TARGET_SOURCES}/ScriptConsoleView.ui 
    ${CRSL_TARGET_SOURCES}/ScriptUnitView.ui 
)

######################################################################
# Resources
set(__RESOURCES
    ${CRSL_TARGET_SOURCES}/jsscriptingui.qrc 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/org.carousel.JsScriptingUI.definition 
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
target_link_libraries(${CRSL_PROJECT_NAME} org.carousel.Interactivity org.carousel.JsScripting)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core Widgets Script)

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)
