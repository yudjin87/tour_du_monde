#include "ServiceLocatorTest.h"
#include "fakes/MockServiceLocator.h"
#include "fakes/Services.h"

#include <utils/ServiceLocator.h>
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
void ServiceLocatorTest::canLocateToRegisterInstanceByType()
{
    Service1 service(45);

    ServiceLocator locator;
    locator.registerInstance<IService>(&service);
    IService *p_located_service = locator.locate<IService>();

    QVERIFY(p_located_service == &service);
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

    IService *p_located_service2 = locator.locate<IService>("SecondOne");
    QVERIFY(p_located_service2 == &service2);
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
//TODO: replace to lambda
void *removeMeWhenLambdaSupportWillBeAdded()
{
    return new Service1();
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canRegisterFactoryMethodForType()
{
    MockServiceLocator mockLocator;
    factoryMethod creator = &removeMeWhenLambdaSupportWillBeAdded;
    mockLocator.registerType<IService>(creator);

    QCOMPARE(mockLocator.creators().size(), 1);
}

//------------------------------------------------------------------------------
void ServiceLocatorTest::canBuildRegisteredWithFactoryMethodInterfaceByType()
{
    MockServiceLocator mockLocator;
    factoryMethod creator = &removeMeWhenLambdaSupportWillBeAdded;
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
