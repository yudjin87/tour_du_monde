PROJECT_SOURCES = $$CPP_SOURCE_TREE/componentsystem
PROJECT_HEADERS = $$HPP_SOURCE_TREE/componentsystem

SOURCES += \
    $$PROJECT_SOURCES/BaseComponent.cpp \
    $$PROJECT_SOURCES/ComponentDefinition.cpp \
    $$PROJECT_SOURCES/ComponentDependencies.cpp \
    $$PROJECT_SOURCES/ComponentInitialiser.cpp \
    $$PROJECT_SOURCES/ComponentLoader.cpp \
    $$PROJECT_SOURCES/ComponentManager.cpp \
    $$PROJECT_SOURCES/ComponentProvider.cpp \
    $$PROJECT_SOURCES/CompositeComponentProvider.cpp \
    $$PROJECT_SOURCES/DefinitionConstuctor.cpp \
    $$PROJECT_SOURCES/DependenciesSolvingResult.cpp \
    $$PROJECT_SOURCES/DependencySolver.cpp \
    $$PROJECT_SOURCES/DirectoryComponentProvider.cpp \
    $$PROJECT_SOURCES/DirectoryWatchingComponentProvider.cpp \
    $$PROJECT_SOURCES/FileComponentProvider.cpp \
    $$PROJECT_SOURCES/ProxyComponent.cpp \
    $$PROJECT_SOURCES/XmlDefinitionParser.cpp \
    $$PROJECT_SOURCES/AbsolutePathComponentLocationConstructorDelegate.cpp

HEADERS += \
    $$PROJECT_HEADERS/BaseComponent.h \
    $$PROJECT_HEADERS/ComponentDefinition.h \
    $$PROJECT_HEADERS/ComponentDependencies.h \
    $$PROJECT_HEADERS/ComponentExport.h \
    $$PROJECT_HEADERS/ComponentInitialiser.h \
    $$PROJECT_HEADERS/ComponentLoader.h \
    $$PROJECT_HEADERS/ComponentManager.h \
    $$PROJECT_HEADERS/ComponentProvider.h \
    $$PROJECT_HEADERS/componentsystem_global.h \
    $$PROJECT_HEADERS/CompositeComponentProvider.h \
    $$PROJECT_HEADERS/DefinitionConstuctor.h \
    $$PROJECT_HEADERS/DependenciesSolvingResult.h \
    $$PROJECT_HEADERS/DependencySolver.h \
    $$PROJECT_HEADERS/DirectoryComponentProvider.h \
    $$PROJECT_HEADERS/DirectoryWatchingComponentProvider.h \
    $$PROJECT_HEADERS/FileComponentProvider.h \
    $$PROJECT_HEADERS/IComponent.h \
    $$PROJECT_HEADERS/IComponentDependencies.h \
    $$PROJECT_HEADERS/IComponentExtension.h \
    $$PROJECT_HEADERS/IComponentInitialiser.h \
    $$PROJECT_HEADERS/IComponentLoader.h \
    $$PROJECT_HEADERS/IComponentManager.h \
    $$PROJECT_HEADERS/IComponentProvider.h \
    $$PROJECT_HEADERS/IDefinitionParser.h \
    $$PROJECT_HEADERS/IDirectoryComponentProvider.h \
    $$PROJECT_HEADERS/ProxyComponent.h \
    $$PROJECT_HEADERS/XmlDefinitionParser.h \
    $$PROJECT_HEADERS/IComponentLocationConstructorDelegate.h \
    $$PROJECT_HEADERS/AbsolutePathComponentLocationConstructorDelegate.h

