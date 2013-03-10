cmake_minimum_required(VERSION 2.8)

###############################################################################
# componentsystem project
set(CRSL_PROJECT_NAME "ComponentSystem")
include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/BaseComponent.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentDefinition.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentDependencies.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentInitialiser.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentLoader.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentManager.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/CompositeComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/DependenciesSolvingResult.cpp 
    ${CRSL_TARGET_SOURCES}/DependencySolver.cpp 
    ${CRSL_TARGET_SOURCES}/DirectoryComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/DirectoryWatchingComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/FileComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/ProxyComponent.cpp 
    ${CRSL_TARGET_SOURCES}/XmlDefinitionParser.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/BaseComponent.h 
    ${CRSL_TARGET_HEADERS}/ComponentDefinition.h 
    ${CRSL_TARGET_HEADERS}/ComponentDependencies.h 
    ${CRSL_TARGET_HEADERS}/ComponentInitialiser.h 
    ${CRSL_TARGET_HEADERS}/ComponentLoader.h 
    ${CRSL_TARGET_HEADERS}/ComponentManager.h 
    ${CRSL_TARGET_HEADERS}/ComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem_global.h 
    ${CRSL_TARGET_HEADERS}/CompositeComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/DependenciesSolvingResult.h 
    ${CRSL_TARGET_HEADERS}/DependencySolver.h 
    ${CRSL_TARGET_HEADERS}/DirectoryComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/DirectoryWatchingComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/FileComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/IComponent.h 
    ${CRSL_TARGET_HEADERS}/IComponentDefinition.h 
    ${CRSL_TARGET_HEADERS}/IComponentDependencies.h 
    ${CRSL_TARGET_HEADERS}/IComponentExtension.h 
    ${CRSL_TARGET_HEADERS}/IComponentInitialiser.h 
    ${CRSL_TARGET_HEADERS}/IComponentLoader.h 
    ${CRSL_TARGET_HEADERS}/IComponentManager.h 
    ${CRSL_TARGET_HEADERS}/IComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/IDefinitionParser.h 
    ${CRSL_TARGET_HEADERS}/IDirectoryComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/ProxyComponent.h 
    ${CRSL_TARGET_HEADERS}/XmlDefinitionParser.h 
)

######################################################################
# Qt generated files
qt4_wrap_cpp(__HEADERS_MOC ${__HEADERS})

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS})
source_group("moc" FILES ${__HEADERS_MOC})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC})

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} Logging Utils)

###############################################################################
# Qt dependencies
target_link_libraries(${CRSL_PROJECT_NAME} ${QT_QTCORE_LIBRARY} ${QT_QTXML_LIBRARY})
