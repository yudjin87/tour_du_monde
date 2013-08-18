#include "ServiceLocatorTest.h"
#include "fakes/MockServiceLocator.h"
#include "fakes/Services.h"

#include <carousel/utils/ServiceLocator.h>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
ServiceLocatorTest::ServiceLocatorTest()
    : QObject(nullptr)
{

}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canRegisterInstance()
{
    Service1 service(45);
    MockServiceLocator mockLocator;

    mockLocator.registerInstance<IService>(&service);
    QCOMPARE(mockLocator.items().size(), 1);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::shouldNotRegisterInstanceOfExistingType()
{
    Service1 service(1);
    Service1 service2(2);

    MockServiceLocator mockLocator;
    mockLocator.registerInstance<IService>(&service);
    mockLocator.registerInstance<IService>(&service2);

    QCOMPARE(mockLocator.items().size(), 1);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canRegisterInstanceOfExistingTypeWithTag()
{
    Service1 service(1);
    Service1 service2(2);

    MockServiceLocator mockLocator;
    mockLocator.registerInstance<IService>(&service);
    mockLocator.registerInstance<IService>(&service2, "SecondOne");

    QCOMPARE(mockLocator.items().size(), 2);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::shouldNotRegisterInstanceOfExistingTypeWithExistingTag()
{
    Service1 service(1);
    Service1 service2(2);
    Service1 service3(3);

    MockServiceLocator mockLocator;
    mockLocator.registerInstance<IService>(&service);
    mockLocator.registerInstance<IService>(&service2, "SecondOne");
    mockLocator.registerInstance<IService>(&service3, "SecondOne");

    QCOMPARE(mockLocator.items().size(), 2);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::unregisterInstance_shouldReturnFoundInstance()
{
    Service1 service(1);

    MockServiceLocator mockLocator;
    mockLocator.registerInstance<IService>(&service);

    IService *unregistered = mockLocator.unregisterInstance<IService>();
    QVERIFY(unregistered == &service);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::unregisterInstance_shouldRemoveInstanceFromList()
{
    Service1 service(1);

    MockServiceLocator mockLocator;
    mockLocator.registerInstance<IService>(&service);

    mockLocator.unregisterInstance<IService>();
    QCOMPARE(mockLocator.items().size(), 0);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::shouldRegisterInstanceAfterUnregistring()
{
    Service1 service(1);
    MockServiceLocator mockLocator;
    mockLocator.registerInstance<IService>(&service);
    mockLocator.unregisterInstance<IService>();

    Service1 service2(2);
    mockLocator.registerInstance<IService>(&service2);

    IService *iservice2 = mockLocator.unregisterInstance<IService>();
    QCOMPARE(iservice2->id(), 2);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canLocateToRegisterInstanceByType()
{
    Service1 service(45);

    ServiceLocator locator;
    locator.registerInstance<IService>(&service);
    IService *located_service = locator.locate<IService>();

    QVERIFY(located_service == &service);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canLocateToRegisterInstanceByTypeAndTag()
{
    Service1 service(1);
    Service1 service2(2);

    MockServiceLocator locator;
    locator.registerInstance<IService>(&service);
    locator.registerInstance<IService>(&service2, "SecondOne");

    QCOMPARE(locator.items().size(), 2);

    IService *located_service2 = locator.locate<IService>("SecondOne");
    QVERIFY(located_service2 == &service2);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canLocateToRegisteredObjectByClassName()
{
    Service1 service(45);

    ServiceLocator locator;
    locator.registerInstance<IService>(&service);
    QObject *located_service = locator.locateToObject("IService");

    QVERIFY(located_service == &service);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canLocateByIndex()
{
    Service1 service(45);

    ServiceLocator locator;
    locator.registerInstance<IService>(&service);
    QObject *located_service = locator.locateByIndex(0);

    QVERIFY(located_service == &service);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canBindConcreteClassForType()
{
    MockServiceLocator mockLocator;
    mockLocator.bindType<IService, Service1>();
 
    QCOMPARE(mockLocator.creators().size(), 1);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::shouldNotBindConcreteClassForExistingType()
{
    MockServiceLocator mockLocator;
    mockLocator.bindType<IService, Service1>();
    mockLocator.bindType<IService, Service1>();

    QCOMPARE(mockLocator.creators().size(), 1);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canBindConcreteClassForExistingTypeWithTag()
{
    MockServiceLocator mockLocator;
    mockLocator.bindType<IService, Service1>();
    mockLocator.bindType<IService, Service1>("SecondOne");

    QCOMPARE(mockLocator.creators().size(), 2);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::shouldNotBindConcreteClassForExistingTypeWithExistingTag()
{
    MockServiceLocator mockLocator;
    mockLocator.bindType<IService, Service1>();
    mockLocator.bindType<IService, Service1>("SecondOne");
    mockLocator.bindType<IService, Service1>("SecondOne");

    QCOMPARE(mockLocator.creators().size(), 2);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canRegisterFactoryMethodForType()
{
    MockServiceLocator mockLocator;
    auto creator = [](){return new Service1();};
    mockLocator.registerType<IService>(creator);

    QCOMPARE(mockLocator.creators().size(), 1);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canBuildRegisteredWithFactoryMethodInterfaceByType()
{
    MockServiceLocator mockLocator;
    auto creator = [](){return new Service1();};
    mockLocator.registerType<IService>(creator);

    QCOMPARE(Service1::instancesCount, 0);

    IService *service = mockLocator.buildInstance<IService>();
    IService *service2 = mockLocator.buildInstance<IService>();

    QCOMPARE(Service1::instancesCount, 2);

    QVERIFY(service != nullptr);
    QVERIFY(service2 != nullptr);
    QVERIFY(service != service2);

    delete service;
    delete service2;
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canBuildBindedInterfaceByType()
{
    MockServiceLocator mockLocator;
    mockLocator.bindType<IService, Service1>();

    QCOMPARE(Service1::instancesCount, 0);

    IService *service = mockLocator.buildInstance<IService>();
    IService *service2 = mockLocator.buildInstance<IService>();

    QCOMPARE(Service1::instancesCount, 2);

    QVERIFY(service != nullptr);
    QVERIFY(service2 != nullptr);
    QVERIFY(service != service2);

    delete service;
    delete service2;
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canBuildBindedInterfaceByTypeAndTag()
{
    MockServiceLocator mockLocator;
    mockLocator.bindType<IService, Service1>("SecondOne");

    QCOMPARE(Service1::instancesCount, 0);

    IService *service = mockLocator.buildInstance<IService>("SecondOne");
    IService *service2 = mockLocator.buildInstance<IService>("SecondOne");

    QCOMPARE(Service1::instancesCount, 2);

    QVERIFY(service != nullptr);
    QVERIFY(service2 != nullptr);
    QVERIFY(service != service2);

    delete service;
    delete service2;
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canBuildRegisteredWithFactoryMethodInterfaceClassName()
{
    MockServiceLocator mockLocator;
    auto creator = [](){return new Service1();};
    mockLocator.registerType<IService>(creator);

    QObject *obj = mockLocator.buildObject("IService");
    QVERIFY(dynamic_cast<IService *>(obj) != nullptr);
}

//------------------------------------------------------------------------------
