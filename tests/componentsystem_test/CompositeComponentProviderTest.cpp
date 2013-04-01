#include "CompositeComponentProviderTest.h"
#include "fakes/MockComponent.h"
#include "fakes/MockComponentProvider.h"
#include "fakes/MockCompositeComponentProvider.h"

#include <componentsystem/CompositeComponentProvider.h>
#include <componentsystem/ComponentProvider.h>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
void CompositeComponentProviderTest::canAddProvider()
{
    MockCompositeComponentProvider mock;
    mock.addProvider(new MockCompositeComponentProvider());

    // There are two providers: MockCompositeComponentProvider and ComponentProvider
    QCOMPARE((int)mock.size(), 1 + 1);

}

//------------------------------------------------------------------------------
void CompositeComponentProviderTest::shouldInitialiseAllProviders()
{
    MockComponentProvider *p_provider1 = new MockComponentProvider();
    MockComponentProvider *p_provider2 = new MockComponentProvider();

    MockCompositeComponentProvider mock;
    mock.addProvider(p_provider1)
        .addProvider(p_provider2);

    mock.initialize();

    QVERIFY(p_provider1->hasBeenInit());
    QVERIFY(p_provider2->hasBeenInit());

}

//------------------------------------------------------------------------------
void CompositeComponentProviderTest::shouldJoinComponentsFromAllProviders()
{
    MockComponentProvider *p_provider1 = new MockComponentProvider();
    p_provider1->registerComponent(new MockComponent("MockComponent1"));
    p_provider1->registerComponent(new MockComponent("MockComponent2"));

    MockComponentProvider *p_provider2 = new MockComponentProvider();
    p_provider2->registerComponent(new MockComponent("MockComponent3"));

    MockCompositeComponentProvider mock;
    mock.addProvider(p_provider1);
    mock.addProvider(p_provider2);

    mock.initialize();

    QList<IComponent *> components = mock.components();

    QCOMPARE(components.size(), 3);
}

//------------------------------------------------------------------------------
void CompositeComponentProviderTest::shouldMergeComponentsBothFromProvidersAndFromComponentsList()
{
    MockComponentProvider *p_provider1 = new MockComponentProvider();
    p_provider1->registerComponent(new MockComponent("MockComponent1"));

    MockComponentProvider *p_provider2 = new MockComponentProvider();
    p_provider2->registerComponent(new MockComponent("MockComponent2"));

    MockCompositeComponentProvider mock;
    mock.addProvider(p_provider1);
    mock.addProvider(p_provider2);

    mock.registerComponent(new MockComponent("MockComponent3"));

    mock.initialize();

    QList<IComponent *> components = mock.components();

    QCOMPARE(components.size(), 3);
}

//------------------------------------------------------------------------------
