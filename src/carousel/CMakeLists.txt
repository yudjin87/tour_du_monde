##############################################################################
# booting project
set(CRSL_PROJECT_NAME "Carousel")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/booting/BootloaderBase.cpp 
    ${CRSL_TARGET_SOURCES}/booting/CarouselBootloader.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/AbsolutePathComponentLocationConstructorDelegate.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/BaseComponent.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ComponentCollection.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ComponentDefinition.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ComponentDependencies.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ComponentInstaller.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ComponentLoader.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ComponentManager.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/CompositeComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/DefinitionConstuctor.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/DependenciesSolvingResult.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/DependencySolver.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/DirectoryComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/DirectoryInstaller.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/DirectoryWatchingComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/FileComponentProvider.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ParentDefinition.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ParentDefinitions.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/ProxyComponent.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/Version.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/WebInstaller.cpp 
    ${CRSL_TARGET_SOURCES}/componentsystem/XmlDefinitionParser.cpp 
    ${CRSL_TARGET_SOURCES}/logging/LoggerFacade.cpp 
    ${CRSL_TARGET_SOURCES}/logging/NullLogger.cpp 
    ${CRSL_TARGET_SOURCES}/logging/TextLogger.cpp 
    ${CRSL_TARGET_SOURCES}/utils/FileUtils.cpp 
    ${CRSL_TARGET_SOURCES}/utils/ServiceLocator.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/booting/BootloaderBase.h 
    ${CRSL_TARGET_HEADERS}/booting/CarouselBootloader.h 
    ${CRSL_TARGET_HEADERS}/booting/IBootloader.h 
    ${CRSL_TARGET_HEADERS}/carousel_global.h 
    ${CRSL_TARGET_HEADERS}/commands/IUndoableCommand.h 
    ${CRSL_TARGET_HEADERS}/commands/IUndoStack.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/AbsolutePathComponentLocationConstructorDelegate.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/BaseComponent.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentCollection.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentDefinition.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentDependencies.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentExport.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentExport.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentInstaller.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentLoader.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentManager.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/CompositeComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/DefinitionConstuctor.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/DependenciesSolvingResult.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/DependencySolver.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/DirectoryComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/DirectoryInstaller.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/DirectoryWatchingComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/FileComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IComponent.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IComponentDependencies.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IComponentExtension.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IComponentInstaller.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IComponentLoader.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IComponentLocationConstructorDelegate.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IComponentManager.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IDefinitionParser.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/IDirectoryComponentProvider.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ParentDefinition.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ParentDefinitions.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/ProxyComponent.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/Version.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/WebInstaller.h 
    ${CRSL_TARGET_HEADERS}/componentsystem/XmlDefinitionParser.h 
    ${CRSL_TARGET_HEADERS}/logging/ILoggerEngine.h 
    ${CRSL_TARGET_HEADERS}/logging/ILoggerEngineCreator.h 
    ${CRSL_TARGET_HEADERS}/logging/LoggerFacade.h 
    ${CRSL_TARGET_HEADERS}/logging/NullLogger.h 
    ${CRSL_TARGET_HEADERS}/logging/TextLogger.h 
    ${CRSL_TARGET_HEADERS}/utils/FileUtils.h 
    ${CRSL_TARGET_HEADERS}/utils/IServiceLocator.h 
    ${CRSL_TARGET_HEADERS}/utils/ListDictionary.h 
    ${CRSL_TARGET_HEADERS}/utils/ObservableList.h 
    ${CRSL_TARGET_HEADERS}/utils/ServiceLocator.h 
    ${CRSL_TARGET_HEADERS}/utils/TypeObjectsMap.h 
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

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core Xml XmlPatterns)

