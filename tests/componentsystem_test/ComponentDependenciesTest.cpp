/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "ComponentDependenciesTest.h"

#include "fakes/MockChildComponent.h"
#include "fakes/MockComponent.h"
#include "fakes/TestDescriptionComponent.h"
#include "Utils.h"

#include <carousel/componentsystem/ComponentDependencies.h>
#include <carousel/componentsystem/DependenciesSolvingResult.h>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
ComponentDependenciesTest::ComponentDependenciesTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldAddComponent()
{
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createComponent("B");

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentB);

    QCOMPARE(dependencies.components().count(), 2);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldnotAddExistedComponent()
{
    IComponent *componentA = createComponent("A");
    IComponentPtr componentAagain(createComponent("A"));
    IComponent *componentB = createComponent("B");

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentB);
    dependencies.addComponent(componentAagain.get());

    QCOMPARE(dependencies.components().count(), 2);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldNotAddNullPointer()
{
    IComponent *componentA = createComponent("A");

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);
    dependencies.addComponent(nullptr);

    QCOMPARE(dependencies.components().count(), 1);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldFindComponentByName()
{
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createComponent("B");

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentB);

    IComponent *foundCom = dependencies.componentByName("B");
    QCOMPARE(foundCom, componentB);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldReturnResultWithCiclycFlag()
{
    // A <- B <- C <- A
    IComponent *componentA = createParentComponent("A", "C");
    IComponent *componentB = createParentComponent("B", "A");
    IComponent *componentC = createParentComponent("C", "B");

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentB);
    dependencies.addComponent(componentC);

    DependenciesSolvingResult result = dependencies.orderedComponents();
    QVERIFY(result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldGetParentsForComponent()
{
    // A <- B
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentB);

    DependenciesSolvingResult result = dependencies.getParentComponents(componentB);
    QList<IComponent *> components = result.ordered();

    QCOMPARE(components.size(), 1);
    QCOMPARE(componentA->name(), components[0]->name());
    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldGetDependingsForComponent()
{
    // A <- B
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentB);

    DependenciesSolvingResult result = dependencies.getChildComponents(componentA);
    QList<IComponent *> components = result.ordered();

    QCOMPARE(components.size(), 1);
    QCOMPARE(componentB->name(), components[0]->name());
    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithChild()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *componentE = createParentComponent("E", "C"); //dependent from C;

    ComponentDependencies dependencies;
    // Add the components in random order
    dependencies.addComponent(componentB);
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentD);
    dependencies.addComponent(componentE);
    dependencies.addComponent(componentC);

    DependenciesSolvingResult result = dependencies.completeListWithChild(componentC);
    QList<IComponent *> components = result.ordered();

    QCOMPARE(components.size(), 3); // A, B and C components should be passed

    QVERIFY(components.indexOf(componentA) < components.indexOf(componentB));
    QVERIFY(components.indexOf(componentB) < components.indexOf(componentC));

    // E and D components should not been passed
    QCOMPARE(components.contains(componentD), false);
    QCOMPARE(components.contains(componentE), false);

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithParentsForOneComponent()
{
    IComponent *componentA = createComponent("A");

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);

    QList<IComponent *> parents;
    parents.push_back(componentA);

    DependenciesSolvingResult result = dependencies.completeListWithParents(parents);
    QList<IComponent *> childrenAndParent = result.ordered();

    QCOMPARE(childrenAndParent.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithTheirChildren()
{
    // A <- B <- C
    IComponent *componentA = createComponent("A");
    IComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    IComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    IComponentPtr independentComponent(createComponent("independentComponent"));

    ComponentDependencies dependencies;
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentB);
    dependencies.addComponent(componentC);
    dependencies.addComponent(independentComponent.get());

    QList<IComponent *> children;
    children.push_back(componentC);

    DependenciesSolvingResult result = dependencies.completeListWithChildren(children);
    QList<IComponent *> childrenAndParent = result.ordered();

    QCOMPARE(childrenAndParent.size(), 3);
    QVERIFY(childrenAndParent.contains(componentA));
    QVERIFY(childrenAndParent.contains(componentB));
    QVERIFY(childrenAndParent.contains(componentC));
    QVERIFY(!childrenAndParent.contains(independentComponent.get()));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteOrderedComponents()
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


    ComponentDependencies dependencies;

    // Add the components in random order
    dependencies.addComponent(componentB);
    dependencies.addComponent(componentC);
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentD);
    dependencies.addComponent(componentE);

    DependenciesSolvingResult result = dependencies.orderedComponents();
    QList<IComponent *> comps = result.ordered();

    QCOMPARE(comps.size(), 5);

    QVERIFY(comps.indexOf(componentA) < comps.indexOf(componentB));
    QVERIFY(comps.indexOf(componentB) < comps.indexOf(componentC));
    QVERIFY(comps.indexOf(componentC) < comps.indexOf(componentD));
    QVERIFY(comps.indexOf(componentC) < comps.indexOf(componentE));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithTheirParents()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *componentE = createParentComponent("E", "C"); //dependent from C;
    IComponentPtr independentComponent(createComponent("independentComponent"));

    ComponentDependencies dependencies;
    dependencies.addComponent(componentB);
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentD);
    dependencies.addComponent(componentE);
    dependencies.addComponent(componentC);
    dependencies.addComponent(independentComponent.get());

    QList<IComponent *> parents;
    parents.push_back(componentC);

    DependenciesSolvingResult result = dependencies.completeListWithParents(parents);
    QList<IComponent *> childrenAndParent = result.ordered();

    QCOMPARE(childrenAndParent.size(), 3); // C, D and E components should be found

    QVERIFY(childrenAndParent.contains(componentD));
    QVERIFY(childrenAndParent.contains(componentE));
    QVERIFY(childrenAndParent.contains(componentC));

    QVERIFY(childrenAndParent.indexOf(componentE) < childrenAndParent.indexOf(componentC));
    QVERIFY(childrenAndParent.indexOf(componentD) < childrenAndParent.indexOf(componentC));

    // A and B components should not been passed
    QCOMPARE(childrenAndParent.contains(componentA), false);
    QCOMPARE(childrenAndParent.contains(componentB), false);
    QCOMPARE(childrenAndParent.contains(independentComponent.get()), false);

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithFullParents()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *componentE = createParentComponent("E", "C"); //dependent from C;

    ComponentDependencies dependencies;
    dependencies.addComponent(componentB);
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentD);
    dependencies.addComponent(componentE);
    dependencies.addComponent(componentC);

    DependenciesSolvingResult result = dependencies.completeListWithParents(dependencies.components().toList());
    QList<IComponent *> comps = result.ordered();

    QCOMPARE(comps.size(), 5);

    QVERIFY(comps.indexOf(componentD) < comps.indexOf(componentC));
    QVERIFY(comps.indexOf(componentE) < comps.indexOf(componentC));
    QVERIFY(comps.indexOf(componentC) < comps.indexOf(componentB));
    QVERIFY(comps.indexOf(componentB) < comps.indexOf(componentA));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithParentsTransitively()
{
    // Zero <- C <- A <- N


    MockComponent *componentZero = createComponent("Zero");
    MockChildComponent *componentC = createParentComponent("C", "Zero"); //dependent from Zero;
    MockChildComponent *componentA = createParentComponent("A", "C");    //dependent from C;
    MockChildComponent *componentN = createParentComponent("N", "A");    //dependent from A;


    ComponentDependencies dependencies;
    dependencies.addComponent(componentC);
    dependencies.addComponent(componentZero);
    dependencies.addComponent(componentN);
    dependencies.addComponent(componentA);

    QList<IComponent *> parents;
    parents.push_back(componentC);

    DependenciesSolvingResult result = dependencies.completeListWithParents(parents);
    QList<IComponent *> comps = result.ordered();

    QCOMPARE(comps.size(), 3); // C, N and A

    // Zero should not been passed
    QCOMPARE(comps.contains(componentZero), false);

    QVERIFY(comps.indexOf(componentN) < comps.indexOf(componentA));
    QVERIFY(comps.indexOf(componentA) < comps.indexOf(componentC));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldNotAddExtraParentsToCompletedList()
{
    // The C should not be added when we try to complete with A
    //
    // Zero <- C <- A <- N
    //         ^    ^    │
    //         └────┴────┘

    MockComponent *componentZero = createComponent("Zero");
    MockChildComponent *componentC = createParentComponent("C", "Zero");   //dependent from Zero;
    MockChildComponent *componentA = createParentComponent("A", "C");      //dependent from C;
    MockChildComponent *componentN = createParentComponent("N", "C", "A"); //dependent from C and A;


    ComponentDependencies dependencies;
    dependencies.addComponent(componentC);
    dependencies.addComponent(componentZero);
    dependencies.addComponent(componentN);
    dependencies.addComponent(componentA);

    QList<IComponent *> parents;
    parents.push_back(componentA);

    DependenciesSolvingResult result = dependencies.completeListWithParents(parents);
    QList<IComponent *> comps = result.ordered();

    QCOMPARE(comps.size(), 2); // Only N and A

    // Zero and C components should not been passed
    QCOMPARE(comps.contains(componentZero), false);
    QCOMPARE(comps.contains(componentC), false);

    QVERIFY(comps.indexOf(componentN) < comps.indexOf(componentA));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithTheirParent()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *componentA = createComponent("A");
    MockChildComponent *componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *componentE = createParentComponent("E", "C"); //dependent from C;

    ComponentDependencies dependencies;
    // Add the components in random order
    dependencies.addComponent(componentB);
    dependencies.addComponent(componentA);
    dependencies.addComponent(componentD);
    dependencies.addComponent(componentE);
    dependencies.addComponent(componentC);

    DependenciesSolvingResult result = dependencies.completeListWithParent(componentC);
    QList<IComponent *> comps = result.ordered();

    QCOMPARE(comps.size(), 3); // C, D and E components should be passed
    QVERIFY(comps.indexOf(componentE) < comps.indexOf(componentC));
    QVERIFY(comps.indexOf(componentD) < comps.indexOf(componentC));

    // A and B components should not been passed
    QCOMPARE(comps.contains(componentA), false);
    QCOMPARE(comps.contains(componentB), false);

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------

