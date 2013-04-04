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

#include <componentsystem/ComponentDependencies.h>
#include <componentsystem/DependenciesSolvingResult.h>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
ComponentDependenciesTest::ComponentDependenciesTest(QObject *parent)
    : QObject(parent)
{
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldAddComponent()
{
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createComponent("B");

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentB);

    QCOMPARE(dependencies.components().count(), 2);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldnotAddExistedComponent()
{
    IComponent *p_componentA = createComponent("A");
    IComponentPtr p_componentAagain(createComponent("A"));
    IComponent *p_componentB = createComponent("B");

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentB);
    dependencies.addComponent(p_componentAagain.get());

    QCOMPARE(dependencies.components().count(), 2);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldNotAddNullPointer()
{
    IComponent *p_componentA = createComponent("A");

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(nullptr);

    QCOMPARE(dependencies.components().count(), 1);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldFindComponentByName()
{
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createComponent("B");

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentB);

    IComponent *p_foundCom = dependencies.componentByName("B");
    QCOMPARE(p_foundCom, p_componentB);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldReturnResultWithCiclycFlag()
{
    // A <- B <- C <- A
    IComponent *p_componentA = createParentComponent("A", "C");
    IComponent *p_componentB = createParentComponent("B", "A");
    IComponent *p_componentC = createParentComponent("C", "B");

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentB);
    dependencies.addComponent(p_componentC);

    DependenciesSolvingResult result = dependencies.orderedComponents();
    QVERIFY(result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldGetParentsForComponent()
{
    // A <- B
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentB);

    DependenciesSolvingResult result = dependencies.getParentComponents(p_componentB);
    QList<IComponent *> components = result.ordered();

    QCOMPARE(components.size(), 1);
    QCOMPARE(p_componentA->name(), components[0]->name());
    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldGetDependingsForComponent()
{
    // A <- B
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentB);

    DependenciesSolvingResult result = dependencies.getChildComponents(p_componentA);
    QList<IComponent *> components = result.ordered();

    QCOMPARE(components.size(), 1);
    QCOMPARE(p_componentB->name(), components[0]->name());
    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithChild()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *p_componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *p_componentE = createParentComponent("E", "C"); //dependent from C;

    ComponentDependencies dependencies;
    // Add the components in random order
    dependencies.addComponent(p_componentB);
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentD);
    dependencies.addComponent(p_componentE);
    dependencies.addComponent(p_componentC);

    DependenciesSolvingResult result = dependencies.completeListWithChild(p_componentC);
    QList<IComponent *> components = result.ordered();

    QCOMPARE(components.size(), 3); // A, B and C components should be passed

    QVERIFY(components.indexOf(p_componentA) < components.indexOf(p_componentB));
    QVERIFY(components.indexOf(p_componentB) < components.indexOf(p_componentC));

    // E and D components should not been passed
    QCOMPARE(components.contains(p_componentD), QBool(false));
    QCOMPARE(components.contains(p_componentE), QBool(false));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithParentsForOneComponent()
{
    IComponent *p_componentA = createComponent("A");

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);

    QList<IComponent *> parents;
    parents.push_back(p_componentA);

    DependenciesSolvingResult result = dependencies.completeListWithParents(parents);
    QList<IComponent *> childrenAndParent = result.ordered();

    QCOMPARE(childrenAndParent.size(), 1);
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithTheirChildren()
{
    // A <- B <- C
    IComponent *p_componentA = createComponent("A");
    IComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    IComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    IComponentPtr p_independentComponent(createComponent("independentComponent"));

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentB);
    dependencies.addComponent(p_componentC);
    dependencies.addComponent(p_independentComponent.get());

    QList<IComponent *> children;
    children.push_back(p_componentC);

    DependenciesSolvingResult result = dependencies.completeListWithChildren(children);
    QList<IComponent *> childrenAndParent = result.ordered();

    QCOMPARE(childrenAndParent.size(), 3);
    QVERIFY(childrenAndParent.contains(p_componentA));
    QVERIFY(childrenAndParent.contains(p_componentB));
    QVERIFY(childrenAndParent.contains(p_componentC));
    QVERIFY(!childrenAndParent.contains(p_independentComponent.get()));

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
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;

    MockChildComponent *p_componentD = createParentComponent("D", "B", "C"); //dependent from B & C;
    MockChildComponent *p_componentE = createParentComponent("E", "A", "C"); //dependent from A & C;


    ComponentDependencies dependencies;

    // Add the components in random order
    dependencies.addComponent(p_componentB);
    dependencies.addComponent(p_componentC);
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentD);
    dependencies.addComponent(p_componentE);

    DependenciesSolvingResult result = dependencies.orderedComponents();
    QList<IComponent *> comps = result.ordered();

    QCOMPARE(comps.size(), 5);

    QVERIFY(comps.indexOf(p_componentA) < comps.indexOf(p_componentB));
    QVERIFY(comps.indexOf(p_componentB) < comps.indexOf(p_componentC));
    QVERIFY(comps.indexOf(p_componentC) < comps.indexOf(p_componentD));
    QVERIFY(comps.indexOf(p_componentC) < comps.indexOf(p_componentE));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithTheirParents()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *p_componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *p_componentE = createParentComponent("E", "C"); //dependent from C;
    IComponentPtr p_independentComponent(createComponent("independentComponent"));

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentB);
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentD);
    dependencies.addComponent(p_componentE);
    dependencies.addComponent(p_componentC);
    dependencies.addComponent(p_independentComponent.get());

    QList<IComponent *> parents;
    parents.push_back(p_componentC);

    DependenciesSolvingResult result = dependencies.completeListWithParents(parents);
    QList<IComponent *> childrenAndParent = result.ordered();

    QCOMPARE(childrenAndParent.size(), 3); // C, D and E components should be found

    QVERIFY(childrenAndParent.contains(p_componentD));
    QVERIFY(childrenAndParent.contains(p_componentE));
    QVERIFY(childrenAndParent.contains(p_componentC));

    QVERIFY(childrenAndParent.indexOf(p_componentE) < childrenAndParent.indexOf(p_componentC));
    QVERIFY(childrenAndParent.indexOf(p_componentD) < childrenAndParent.indexOf(p_componentC));

    // A and B components should not been passed
    QCOMPARE(childrenAndParent.contains(p_componentA), QBool(false));
    QCOMPARE(childrenAndParent.contains(p_componentB), QBool(false));
    QCOMPARE(childrenAndParent.contains(p_independentComponent.get()), QBool(false));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithFullParents()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *p_componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *p_componentE = createParentComponent("E", "C"); //dependent from C;

    ComponentDependencies dependencies;
    dependencies.addComponent(p_componentB);
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentD);
    dependencies.addComponent(p_componentE);
    dependencies.addComponent(p_componentC);

    DependenciesSolvingResult result = dependencies.completeListWithParents(dependencies.components().toList());
    QList<IComponent *> comps = result.ordered();

    QCOMPARE(comps.size(), 5);

    QVERIFY(comps.indexOf(p_componentD) < comps.indexOf(p_componentC));
    QVERIFY(comps.indexOf(p_componentE) < comps.indexOf(p_componentC));
    QVERIFY(comps.indexOf(p_componentC) < comps.indexOf(p_componentB));
    QVERIFY(comps.indexOf(p_componentB) < comps.indexOf(p_componentA));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------
void ComponentDependenciesTest::shouldCompleteListWithTheirParent()
{
    // A <- B <- C <- D,    C <- E
    MockComponent *p_componentA = createComponent("A");
    MockChildComponent *p_componentB = createParentComponent("B", "A"); //dependent from A;
    MockChildComponent *p_componentC = createParentComponent("C", "B"); //dependent from B;
    MockChildComponent *p_componentD = createParentComponent("D", "C"); //dependent from C;
    MockChildComponent *p_componentE = createParentComponent("E", "C"); //dependent from C;

    ComponentDependencies dependencies;
    // Add the components in random order
    dependencies.addComponent(p_componentB);
    dependencies.addComponent(p_componentA);
    dependencies.addComponent(p_componentD);
    dependencies.addComponent(p_componentE);
    dependencies.addComponent(p_componentC);

    DependenciesSolvingResult result = dependencies.completeListWithParent(p_componentC);
    QList<IComponent *> comps = result.ordered();

    QCOMPARE(comps.size(), 3); // C, D and E components should be passed
    QVERIFY(comps.indexOf(p_componentE) < comps.indexOf(p_componentC));
    QVERIFY(comps.indexOf(p_componentD) < comps.indexOf(p_componentC));

    // A and B components should not been passed
    QCOMPARE(comps.contains(p_componentA), QBool(false));
    QCOMPARE(comps.contains(p_componentB), QBool(false));

    QVERIFY(!result.hasCyclicDependencies());
}

//------------------------------------------------------------------------------

