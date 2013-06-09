###############################################################################
# componentsystem project
set(CRSL_PROJECT_NAME "ComponentSystem")
include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/AbsolutePathComponentLocationConstructorDelegate.cpp 
    ${CRSL_TARGET_SOURCES}/BaseComponent.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentDefinition.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentDependencies.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentInstaller.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentLoader.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentManager.cpp 
    ${CRSL_TARGET_SOURCES}/ComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/CompositeComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/DefinitionConstuctor.cpp 
    ${CRSL_TARGET_SOURCES}/DependenciesSolvingResult.cpp 
    ${CRSL_TARGET_SOURCES}/DependencySolver.cpp 
    ${CRSL_TARGET_SOURCES}/DirectoryComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/DirectoryInstaller.cpp 
    ${CRSL_TARGET_SOURCES}/DirectoryWatchingComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/FileComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/IComponent.cpp 
    ${CRSL_TARGET_SOURCES}/ProxyComponent.cpp 
    ${CRSL_TARGET_SOURCES}/WebInstaller.cpp 
    ${CRSL_TARGET_SOURCES}/XmlDefinitionParser.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/AbsolutePathComponentLocationConstructorDelegate.h 
    ${CRSL_TARGET_HEADERS}/BaseComponent.h 
    ${CRSL_TARGET_HEADERS}/ComponentDefinition.h 
    ${CRSL_TARGET_HEADERS}/ComponentDependencies.h 
    ${CRSL_TARGET_HEADERS}/ComponentExport.h 
    ${CRSL_TARGET_HEADERS}/ComponentExport.h 
    ${CRSL_TARGET_HEADERS}/ComponentInstaller.h 
    ${CRSL_TARGET_HEADERS}/ComponentLoader.h 
    ${CRSL_TARGET_HEADERS}/ComponentManager.h 
    ${CRSL_TARGET_HEADERS}/ComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem_global.h 
    ${CRSL_TARGET_HEADERS}/CompositeComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/DefinitionConstuctor.h 
    ${CRSL_TARGET_HEADERS}/DependenciesSolvingResult.h 
    ${CRSL_TARGET_HEADERS}/DependencySolver.h 
    ${CRSL_TARGET_HEADERS}/DirectoryComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/DirectoryInstaller.h 
    ${CRSL_TARGET_HEADERS}/DirectoryWatchingComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/FileComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/IComponent.h 
    ${CRSL_TARGET_HEADERS}/IComponentDependencies.h 
    ${CRSL_TARGET_HEADERS}/IComponentExtension.h 
    ${CRSL_TARGET_HEADERS}/IComponentInstaller.h 
    ${CRSL_TARGET_HEADERS}/IComponentLoader.h 
    ${CRSL_TARGET_HEADERS}/IComponentLocationConstructorDelegate.h 
    ${CRSL_TARGET_HEADERS}/IComponentManager.h 
    ${CRSL_TARGET_HEADERS}/IComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/IDefinitionParser.h 
    ${CRSL_TARGET_HEADERS}/IDirectoryComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/ProxyComponent.h 
    ${CRSL_TARGET_HEADERS}/WebInstaller.h 
    ${CRSL_TARGET_HEADERS}/XmlDefinitionParser.h 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})

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
qt5_use_modules(${CRSL_PROJECT_NAME} Core Xml)
