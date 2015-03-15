#include "CarouselBootloaderTest.h"
#include "fakes/CarouselBootloaderMock.h"
#include "fakes/CarouselBootloaderProviderMock.h"
#include "fakes/CarouselBootloader_ComponentManagerFixture.h"

#include <carousel/booting/CarouselBootloader.h>
#include <carousel/componentsystem/ComponentManager.h>
#include <carousel/componentsystem/ComponentProvider.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>
#include <carousel/utils/ObservableList.h>

#include <QtWidgets/QMainWindow>
#include <QtTest/QtTest>

CarouselBootloaderTest::CarouselBootloaderTest(QObject *parent)
    : QObject(parent)
{
}

void CarouselBootloaderTest::canRunLoading()
{
    CarouselBootloader carouselBootloader;
    carouselBootloader.run();
}

void CarouselBootloaderTest::shouldCallCreateLoggerEngineOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createLoggerCalled());
}

void CarouselBootloaderTest::shouldInstallCreatedLoggerEngineOnRun()
{
    CarouselBootloader carouselBootloader;

    QVERIFY(LoggerFacade::loggerEngine() == nullptr);

    carouselBootloader.run();

    QVERIFY(LoggerFacade::loggerEngine() != nullptr);
}

void CarouselBootloaderTest::shouldCallCreateComponentProviderOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createComponentProviderCalled());
}

void CarouselBootloaderTest::shouldCallCreateComponentManagerOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createComponentManagerCalled());
}

void CarouselBootloaderTest::shouldCallCreateServiceLocatorOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.createServiceLocatorCalled());
}

void CarouselBootloaderTest::shouldCallConfigureComponentProviderOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.configureComponentProviderCalled());
}

void CarouselBootloaderTest::shouldCallConfigureComponentManagerOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.configureComponentManagerCalled());
}

void CarouselBootloaderTest::shouldCallConfigureServiceLocatorOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.configureServiceLocatorCalled());
}

void CarouselBootloaderTest::shouldCallInitialiseComponentProviderOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    QVERIFY(mockLoader.initialiseComponentProviderCalled());
}

void CarouselBootloaderTest::shouldCallRunSequenceInOrderOnRun()
{
    CarouselBootloaderMock mockLoader;
    mockLoader.run();

    const QStringList &methodCalls = mockLoader.methodCalls();

    QCOMPARE(methodCalls[0], QString("createLoggerEngine"));
    QCOMPARE(methodCalls[1], QString("createServiceLocator"));
    QCOMPARE(methodCalls[2], QString("onLoadingSequenceStarting"));
    QCOMPARE(methodCalls[3], QString("createComponentManager"));
    QCOMPARE(methodCalls[4], QString("createComponentProvider"));
    QCOMPARE(methodCalls[5], QString("configureComponentProvider"));
    QCOMPARE(methodCalls[6], QString("configureServiceLocator"));
    QCOMPARE(methodCalls[7], QString("initialiseComponentProvider"));
    QCOMPARE(methodCalls[8], QString("configureComponentManager"));
    QCOMPARE(methodCalls[9], QString("startComponentManager"));
    QCOMPARE(methodCalls[10], QString("onLoadingSequenceFinised"));
}

void CarouselBootloaderTest::shouldInitialiseComponentProviderOnRun()
{
    CarouselBootloaderProviderMock mockLoader;
    mockLoader.run();

    bool initialiseCalled = mockLoader.componentProvider().initialiseCalled();
    QVERIFY(initialiseCalled);
}

void CarouselBootloaderTest::configuringComponentManagerShouldAddComponentsToIt()
{
    CarouselBootloader_ComponentManagerFixture fixture;
    fixture.run();

    IComponentManager& manager = fixture.componentManager();

    QCOMPARE(manager.components().count(), 2);
}

void CarouselBootloaderTest::configuringServiceLocatorShouldAddComponentProviderToServices()
{
    CarouselBootloaderMock carouselBootloader;
    carouselBootloader.run();

    IServiceLocator *serviceLocator = carouselBootloader.locator();
    QVERIFY(serviceLocator != nullptr);

    IComponentProvider *provider = serviceLocator->locate<IComponentProvider>();

    QVERIFY(dynamic_cast<ComponentProvider *>(provider) != nullptr);
}

void CarouselBootloaderTest::configuringServiceLocatorShouldAddComponentManagerToServices()
{
    CarouselBootloaderMock carouselBootloader;
    carouselBootloader.run();

    IServiceLocator *serviceLocator = carouselBootloader.locator();
    QVERIFY(serviceLocator != nullptr);

    IComponentManager *componentManager  = serviceLocator->locate<IComponentManager>();

    QVERIFY(componentManager != nullptr);
}

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

