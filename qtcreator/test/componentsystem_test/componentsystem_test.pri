TEST_PROJECT_SOURCES = $$CPP_TESTS_TREE/componentsystem_test

SOURCES += \
    $$TEST_PROJECT_SOURCES/BaseComponentTest.cpp \
    $$TEST_PROJECT_SOURCES/ComponentDefinitionTest.cpp \
    $$TEST_PROJECT_SOURCES/ComponentDependenciesTest.cpp \
    $$TEST_PROJECT_SOURCES/ComponentInstallerTest.cpp \
    $$TEST_PROJECT_SOURCES/ComponentLoaderTest.cpp \
    $$TEST_PROJECT_SOURCES/ComponentManagerTest.cpp \
    $$TEST_PROJECT_SOURCES/CompositeComponentProviderTest.cpp \
    $$TEST_PROJECT_SOURCES/DefinitionConstuctorTest.cpp \
    $$TEST_PROJECT_SOURCES/DependencySolverTest.cpp \
    $$TEST_PROJECT_SOURCES/DirectoryComponentProviderTest.cpp \
    $$TEST_PROJECT_SOURCES/DirectoryWatchingComponentProviderTest.cpp \
    $$TEST_PROJECT_SOURCES/fakes/ComponentWithExtensions.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeComponentInstaller.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeComponentLoader.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeComponentLocationConstructorDelegate.cpp \
    $$TEST_PROJECT_SOURCES/fakes/FakeDefinitionParser.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockChildComponent.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockComponent.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentDependencies.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentLoader.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentManager.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentProvider.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockCompositeComponentProvider.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockDefaultConstructor.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockDirectoryComponentProvider.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockDirectoryWatchingComponentProvider.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockFileComponentProvider.cpp \
    $$TEST_PROJECT_SOURCES/fakes/MockFileSystemWatcher.cpp \
    $$TEST_PROJECT_SOURCES/fakes/TestDescriptionComponent.cpp\
    $$TEST_PROJECT_SOURCES/FileComponentProviderTest.cpp \
    $$TEST_PROJECT_SOURCES/main_componentsystem_test.cpp \
    $$TEST_PROJECT_SOURCES/ProxyComponentTest.cpp \
    $$TEST_PROJECT_SOURCES/Utils.cpp \
    $$TEST_PROJECT_SOURCES/XmlDefinitionParserTest.cpp \

HEADERS += \
    $$TEST_PROJECT_SOURCES/BaseComponentTest.h \
    $$TEST_PROJECT_SOURCES/ComponentDefinitionTest.h \
    $$TEST_PROJECT_SOURCES/ComponentDependenciesTest.h \
    $$TEST_PROJECT_SOURCES/ComponentInstallerTest.h \
    $$TEST_PROJECT_SOURCES/ComponentLoaderTest.h \
    $$TEST_PROJECT_SOURCES/ComponentManagerTest.h \
    $$TEST_PROJECT_SOURCES/CompositeComponentProviderTest.h \
    $$TEST_PROJECT_SOURCES/DefinitionConstuctorTest.h \
    $$TEST_PROJECT_SOURCES/DependencySolverTest.h \
    $$TEST_PROJECT_SOURCES/DirectoryComponentProviderTest.h \
    $$TEST_PROJECT_SOURCES/DirectoryWatchingComponentProviderTest.h \
    $$TEST_PROJECT_SOURCES/fakes/ComponentWithExtensions.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeComponentInstaller.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeComponentLoader.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeComponentLocationConstructorDelegate.h \
    $$TEST_PROJECT_SOURCES/fakes/FakeDefinitionParser.h \
    $$TEST_PROJECT_SOURCES/fakes/MockChildComponent.h \
    $$TEST_PROJECT_SOURCES/fakes/MockComponent.h \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentDependencies.h \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentLoader.h \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentManager.h \
    $$TEST_PROJECT_SOURCES/fakes/MockComponentProvider.h \
    $$TEST_PROJECT_SOURCES/fakes/MockCompositeComponentProvider.h \
    $$TEST_PROJECT_SOURCES/fakes/MockDefaultConstructor.h \
    $$TEST_PROJECT_SOURCES/fakes/MockDirectoryComponentProvider.h \
    $$TEST_PROJECT_SOURCES/fakes/MockDirectoryWatchingComponentProvider.h \
    $$TEST_PROJECT_SOURCES/fakes/MockFileComponentProvider.h \
    $$TEST_PROJECT_SOURCES/fakes/MockFileSystemWatcher.h \
    $$TEST_PROJECT_SOURCES/fakes/TestDescriptionComponent.h \
    $$TEST_PROJECT_SOURCES/FileComponentProviderTest.h \
    $$TEST_PROJECT_SOURCES/ProxyComponentTest.h \
    $$TEST_PROJECT_SOURCES/Utils.h \
    $$TEST_PROJECT_SOURCES/XmlDefinitionParserTest.h \

