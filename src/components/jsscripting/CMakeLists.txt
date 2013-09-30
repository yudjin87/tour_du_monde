###############################################################################
# utils project
set(CRSL_PROJECT_NAME "org.carousel.JsScripting")
set(CRSL_TARGET_TYPE "components")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/CarouselScriptEngineConfigurationDelegate.cpp 
    ${CRSL_TARGET_SOURCES}/JsScriptingComponent.cpp 
    ${CRSL_TARGET_SOURCES}/prototypes/ComponentDefinitionPrototype.cpp 
    ${CRSL_TARGET_SOURCES}/prototypes/PointClass.cpp 
    ${CRSL_TARGET_SOURCES}/prototypes/PointFPrototype.cpp 
    ${CRSL_TARGET_SOURCES}/prototypes/PointPrototype.cpp 
    ${CRSL_TARGET_SOURCES}/prototypes/RectFPrototype.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptCollection.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptConsole.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptingService.cpp 
    ${CRSL_TARGET_SOURCES}/ScriptUnit.cpp 
    ${CRSL_TARGET_SOURCES}/ServiceLocatorWrapper.cpp 
    ${CRSL_TARGET_SOURCES}/SimpleCompleter.cpp 
)
	
######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/CarouselScriptEngineConfigurationDelegate.h 
    ${CRSL_TARGET_HEADERS}/IOutputHandler.h 
    ${CRSL_TARGET_HEADERS}/IScriptCollection.h 
    ${CRSL_TARGET_HEADERS}/IScriptConsole.h 
    ${CRSL_TARGET_HEADERS}/IScriptEngineConfigurationDelegate.h 
    ${CRSL_TARGET_HEADERS}/IScriptEngineFactory.h 
    ${CRSL_TARGET_HEADERS}/IScriptExtension.h 
    ${CRSL_TARGET_HEADERS}/IScriptingService.h 
    ${CRSL_TARGET_HEADERS}/IScriptUnit.h 
    ${CRSL_TARGET_HEADERS}/jsscripting_global.h 
    ${CRSL_TARGET_HEADERS}/JsScriptingComponent.h 
    ${CRSL_TARGET_HEADERS}/prototypes/ComponentDefinitionPrototype.h 
    ${CRSL_TARGET_HEADERS}/prototypes/PointClass.h 
    ${CRSL_TARGET_HEADERS}/prototypes/PointFPrototype.h 
    ${CRSL_TARGET_HEADERS}/prototypes/PointPrototype.h 
    ${CRSL_TARGET_HEADERS}/prototypes/RectFPrototype.h 
    ${CRSL_TARGET_HEADERS}/ScriptCollection.h 
    ${CRSL_TARGET_HEADERS}/ScriptConsole.h 
    ${CRSL_TARGET_HEADERS}/ScriptingService.h 
    ${CRSL_TARGET_HEADERS}/ScriptUnit.h 
    ${CRSL_TARGET_HEADERS}/ServiceLocatorWrapper.h 
    ${CRSL_TARGET_HEADERS}/SimpleCompleter.h 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/org.carousel.JsScripting.definition 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})

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
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__OTHER_FILES})

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} Carousel)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core Gui Script)

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)
