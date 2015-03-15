#include "BaseComponentTest.h"
#include "ComponentManagerTest.h"
#include "CompositeComponentProviderTest.h"
#include "DependencySolverTest.h"
#include "ComponentDefinitionTest.h"
#include "ProxyComponentTest.h"
#include "XmlDefinitionParserTest.h"
#include "ComponentLoaderTest.h"
#include "DirectoryComponentProviderTest.h"
#include "ComponentDependenciesTest.h"
#include "DirectoryWatchingComponentProviderTest.h"
#include "FileComponentProviderTest.h"
#include "DefinitionConstuctorTest.h"
#include "ComponentInstallerTest.h"
#include "VersionTest.h"

#include <carousel/logging/LoggerFacade.h>
#include <carousel/logging/NullLogger.h>

#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("componentsystem_test");
    QCoreApplication::setOrganizationName("carousel");
    NullLogger log;
    LoggerFacade::installLoggerEngineCreator(&log);

    BaseComponentTest baseComponentTest;
    QTest::qExec(&baseComponentTest, argc, argv);

    CompositeComponentProviderTest compositeComponentProviderTest;
    QTest::qExec(&compositeComponentProviderTest, argc, argv);

    DependencySolverTest dependencySolverTest;
    QTest::qExec(&dependencySolverTest, argc, argv);

    ComponentManagerTest componentManagerTest;
    QTest::qExec(&componentManagerTest, argc, argv);

    ComponentDefinitionTest componentDescriptionExtensionTest;
    QTest::qExec(&componentDescriptionExtensionTest, argc, argv);

    ProxyComponentTest proxyComponentTest;
    QTest::qExec(&proxyComponentTest, argc, argv);

    XmlDefinitionParserTest xmlDescriptionParserTest;
    QTest::qExec(&xmlDescriptionParserTest, argc, argv);

    ComponentLoaderTest componentLoaderTest;
    QTest::qExec(&componentLoaderTest, argc, argv);

    DirectoryComponentProviderTest directoryComponentProviderTest;
    QTest::qExec(&directoryComponentProviderTest, argc, argv);

    ComponentDependenciesTest componentDependenciesTest;
    QTest::qExec(&componentDependenciesTest, argc, argv);

    DirectoryWatchingComponentProviderTest directoryWatchingComponentProviderTest;
    QTest::qExec(&directoryWatchingComponentProviderTest, argc, argv);

    FileComponentProviderTest fileComponentProviderTest;
    QTest::qExec(&fileComponentProviderTest, argc, argv);

    DefinitionConstuctorTest definitionConstuctorTest;
    QTest::qExec(&definitionConstuctorTest, argc, argv);

    ComponentInstallerTest componentInstallerTest;
    QTest::qExec(&componentInstallerTest, argc, argv);

    VersionTest versionTest;
    QTest::qExec(&versionTest, argc, argv);

    // clean stuff
    QSettings settings;
    QDir settingsDir(settings.fileName());
    settingsDir.remove(settings.fileName());
    settingsDir.cdUp();
    settingsDir.rmdir(settingsDir.path());

    return 0;
}


