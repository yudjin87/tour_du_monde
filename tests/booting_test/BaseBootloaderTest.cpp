#include "BaseBootloaderTest.h"
#include "fakes/BootloaderMock.h"

#include <carousel/booting/BootloaderBase.h>
#include <QtTest/QtTest>

BaseBootloaderTest::BaseBootloaderTest(QObject *parent)
    : QObject(parent)
{
}

void BaseBootloaderTest::shouldCreateDefaultLogger()
{
    BootloaderMock loader;
    loader.callCreateLogger();

    ILoggerEngineCreator *defaultLogger = loader.logger();

    QVERIFY(defaultLogger != nullptr);
}

void BaseBootloaderTest::shouldCreateDefaultComponentProvider()
{
    BootloaderMock loader;
    loader.callCreateComponentProvider();

    IComponentProvider *defaultComponentProvider = loader.componentProvider();

    QVERIFY(defaultComponentProvider != nullptr);
}

void BaseBootloaderTest::shouldCreateDefaultComponentManager()
{
    BootloaderMock loader;
    loader.callCreateComponentManager();

    IComponentManager *defaultComponentManager = loader.componentManager();

    QVERIFY(defaultComponentManager != nullptr);
}

void BaseBootloaderTest::shouldCreateDefaultServiceLocator()
{
    BootloaderMock loader;
    loader.callCreateServiceLocator();

    IServiceLocator *defaultServiceLocator = loader.serviceLocator();

    QVERIFY(defaultServiceLocator != nullptr);
}

void BaseBootloaderTest::canRunOnlyOncePerInstance()
{
    BootloaderMock loader;
    QCOMPARE(loader.runAttemptsCount(), 0);

    loader.run();
    QCOMPARE(loader.runAttemptsCount(), 1);

    loader.run();
    QCOMPARE(loader.runAttemptsCount(), 1);
}

