#include "BaseBootloaderTest.h"
#include "fakes/BootloaderMock.h"

#include <booting/BootloaderBase.h>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
BaseBootloaderTest::BaseBootloaderTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void BaseBootloaderTest::shouldCreateDefaultLogger()
{
    BootloaderMock loader;
    loader.callCreateLogger();

    ILogger *p_defaultLogger = loader.logger();

    QVERIFY(p_defaultLogger != nullptr);
}

//------------------------------------------------------------------------------
void BaseBootloaderTest::shouldCreateDefaultComponentProvider()
{
    BootloaderMock loader;
    loader.callCreateComponentProvider();

    IComponentProvider *p_defaultComponentProvider = loader.componentProvider();

    QVERIFY(p_defaultComponentProvider != nullptr);
}

//------------------------------------------------------------------------------
void BaseBootloaderTest::shouldCreateDefaultComponentManager()
{
    BootloaderMock loader;
    loader.callCreateComponentManager();

    IComponentManager *p_defaultComponentManager = loader.componentManager();

    QVERIFY(p_defaultComponentManager != nullptr);
}

//------------------------------------------------------------------------------
void BaseBootloaderTest::shouldCreateDefaultServiceLocator()
{
    BootloaderMock loader;
    loader.callCreateServiceLocator();

    IServiceLocator *p_defaultServiceLocator = loader.serviceLocator();

    QVERIFY(p_defaultServiceLocator != nullptr);
}

//------------------------------------------------------------------------------
void BaseBootloaderTest::shouldCreateDefaultMainWindow()
{
    BootloaderMock loader;
    loader.callCreateMainWindow();

    QMainWindow *p_defaultMainWindow = loader.mainWindow();

    QVERIFY(p_defaultMainWindow != nullptr);
}

//------------------------------------------------------------------------------
void BaseBootloaderTest::canRunOnlyOncePerInstance()
{
    BootloaderMock loader;
    QCOMPARE(loader.runAttemptsCount(), 0);

    loader.run();
    QCOMPARE(loader.runAttemptsCount(), 1);

    loader.run();
    QCOMPARE(loader.runAttemptsCount(), 1);
}

//------------------------------------------------------------------------------
