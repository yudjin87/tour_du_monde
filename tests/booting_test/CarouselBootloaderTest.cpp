#include "CarouselBootloaderTest.h"
#include "fakes/CarouselBootloaderMock.h"
#include "fakes/CarouselBootloaderProviderMock.h"
#include "fakes/CarouselBootloader_ComponentManagerFixture.h"

#include <booting/CarouselBootloader.h>
#include <componentsystem/ComponentManager.h>
#include <componentsystem/ComponentProvider.h>
#include <logging/ILogger.h>
#include <utils/IServiceLocator.h>
#include <utils/ObservableList.h>

#include <QtGui/QMainWindow>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
CarouselBootloaderTest::CarouselBootloaderTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::canRunLoading()
{
    CarouselBootloader carouselBootloader;
    carouselBootloader.run();
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallCreateLoggerOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createLoggerCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallCreateComponentProviderOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createComponentProviderCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallCreateComponentManagerOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createComponentManagerCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallCreateServiceLocatorOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createServiceLocatorCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallCreateMainWindowOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createMainWindowCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallConfigureComponentProviderOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.configureComponentProviderCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallConfigureComponentManagerOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.configureComponentManagerCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallConfigureServiceLocatorOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.configureServiceLocatorCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallInitialiseComponentProviderOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.initialiseComponentProviderCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldCallRunSequenceInOrderOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    const QStringList &methodCalls = mockLoader.methodCalls();

    QCOMPARE(methodCalls[0], QString("_createLogger"));
    QCOMPARE(methodCalls[1], QString("_createComponentManager"));
    QCOMPARE(methodCalls[2], QString("_createComponentProvider"));
    QCOMPARE(methodCalls[3], QString("_createServiceLocator"));
    QCOMPARE(methodCalls[4], QString("_createMainWindow"));
    QCOMPARE(methodCalls[5], QString("_configureComponentProvider"));
    QCOMPARE(methodCalls[6], QString("_configureServiceLocator"));
    QCOMPARE(methodCalls[7], QString("_initialiseComponentProvider"));
    QCOMPARE(methodCalls[8], QString("_configureComponentManager"));

}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldInitialiseComponentProviderOnRun()
{
    CarouselBootloaderProviderMock mockLoader;
    mockLoader.run();

    bool initialiseCalled = mockLoader.componentProvider().initialiseCalled();
    QVERIFY(initialiseCalled);
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::configuringComponentManagerShouldAddComponentsToIt()
{
    CarouselBootloader_ComponentManagerFixture fixture;
    fixture.run();

    IComponentManager& manager = fixture.componentManager();

    QCOMPARE(manager.components().count(), 2);
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::configuringServiceLocatorShouldAddComponentProviderToServices()
{
    CarouselBootloader carouselBootloader;
    carouselBootloader.run();

    IServiceLocator *serviceLocator = carouselBootloader.serviceLocator();
    QVERIFY(serviceLocator != nullptr);

    IComponentProvider *provider = serviceLocator->locate<IComponentProvider>();

    QVERIFY(dynamic_cast<ComponentProvider *>(provider) != nullptr);
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::configuringServiceLocatorShouldAddLoggerToServices()
{
    CarouselBootloader carouselBootloader;
    carouselBootloader.run();

    IServiceLocator *serviceLocator = carouselBootloader.serviceLocator();
    QVERIFY(serviceLocator != nullptr);

    ILogger *logger = serviceLocator->locate<ILogger>();

    QVERIFY(logger != nullptr);
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::configuringServiceLocatorShouldAddComponentManagerToServices()
{
    CarouselBootloader carouselBootloader;
    carouselBootloader.run();

    IServiceLocator *serviceLocator = carouselBootloader.serviceLocator();
    QVERIFY(serviceLocator != nullptr);

    IComponentManager *componentManager  = serviceLocator->locate<IComponentManager>();

    QVERIFY(componentManager != nullptr);
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::configuringServiceLocatorShouldAddMainWindowToServices()
{
    CarouselBootloader carouselBootloader;
    carouselBootloader.run();

    IServiceLocator *serviceLocator = carouselBootloader.serviceLocator();
    QVERIFY(serviceLocator != nullptr);

    QMainWindow *mainWindow  = serviceLocator->locate<QMainWindow>();

    QVERIFY(mainWindow != nullptr);
}

//------------------------------------------------------------------------------
