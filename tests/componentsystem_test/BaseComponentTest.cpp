#include "BaseComponentTest.h"

#include "fakes/ComponentWithExtensions.h"
#include "fakes/MockComponent.h"

#include <componentsystem/BaseComponent.h>
#include <componentsystem/IComponentDefinition.h>
#include <utils/IServiceLocator.h>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
BaseComponentTest::BaseComponentTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldReturnResultOfProtectedMethodOnFirstSuccessfulStartup()
{
    MockComponent mockComponent(true);
    QVERIFY(mockComponent.startup(nullptr));

    MockComponent mockComponent2(false);
    QVERIFY(!mockComponent2.startup(nullptr));
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldAssignResultOfProtectedMethodToTheStartedFlag()
{
    MockComponent mockComponent(true);
    mockComponent.startup(nullptr);
    QVERIFY(mockComponent.started());

    MockComponent mockComponent2(false);
    mockComponent2.startup(nullptr);
    QVERIFY(!mockComponent2.started());
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldNotStartupIfAlreadyStarted()
{
    MockComponent mockComponent;
    QSignalSpy spy(&mockComponent, SIGNAL(whenStarted(const QString &)));

    mockComponent.startup(nullptr);
    mockComponent.startup(nullptr); // should not be emitted the second time

    // make sure the signal was emitted exactly one time
    QCOMPARE(spy.count(), 1);
    QCOMPARE(mockComponent.started(), true);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldShutdownIfAlreadyStoped()
{
    MockComponent mockComponent;
    QSignalSpy spy(&mockComponent, SIGNAL(whenShutdown(const QString &)));

    mockComponent.shutdown();

    // make sure the signal wasn't emitted
    QCOMPARE(spy.count(), 0);
    QCOMPARE(mockComponent.started(), false);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldReturnRegisteredInDerivedClassesExtensions()
{
    ComponentWithExtensions componentWithExtensions;

    IComponentExtension1 *p_extension1 = componentWithExtensions.extension<IComponentExtension1>();
    IComponentExtension2 *p_extension2 = componentWithExtensions.extension<IComponentExtension2>();

    QCOMPARE(p_extension2, componentWithExtensions.mp_extension2);
    QCOMPARE(p_extension1, componentWithExtensions.mp_extension1);
}

//------------------------------------------------------------------------------
void BaseComponentTest::shouldReturnNullWhenUnregisteredExtensionIsQueried()
{
    ComponentWithExtensions componentWithExtensions;

    BaseComponentTest *p_unregisteredExtension = componentWithExtensions.extension<BaseComponentTest>();

    QVERIFY(p_unregisteredExtension == nullptr);
}

//------------------------------------------------------------------------------
