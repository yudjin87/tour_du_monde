#include "CarouselBootloaderTest.h"
#include "fakes/CarouselBootloaderMock.h"
#include "fakes/CarouselBootloaderProviderMock.h"
#include "fakes/CarouselBootloader_ComponentManagerFixture.h"

#include <booting/CarouselBootloader.h>
#include <componentsystem/ComponentManager.h>
#include <componentsystem/ComponentProvider.h>
#include <logging/LoggerFacade.h>
#include <utils/IServiceLocator.h>
#include <utils/ObservableList.h>

#include <QtWidgets/QMainWindow>
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
void CarouselBootloaderTest::shouldCallCreateLoggerEngineOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createLoggerCalled());
}

//------------------------------------------------------------------------------
void CarouselBootloaderTest::shouldInstallCreatedLoggerEngineOnRun()
{
    CarouselBootloader carouselBootloader;

    QVERIFY(LoggerFacade::loggerEngine() == nullptr);

    carouselBootloader.run();

    QVERIFY(LoggerFacade::loggerEngine() != nullptr);
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

    QCOMPARE(methodCalls[0], QString("createLoggerEngine"));
    QCOMPARE(methodCalls[1], QString("createServiceLocator"));
    QCOMPARE(methodCalls[2], QString("createComponentManager"));
    QCOMPARE(methodCalls[3], QString("createComponentProvider"));
    QCOMPARE(methodCalls[4], QString("createMainWindow"));
    QCOMPARE(methodCalls[5], QString("configureComponentProvider"));
    QCOMPARE(methodCalls[6], QString("configureServiceLocator"));
    QCOMPARE(methodCalls[7], QString("initialiseComponentProvider"));
    QCOMPARE(methodCalls[8], QString("configureComponentManager"));

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
void CarouselBootloaderTest::shouldInstallNullLoggerEngineInDestructor()
{
    {
        CarouselBootloader carouselBootloader;

        QVERIFY(LoggerFacade::loggerEngine() == nullptr);

        carouselBootloader.run();

        QVERIFY(LoggerFacade::loggerEngine() != nullptr);
    }

    QVERIFY(LoggerFacade::loggerEngine() == nullptr);
}

//------------------------------------------------------------------------------
