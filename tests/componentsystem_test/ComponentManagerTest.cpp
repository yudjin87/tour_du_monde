#include "ComponentManagerTest.h"

#include "fakes/MockChildComponent.h"
#include "fakes/MockComponent.h"
#include "fakes/MockComponentDependencies.h"
#include "fakes/MockComponentManager.h"
#include "fakes/TestDescriptionComponent.h"

#include "Utils.h"

#include <componentsystem/ComponentManager.h>
#include <logging/NullLogger.h>
#include <utils/ServiceLocator.h>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
namespace { NullLogger lg; }

//------------------------------------------------------------------------------
ComponentManagerTest::ComponentManagerTest()
{
}

//------------------------------------------------------------------------------
void ComponentManagerTest::addComponent_shouldAddComponentToTheStoppedComponents()
{
    ComponentManager manager(lg);
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createComponent("B");
    manager.addComponent(componentA);
    manager.addComponent(componentB);

    QCOMPARE(manager.stoppedComponents().size(), 2);
    QVERIFY(manager.stoppedComponents().contains(componentA));
    QVERIFY(manager.stoppedComponents().contains(componentB));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::addComponent_shouldSetCheckedFlagToFalse()
{
    IComponent *componentA = createComponent("A");
    ComponentManager manager(lg);
    manager.check();

    QVERIFY(manager.isChecked());

    manager.addComponent(componentA);

    QCOMPARE(manager.isChecked(), false);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::check_shouldCallResolving()
{
    MockComponentDependencies *dependencies = new MockComponentDependencies();
    ComponentManager manager(dependencies, lg);

    manager.check();

    QCOMPARE(dependencies->completeListWithChildrenCalled, 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::check_shouldSetCheckedFlag()
{
    ComponentManager manager(lg);

    QCOMPARE(manager.isChecked(), false);

    manager.check();

    QVERIFY(manager.isChecked());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::check_shouldNotResolveComponentsAgainIfCheckedFlagIsTrue()
{
    MockComponentDependencies *dependencies = new MockComponentDependencies();
    ComponentManager manager(dependencies, lg);

    manager.check();

    QCOMPARE(dependencies->completeListWithChildrenCalled, 1);

    manager.check();

    // No components were added, so cache still is OK
    QCOMPARE(dependencies->completeListWithChildrenCalled, 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::check_shouldFillMissingComponents()
{
    // A <- B,  C
    MockComponent *componentC = createComponent("C");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentManager manager(lg);
    manager.addComponent(componentB);
    manager.addComponent(componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.missingComponents().size(), 1); // A is missing
    QCOMPARE(manager.missingComponents().first(), QString("A"));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::check_shouldFillOrphanComponents()
{
    // A <- B,  C
    MockComponent *componentC = createComponent("C");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentManager manager(lg);
    manager.addComponent(componentB);
    manager.addComponent(componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 1); // B is orphan
    QCOMPARE(manager.orphanComponents().first(), componentB);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startup_shouldShouldNotCallIfAlreadyDid()
{
    MockComponent *component = createComponent("A");

    ComponentManager manager(lg);
    QSignalSpy spy(&manager, SIGNAL(componentStarted(IComponent *)));

    manager.addComponent(component);

    manager.startup();
    QCOMPARE(spy.count(), 1);

    component->shutdown();
    manager.startup();
    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startup_shouldStartComponents()
{
    TestDescriptionComponent *descriptionComponent = new TestDescriptionComponent();
    descriptionComponent->setAvailability(IComponent::Enabled);

    ComponentManager manager(lg);
    manager.addComponent(descriptionComponent);

    manager.startup();

    QVERIFY(descriptionComponent->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startup_shouldNotStartDisabledComponent()
{
    MockComponent *disabledComponent = createComponent("A");
    disabledComponent->setAvailability(IComponent::Disabled);
    QSignalSpy spy(disabledComponent, SIGNAL(whenStarted(QString)));

    ComponentManager manager(lg);
    manager.addComponent(disabledComponent);

    manager.startup();

    QCOMPARE(spy.count(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldCallCheck()
{
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createComponent("B");

    ComponentManager manager(lg);

    QCOMPARE(manager.isChecked(), false);

    manager.addComponent(componentA);
    manager.addComponent(componentB);

    manager.startupAllComponents();

    QVERIFY(manager.isChecked());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldRemoveThemFromStoppedList()
{
    ComponentManager manager(lg);
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createComponent("B");
    manager.addComponent(componentA);
    manager.addComponent(componentB);

    QCOMPARE(manager.stoppedComponents().size(), 2);

    manager.startupAllComponents();

    QCOMPARE(manager.stoppedComponents().size(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldAddThemToTheStartedList()
{
    ComponentManager manager(lg);
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createComponent("B");
    manager.addComponent(componentA);
    manager.addComponent(componentB);

    QCOMPARE(manager.startedComponents().size(), 0);

    manager.startupAllComponents();

    QCOMPARE(manager.startedComponents().size(), 2);
    QVERIFY(manager.startedComponents().contains(componentA));
    QVERIFY(manager.startedComponents().contains(componentB));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldEmit()
{
    ComponentManager manager(lg);
    QSignalSpy spy(&manager, SIGNAL(componentStarted(IComponent *)));

    MockComponent *mockComponent = new MockComponent();
    manager.addComponent(mockComponent);
    manager.startupAllComponents();

    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldStartComponents()
{
    TestDescriptionComponent *descriptionComponent = new TestDescriptionComponent();
    descriptionComponent->setAvailability(IComponent::Enabled);

    ComponentManager manager(lg);
    manager.addComponent(descriptionComponent);

    manager.startupAllComponents();

    QVERIFY(descriptionComponent->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldEmit()
{
    ComponentManager manager(lg);
    QSignalSpy spy(&manager, SIGNAL(componentShutDown(IComponent *)));

    MockComponent *mockComponent = new MockComponent();
    manager.addComponent(mockComponent);
    manager.startupComponent(mockComponent);
    manager.shutdownAllComponents();

    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldEmitAboutSignal()
{
    ComponentManager manager(lg);
    QSignalSpy spy(&manager, SIGNAL(componentAboutToShutDown(IComponent *)));

    MockComponent *mockComponent = new MockComponent();
    manager.addComponent(mockComponent);
    manager.startupComponent(mockComponent);
    manager.shutdownAllComponents();

    QCOMPARE(spy.count(), 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldRemoveThemFromStartedList()
{
    ComponentManager manager(lg);
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createComponent("B");
    manager.addComponent(componentA);
    manager.addComponent(componentB);
    manager.startupAllComponents();

    QCOMPARE(manager.stoppedComponents().size(), 0);

    manager.shutdownAllComponents();

    QCOMPARE(manager.stoppedComponents().size(), 2);
    QVERIFY(manager.stoppedComponents().contains(componentA));
    QVERIFY(manager.stoppedComponents().contains(componentB));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldAddThemToTheStoppedList()
{
    ComponentManager manager(lg);
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createComponent("B");
    manager.addComponent(componentA);
    manager.addComponent(componentB);
    manager.startupAllComponents();

    QCOMPARE(manager.startedComponents().size(), 2);

    manager.shutdownAllComponents();

    QCOMPARE(manager.startedComponents().size(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldNotShutdownUnexistingComponent()
{
    MockComponent *componentA = createComponent("A");
    QSignalSpy spy(componentA, SIGNAL(whenShutdown(QString)));

    ComponentManager manager(lg);
    manager.startupComponent(componentA);

    manager.shutdownAllComponents();

    QCOMPARE(spy.size(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldNotShutdownBuiltInComponent()
{
    MockComponent *componentA = new MockComponent("MockComponent", true);
    QSignalSpy spy(componentA, SIGNAL(whenShutdown(const QString &)));

    componentA->startup(nullptr);

    QCOMPARE(componentA->started(), true);

    ComponentManager manager(lg);
    manager.addComponent(componentA);
    manager.startupAllComponents();
    manager.shutdownAllComponents();

    // make sure the signal wasn't emitted
    QCOMPARE(spy.count(), 0);
    QCOMPARE(componentA->started(), true);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldDisableComponent()
{
    MockComponent *component = createComponent("A");

    ComponentManager manager(lg);
    manager.addComponent(component);

    manager.startupAllComponents();
    manager.shutdownAllComponents();

    QCOMPARE(component->availability(), IComponent::Disabled);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownComponents_shouldReturnJustShutDownComponents()
{
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A");

    ComponentManager manager(lg);
    manager.addComponent(componentA);
    manager.addComponent(componentB);

    manager.startup();
    manager.shutdownComponent(componentB);

    DependenciesSolvingResult result = manager.shutdownComponent(componentA);

    // Only componentA should appear that time
    QCOMPARE(result.ordered().size(), 1);
    QVERIFY(result.ordered().first()->name() == "A");
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdown_shouldShutdownAllComponents()
{
    MockComponent *componentA = createComponent("A");
    QSignalSpy spy(componentA, SIGNAL(whenShutdown(QString)));

    ComponentManager manager(lg);
    manager.addComponent(componentA);
    manager.startupComponent(componentA);

    manager.startup();
    manager.shutdown();

    QCOMPARE(spy.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdown_shouldShutdownBuiltInComponents()
{
    MockComponent *componentA = new MockComponent("A", true);
    QSignalSpy spy(componentA, SIGNAL(whenShutdown(QString)));

    ComponentManager manager(lg);
    manager.addComponent(componentA);
    manager.startupComponent(componentA);

    manager.startup();
    manager.shutdown();

    QCOMPARE(spy.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdown_shouldNotDisableComponent()
{
    MockComponent *component = createComponent("A");

    ComponentManager manager(lg);
    manager.addComponent(component);

    manager.startupAllComponents();
    manager.shutdown();

    QCOMPARE(component->availability(), IComponent::Enabled);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdown_shouldEmit()
{
    ComponentManager manager(lg);
    QSignalSpy spy(&manager, SIGNAL(aboutToShutDown()));

    manager.startup();
    manager.shutdown();

    QCOMPARE(spy.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldPassInitDataToComponent()
{
    MockComponent *mockComponent = new MockComponent();

    ComponentManager manager(lg);
    manager.addComponent(mockComponent);

    manager.setInitializationData(this);
    manager.startupAllComponents();

    QCOMPARE(mockComponent->m_initData, this);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldEnableDisabledComponent()
{
    MockComponent *disabledComponent = createComponent("A");
    disabledComponent->setAvailability(IComponent::Disabled);
    QSignalSpy spy(disabledComponent, SIGNAL(whenStarted(QString)));

    ComponentManager manager(lg);
    manager.addComponent(disabledComponent);

    manager.startupAllComponents();

    QCOMPARE(spy.count(), 1);
    QCOMPARE(disabledComponent->availability(), IComponent::Enabled);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldHandleNullComponent()
{
    ComponentManager manager(lg);
    manager.startupComponent(nullptr);

    // just dot't crash
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldPassComponentsInRightOrder()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *componentE = createParentComponent("E", "C"); //dependent from C;

    MockComponentManager manager(lg);

    // Add the components in random order
    manager.addComponent(componentB);
    manager.addComponent(componentA);
    manager.addComponent(componentD);
    manager.addComponent(componentE);
    manager.addComponent(componentC);

    manager.startupAllComponents();

    QList<IComponent *> comps = manager.m_startupComponents;
    QCOMPARE(comps.size(), 5);

    QVERIFY(comps.indexOf(componentA) < comps.indexOf(componentB));
    QVERIFY(comps.indexOf(componentB) < comps.indexOf(componentC));
    QVERIFY(comps.indexOf(componentC) < comps.indexOf(componentD));
    QVERIFY(comps.indexOf(componentC) < comps.indexOf(componentE));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldPassComponentsInRightOrder_ComplexDependencies()
{
    //      ┌─── E
    //      v    v
    // A <- B <- C
    //      ^    ^
    //      └─── D
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "B", "C"); //dependent from B & C;
    MockChildComponent *componentE = createParentComponent("E", "A", "C"); //dependent from A & C;

    MockComponentManager manager(lg);

    // Add the components in random order
    manager.addComponent(componentB);
    manager.addComponent(componentC);
    manager.addComponent(componentA);
    manager.addComponent(componentD);
    manager.addComponent(componentE);

    manager.startupAllComponents();

    QList<IComponent *> comps = manager.m_startupComponents;
    QCOMPARE(comps.size(), 5);

    QVERIFY(comps.indexOf(componentA) < comps.indexOf(componentB));
    QVERIFY(comps.indexOf(componentB) < comps.indexOf(componentC));
    QVERIFY(comps.indexOf(componentC) < comps.indexOf(componentD));
    QVERIFY(comps.indexOf(componentC) < comps.indexOf(componentE));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldPassComponentsInRightOrder()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *componentE = createParentComponent("E", "C"); //dependent from C;

    MockComponentManager manager(lg);
    manager.addComponent(componentB);
    manager.addComponent(componentA);
    manager.addComponent(componentD);
    manager.addComponent(componentE);
    manager.addComponent(componentC);

    // components will be started in the right order, according to their dependencies
    manager.startupAllComponents();
    manager.shutdownAllComponents();

    QList<IComponent *> comps = manager.m_shutdownComponents;

    QVERIFY(comps.indexOf(componentA) > comps.indexOf(componentB));
    QVERIFY(comps.indexOf(componentB) > comps.indexOf(componentC));
    QVERIFY(comps.indexOf(componentC) > comps.indexOf(componentD));
    QVERIFY(comps.indexOf(componentC) > comps.indexOf(componentE));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupComponent_shouldPassRightComponentsInRightOrder()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *componentE = createParentComponent("E", "C"); //dependent from C;

    MockComponentManager manager(lg);
    // Add the components in random order
    manager.addComponent(componentB);
    manager.addComponent(componentA);
    manager.addComponent(componentD);
    manager.addComponent(componentE);
    manager.addComponent(componentC);

    manager.startupComponent(componentC);

    QList<IComponent *> comps = manager.m_startupComponents;
    QCOMPARE(comps.size(), 3); // A, B and C components should be passed

    QVERIFY(comps.indexOf(componentA) < comps.indexOf(componentB));
    QVERIFY(comps.indexOf(componentB) < comps.indexOf(componentC));

    // E and D components should not been passed
    QCOMPARE(comps.contains(componentD), QBool(false));
    QCOMPARE(comps.contains(componentE), QBool(false));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownComponent_shouldPassComponentsInReverseOrder()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *componentE = createParentComponent("E", "C"); //dependent from C;

    MockComponentManager manager(lg);
    // Add the components in random order
    manager.addComponent(componentB);
    manager.addComponent(componentA);
    manager.addComponent(componentD);
    manager.addComponent(componentE);
    manager.addComponent(componentC);

    manager.startupAllComponents();
    manager.shutdownComponent(componentC);

    QList<IComponent *> comps = manager.m_shutdownComponents;

    QCOMPARE(comps.size(), 3); // C, D and E components should be passed for shutdown

    QVERIFY(comps.indexOf(componentD) < comps.indexOf(componentC));
    QVERIFY(comps.indexOf(componentE) < comps.indexOf(componentC));

    // A and B components should not been passed
    QCOMPARE(comps.contains(componentA), QBool(false));
    QCOMPARE(comps.contains(componentB), QBool(false));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldNotStartChildComponentsIfParentCouldNotStart()
{
    // A <- B <- C
    TestDescriptionComponent *componentA = new TestDescriptionComponent("A");
    componentA->startUpResult = false;
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;

    ComponentManager manager(lg);
    manager.addComponent(componentB);
    manager.addComponent(componentA);
    manager.addComponent(componentC);

    manager.startupAllComponents();

    QVERIFY(!componentA->started());
    QVERIFY(!componentB->started());
    QVERIFY(!componentC->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldStartOrphanComponentIfParentAppeared()
{
    // A <- B,  C
    MockComponent *componentA = createComponent("A");
    MockComponent *componentC = createComponent("C");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentManager manager(lg);
    manager.addComponent(componentB);
    manager.addComponent(componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 1); // B is orphan
    QVERIFY(!componentB->started());

    manager.addComponent(componentA);
    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 0);
    QVERIFY(componentB->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupComponents_shouldStartOrphanComponentsWhenParentsAppeared()
{
    // A <- B,  C
    MockComponent *componentA = createComponent("A");
    MockComponent *componentC = createComponent("C");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentManager manager(lg);
    manager.addComponent(componentB);
    manager.addComponent(componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 1); // B is orphan
    QVERIFY(!componentB->started());

    QList<IComponent *> comps;
    comps.push_back(componentA);
    manager.addComponent(componentA);
    manager.startupComponents(comps);

    QCOMPARE(manager.orphanComponents().size(), 0);
    QVERIFY(componentB->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupComponents_shouldNotStartOrphanComponentsWhenOtherParentsAppeared()
{
    // A <- B,  C, D
    MockComponent *componentD = createComponent("D");
    MockComponent *componentC = createComponent("C");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentManager manager(lg);
    manager.addComponent(componentB);
    manager.addComponent(componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 1); // B is orphan
    QVERIFY(!componentB->started());

    QList<IComponent *> comps;
    comps.push_back(componentD);
    manager.addComponent(componentD);
    manager.startupComponents(comps);

    // B is still orphan because it's parent was not added
    QCOMPARE(manager.orphanComponents().size(), 1);
    QVERIFY(!componentB->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupComponents_shouldReturnJustStartedComponents()
{
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A");

    ComponentManager manager(lg);
    manager.addComponent(componentA);
    manager.startup();
    manager.addComponent(componentB);

    DependenciesSolvingResult result = manager.startupComponent(componentB);

    // Only componentB should appear that time
    QCOMPARE(result.ordered().size(), 1);
    QVERIFY(result.ordered().first()->name() == "B");
}

//------------------------------------------------------------------------------

