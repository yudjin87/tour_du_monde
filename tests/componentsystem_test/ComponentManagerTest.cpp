#include "ComponentManagerTest.h"

#include "fakes/MockChildComponent.h"
#include "fakes/MockComponent.h"
#include "fakes/MockComponentDependencies.h"
#include "fakes/MockComponentInitialiser.h"
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
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createComponent("B");
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentB);

    QCOMPARE(manager.stoppedComponents().size(), 2);
    QVERIFY(manager.stoppedComponents().contains(p_componentA));
    QVERIFY(manager.stoppedComponents().contains(p_componentB));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::addComponent_shouldSetCheckedFlagToFalse()
{
    IComponent *p_componentA = createComponent("A");
    ComponentManager manager(lg);
    manager.check();

    QVERIFY(manager.isChecked());

    manager.addComponent(p_componentA);

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
    MockComponent *p_componentC = createComponent("C");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.missingComponents().size(), 1); // A is missing
    QCOMPARE(manager.missingComponents().first(), QString("A"));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::check_shouldFillOrphanComponents()
{
    // A <- B,  C
    MockComponent *p_componentC = createComponent("C");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 1); // B is orphan
    QCOMPARE(manager.orphanComponents().first(), p_componentB);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldCallCheck()
{
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createComponent("B");

    ComponentManager manager(lg);

    QCOMPARE(manager.isChecked(), false);

    manager.addComponent(p_componentA);
    manager.addComponent(p_componentB);

    manager.startupAllComponents();

    QVERIFY(manager.isChecked());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldRemoveThemFromStoppedList()
{
    ComponentManager manager(lg);
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createComponent("B");
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentB);

    QCOMPARE(manager.stoppedComponents().size(), 2);

    manager.startupAllComponents();

    QCOMPARE(manager.stoppedComponents().size(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldAddThemToTheStartedList()
{
    ComponentManager manager(lg);
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createComponent("B");
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentB);

    QCOMPARE(manager.startedComponents().size(), 0);

    manager.startupAllComponents();

    QCOMPARE(manager.startedComponents().size(), 2);
    QVERIFY(manager.startedComponents().contains(p_componentA));
    QVERIFY(manager.startedComponents().contains(p_componentB));
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
    QSignalSpy spy(&manager, SIGNAL(componentShutedDown(IComponent *)));

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
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createComponent("B");
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentB);
    manager.startupAllComponents();

    QCOMPARE(manager.stoppedComponents().size(), 0);

    manager.shutdownAllComponents();

    QCOMPARE(manager.stoppedComponents().size(), 2);
    QVERIFY(manager.stoppedComponents().contains(p_componentA));
    QVERIFY(manager.stoppedComponents().contains(p_componentB));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldAddThemToTheStoppedList()
{
    ComponentManager manager(lg);
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createComponent("B");
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentB);
    manager.startupAllComponents();

    QCOMPARE(manager.startedComponents().size(), 2);

    manager.shutdownAllComponents();

    QCOMPARE(manager.startedComponents().size(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldNotPassUnexistingComponentToInitialiser()
{
    MockComponent *p_componentA = createComponent("A");

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.startupComponent(p_componentA);

    manager.shutdownAllComponents();

    // componentA should not be passed to initialiser, because it hasn't been added to the manager
    QCOMPARE(initialiser->m_shutdownComponents.size(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdown_shouldPassAllComponentsToInitialiser()
{
    MockComponent *p_componentA = createComponent("A");

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.addComponent(p_componentA);
    manager.startupComponent(p_componentA);

    manager.shutdown();

    QCOMPARE(initialiser->m_forceShutdownComponents.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldPassInitDataToComponentInitialiser()
{
    MockComponent *mockComponent = new MockComponent();
    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.addComponent(mockComponent);

    manager.setInitializationData(this);
    manager.startupAllComponents();

    QCOMPARE(initialiser->mp_initializationData, this);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldNotPassUnexistingComponentToInitialiser()
{
    MockComponent *p_componentA = createComponent("A");

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.startupComponent(p_componentA);

    // componentA should not be passed to initialiser, because it hasn't been added to the manager
    QCOMPARE(initialiser->m_startupComponents.size(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldNotPassNullComponentToInitialiser()
{
    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.startupComponent(nullptr);

    QCOMPARE(initialiser->m_startupComponents.size(), 0);
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldPassComponentsInRightOrder()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *p_componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *p_componentE = createParentComponent("E", "C"); //dependent from C;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);

    // Add the components in random order
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentD);
    manager.addComponent(p_componentE);
    manager.addComponent(p_componentC);

    manager.startupAllComponents();

    QList<IComponent *> comps = initialiser->m_startupComponents;
    QCOMPARE(comps.size(), 5);

    QVERIFY(comps.indexOf(p_componentA) < comps.indexOf(p_componentB));
    QVERIFY(comps.indexOf(p_componentB) < comps.indexOf(p_componentC));
    QVERIFY(comps.indexOf(p_componentC) < comps.indexOf(p_componentD));
    QVERIFY(comps.indexOf(p_componentC) < comps.indexOf(p_componentE));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldPassComponentsInRightOrder_ComplexDependencies()
{
    //      ┌─── E
    //      v    v
    // A <- B <- C
    //      ^    ^
    //      └─── D
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;

    MockChildComponent *p_componentD = createParentComponent("D", "B", "C"); //dependent from B & C;
    MockChildComponent *p_componentE = createParentComponent("E", "A", "C"); //dependent from A & C;


    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);

    // Add the components in random order
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentC);
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentD);
    manager.addComponent(p_componentE);

    manager.startupAllComponents();

    QList<IComponent *> comps = initialiser->m_startupComponents;
    QCOMPARE(comps.size(), 5);

    QVERIFY(comps.indexOf(p_componentA) < comps.indexOf(p_componentB));
    QVERIFY(comps.indexOf(p_componentB) < comps.indexOf(p_componentC));
    QVERIFY(comps.indexOf(p_componentC) < comps.indexOf(p_componentD));
    QVERIFY(comps.indexOf(p_componentC) < comps.indexOf(p_componentE));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownAllComponents_shouldPassComponentsInRightOrder()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *p_componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *p_componentE = createParentComponent("E", "C"); //dependent from C;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentD);
    manager.addComponent(p_componentE);
    manager.addComponent(p_componentC);

    // components will be started in the right order, according to their dependencies
    manager.startupAllComponents();
    manager.shutdownAllComponents();

    QList<IComponent *> comps = initialiser->m_shutdownComponents;

    QVERIFY(comps.indexOf(p_componentA) > comps.indexOf(p_componentB));
    QVERIFY(comps.indexOf(p_componentB) > comps.indexOf(p_componentC));
    QVERIFY(comps.indexOf(p_componentC) > comps.indexOf(p_componentD));
    QVERIFY(comps.indexOf(p_componentC) > comps.indexOf(p_componentE));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupComponent_shouldPassRightComponentsInRightOrder()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *p_componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *p_componentE = createParentComponent("E", "C"); //dependent from C;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    // Add the components in random order
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentD);
    manager.addComponent(p_componentE);
    manager.addComponent(p_componentC);

    manager.startupComponent(p_componentC);

    QList<IComponent *> comps = initialiser->m_startupComponents;
    QCOMPARE(comps.size(), 3); // A, B and C components should be passed

    QVERIFY(comps.indexOf(p_componentA) < comps.indexOf(p_componentB));
    QVERIFY(comps.indexOf(p_componentB) < comps.indexOf(p_componentC));

    // E and D components should not been passed
    QCOMPARE(comps.contains(p_componentD), QBool(false));
    QCOMPARE(comps.contains(p_componentE), QBool(false));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::shutdownComponent_shouldPassComponentsInReverseOrder()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *p_componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *p_componentE = createParentComponent("E", "C"); //dependent from C;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    // Add the components in random order
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentD);
    manager.addComponent(p_componentE);
    manager.addComponent(p_componentC);

    manager.startupAllComponents();
    manager.shutdownComponent(p_componentC);

    QList<IComponent *> comps = initialiser->m_shutdownComponents;

    QCOMPARE(comps.size(), 3); // C, D and E components should be passed for shutdown

    QVERIFY(comps.indexOf(p_componentD) < comps.indexOf(p_componentC));
    QVERIFY(comps.indexOf(p_componentE) < comps.indexOf(p_componentC));

    // A and B components should not been passed
    QCOMPARE(comps.contains(p_componentA), QBool(false));
    QCOMPARE(comps.contains(p_componentB), QBool(false));
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldNotStartComponentIfInitialiserReturnFalse()
{
    TestDescriptionComponent *descriptionComponent = new TestDescriptionComponent();
    descriptionComponent->setAvailability(IComponent::Disabled);

    ComponentManager manager(lg);
    manager.addComponent(descriptionComponent);

    manager.startupAllComponents();

    QVERIFY(!descriptionComponent->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldNotStartChildComponentsIfInitialiserReturnFalseForParentOne()
{
    // A <- B <- C
    TestDescriptionComponent *p_componentA = new TestDescriptionComponent("A");
    p_componentA->setAvailability(IComponent::Disabled);
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;

    ComponentManager manager(lg);
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentA);
    manager.addComponent(p_componentC);

    manager.startupAllComponents();

    QVERIFY(!p_componentA->started());
    QVERIFY(!p_componentB->started());
    QVERIFY(!p_componentC->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupAllComponents_shouldStartOrphanComponentIfParentAppeared()
{
    // A <- B,  C
    MockComponent *p_componentA = createComponent("A");
    MockComponent *p_componentC = createComponent("C");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 1); // B is orphan
    QVERIFY(!p_componentB->started());

    manager.addComponent(p_componentA);
    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 0);
    QVERIFY(p_componentB->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupComponents_shouldStartOrphanComponentsWhenParentsAppeared()
{
    // A <- B,  C
    MockComponent *p_componentA = createComponent("A");
    MockComponent *p_componentC = createComponent("C");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 1); // B is orphan
    QVERIFY(!p_componentB->started());

    QList<IComponent *> comps;
    comps.push_back(p_componentA);
    manager.addComponent(p_componentA);
    manager.startupComponents(comps);

    QCOMPARE(manager.orphanComponents().size(), 0);
    QVERIFY(p_componentB->started());
}

//------------------------------------------------------------------------------
void ComponentManagerTest::startupComponents_shouldNotStartOrphanComponentsWhenOtherParentsAppeared()
{
    // A <- B,  C, D
    MockComponent *p_componentD = createComponent("D");
    MockComponent *p_componentC = createComponent("C");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;

    MockComponentInitialiser *initialiser = new MockComponentInitialiser();
    ComponentManager manager(initialiser, lg);
    manager.addComponent(p_componentB);
    manager.addComponent(p_componentC);

    manager.startupAllComponents();

    QCOMPARE(manager.orphanComponents().size(), 1); // B is orphan
    QVERIFY(!p_componentB->started());

    QList<IComponent *> comps;
    comps.push_back(p_componentD);
    manager.addComponent(p_componentD);
    manager.startupComponents(comps);

    // B is still orphan because it's parent was not added
    QCOMPARE(manager.orphanComponents().size(), 1);
    QVERIFY(!p_componentB->started());
}

//------------------------------------------------------------------------------

