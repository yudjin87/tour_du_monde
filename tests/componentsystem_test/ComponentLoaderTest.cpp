#include "ComponentLoaderTest.h"
#include "Utils.h"
#include "fakes/MockComponentLoader.h"

#include <carousel/componentsystem/ComponentLoader.h>
#include <carousel/componentsystem/IComponent.h>

#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

//------------------------------------------------------------------------------
static QString componentPath;
static QString exportCreateFuncOnly;
static QString exportDelFuncOnly;

//------------------------------------------------------------------------------
ComponentLoaderTest::ComponentLoaderTest(QObject *parent)
    : QObject(parent)
{
    componentPath = pathToLib("exportBothFuncs");
    exportCreateFuncOnly = pathToLib("exportCreateFuncOnly");
    exportDelFuncOnly = pathToLib("exportDelFuncOnly");
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::shouldSetupFile()
{
    ComponentLoader loader(componentPath);

    QCOMPARE(loader.fileName(), componentPath);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::shouldNotSetupFileNameIfFileDoesNotExist()
{
    ComponentLoader loader("/d/to/nowhere.ext");

    QVERIFY(loader.fileName().isEmpty());
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::instanceShouldCallLoad()
{
    MockComponentLoader loader(componentPath);
    loader.instance();

    QCOMPARE(loader.loadCalled, 1);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::instanceShouldNotCallLoadIfAlreadyDid()
{
    MockComponentLoader loader(componentPath);
    loader.instance();
    loader.instance();

    QCOMPARE(loader.loadCalled, 1);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::instanceShouldReturnIComponentPointer()
{
    MockComponentLoader loader(componentPath);
    IComponent *component = loader.instance();

    QVERIFY(component != nullptr);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::loadShouldLoadAndCreateComponent()
{
    MockComponentLoader loader(componentPath);
    QVERIFY(loader.getInstance() == nullptr);

    loader.load();

    QVERIFY(loader.getInstance() != nullptr);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::loadShouldReturnTrue()
{
    MockComponentLoader loader(componentPath);
    bool result = loader.load();

    QVERIFY(result);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::loadShouldNotCreateComponentIfAlreadyDid()
{
    MockComponentLoader loader(componentPath);
    loader.load();
    IComponent *component = loader.getInstance();
    loader.load();

    QCOMPARE(loader.getInstance(), component);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::loadShouldReturnTrueIfLoadedSecondTime()
{
    MockComponentLoader loader(componentPath);
    loader.load();
    bool result = loader.load();

    QVERIFY(result);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::loadShouldReturnFalseIfFileNameDoesNotSet()
{
    MockComponentLoader loader;
    bool result = loader.load();

    QVERIFY(!result);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::loadShouldReturnFalseIfCreateFunctionDoesNotExistInLib()
{
    MockComponentLoader loader(exportDelFuncOnly);
    bool result = loader.load();

    QVERIFY(!result);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::loadShouldReturnFalseIfReleaseFunctionDoesNotExistInLib()
{
    MockComponentLoader loader(exportCreateFuncOnly);
    bool result = loader.load();

    QVERIFY(!result);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::loadShouldSetupIsLoadFlag()
{
    MockComponentLoader loader(componentPath);
    QVERIFY(!loader.isLoaded());

    loader.load();

    QVERIFY(loader.isLoaded());
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::deleteInstanceShouldDeleteComponent()
{
    MockComponentLoader loader(componentPath);
    IComponent *component = loader.instance();
    QSignalSpy spy(component, SIGNAL(destroyed()));

    loader.deleteInstance();

    QCOMPARE(spy.size(), 1);
    QVERIFY(loader.getInstance() == nullptr);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::unloadShouldReturnFalseIfWasNotLoad()
{
    MockComponentLoader loader(componentPath);

    QVERIFY(!loader.deleteInstance());
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::unloadShouldSetupIsLoadFlag()
{
    MockComponentLoader loader(componentPath);
    loader.load();
    loader.deleteInstance();
    QVERIFY(!loader.isLoaded());
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::unloadShouldReturnTrueIfCan()
{
    MockComponentLoader loader(componentPath);
    loader.load();
    QVERIFY(loader.deleteInstance());
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::destructorShouldUnloadComponent()
{
    MockComponentLoader *loader = new MockComponentLoader(componentPath);
    IComponent *component = loader->instance();
    QSignalSpy spy(component, SIGNAL(destroyed()));

    delete loader;

    QCOMPARE(spy.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentLoaderTest::shouldNotSetFileUntilUnload()
{
    MockComponentLoader loader(componentPath);
    loader.load();
    loader.setFileName(exportCreateFuncOnly);

    QCOMPARE(loader.fileName(), componentPath);
}

//------------------------------------------------------------------------------
