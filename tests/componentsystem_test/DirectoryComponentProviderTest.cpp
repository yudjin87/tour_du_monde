#include "DirectoryComponentProviderTest.h"
#include "fakes/FakeDefinitionParser.h"
#include "fakes/MockDirectoryComponentProvider.h"
#include "Utils.h"

#include <componentsystem/DirectoryComponentProvider.h>
#include <componentsystem/IComponent.h>

#include <QtCore/QFile>
#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
typedef AutoComponentProvider<DirectoryComponentProvider> AutoDirectoryComponentProvider;

//------------------------------------------------------------------------------
DirectoryComponentProviderTest::DirectoryComponentProviderTest(QObject *parent)
    : QObject(parent)
    , definitionsLocation(pathToComponentsDir())
{
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::shouldNotSetupWrongDirectoryPath()
{
    AutoDirectoryComponentProvider provider("/path/to/nowhere");

    QVERIFY(provider.path().isEmpty());
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::initialize_shouldReturnTrue()
{
    AutoDirectoryComponentProvider provider(definitionsLocation);

    provider.initialize();

    QCOMPARE(provider.isInitialized(), true);
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::initialize_shouldCallUpdate()
{
    MockDirectoryComponentProvider provider;

    provider.initialize();

    QCOMPARE(provider.updateCalled, 1);
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::initialize_shouldReturnFalseIfPathIsEmpty()
{
    AutoDirectoryComponentProvider provider;

    provider.initialize();

    QCOMPARE(provider.isInitialized(), false);
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::update_shouldCallReadOnParserForEachDefinition()
{
    MockDirectoryComponentProvider provider(definitionsLocation);
    provider.update();

    QCOMPARE(provider.providersCreated, 2);
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::update_shouldReturnTwoComponents()
{
    MockDirectoryComponentProvider provider(definitionsLocation);
    QList<IComponent *> components = provider.update();

    QCOMPARE(components.size(), 2);
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::update_shouldPopulateTwoComponents()
{
    MockDirectoryComponentProvider provider(definitionsLocation);
    provider.update();

    QCOMPARE(provider.components().size(), 2);
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::update_shouldPopulateOnlyWithNewComponents()
{
    AutoDirectoryComponentProvider provider(definitionsLocation);

    // Discover first two components
    provider.initialize();

    QString newComponentDef = "<component name=\"TestComponent2\"></component>";
    QFile newComponentFile(definitionsLocation + "/NewComponent.definition");
    QVERIFY(newComponentFile.open(QIODevice::WriteOnly));
    newComponentFile.write(newComponentDef.toLatin1());
    newComponentFile.close();

    provider.update();

    QVERIFY(newComponentFile.remove());

    QCOMPARE(provider.components().size(), 3);
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::update_shouldReturnOnlyNewComponents()
{
    AutoDirectoryComponentProvider provider(definitionsLocation);

    // Discover first two components
    provider.initialize();

    QString newComponentDef = "<component name=\"TestComponent2\"></component>";
    QFile newComponentFile(definitionsLocation + "/NewComponent.definition");
    QVERIFY(newComponentFile.open(QIODevice::WriteOnly));
    newComponentFile.write(newComponentDef.toLatin1());
    newComponentFile.close();

    QList<IComponent *> components = provider.update();

    QVERIFY(newComponentFile.remove());

    QCOMPARE(components.size(), 1);
}

//------------------------------------------------------------------------------
void DirectoryComponentProviderTest::update_shouldNotPopulateComponentIfItsInitializationFault()
{
    MockDirectoryComponentProvider provider(definitionsLocation);

    FakeFileComponentProvider::initializeReturnValue = false;
    provider.update();
    FakeFileComponentProvider::initializeReturnValue = true;

    QCOMPARE(provider.components().size(), 0);
}

//------------------------------------------------------------------------------
