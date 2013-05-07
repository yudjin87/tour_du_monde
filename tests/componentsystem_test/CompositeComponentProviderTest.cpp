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
    MockComponentProvider *provider1 = new MockComponentProvider();
    MockComponentProvider *provider2 = new MockComponentProvider();

    MockCompositeComponentProvider mock;
    mock.addProvider(provider1)
        .addProvider(provider2);

    mock.initialize();

    QVERIFY(provider1->hasBeenInit());
    QVERIFY(provider2->hasBeenInit());
}

//------------------------------------------------------------------------------
void CompositeComponentProviderTest::shouldJoinComponentsFromAllProviders()
{
    MockComponentProvider *provider1 = new MockComponentProvider();
    provider1->registerComponent(new MockComponent("MockComponent1"));
    provider1->registerComponent(new MockComponent("MockComponent2"));

    MockComponentProvider *provider2 = new MockComponentProvider();
    provider2->registerComponent(new MockComponent("MockComponent3"));

    MockCompositeComponentProvider mock;
    mock.addProvider(provider1);
    mock.addProvider(provider2);

    mock.initialize();

    QList<IComponent *> components = mock.components();

    QCOMPARE(components.size(), 3);
}

//------------------------------------------------------------------------------
void CompositeComponentProviderTest::shouldMergeComponentsBothFromProvidersAndFromComponentsList()
{
    MockComponentProvider *provider1 = new MockComponentProvider();
    provider1->registerComponent(new MockComponent("MockComponent1"));

    MockComponentProvider *provider2 = new MockComponentProvider();
    provider2->registerComponent(new MockComponent("MockComponent2"));

    MockCompositeComponentProvider mock;
    mock.addProvider(provider1);
    mock.addProvider(provider2);

    mock.registerComponent(new MockComponent("MockComponent3"));

    mock.initialize();

    QList<IComponent *> components = mock.components();

    QCOMPARE(components.size(), 3);
}

//------------------------------------------------------------------------------
