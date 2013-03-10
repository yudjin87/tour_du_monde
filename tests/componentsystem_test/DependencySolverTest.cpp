#include "DependencySolverTest.h"

#include <componentsystem/IComponent.h>
#include <componentsystem/DependencySolver.h>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
DependencySolverTest::DependencySolverTest()
{
}

//------------------------------------------------------------------------------
void DependencySolverTest::cannotAddEmptyComponentName()
{
    DependencySolver solver;
    solver.addComponent(QString());
    QCOMPARE(solver.componentsCount(), 0);
}

//------------------------------------------------------------------------------
void DependencySolverTest::cannotAddDependencyWithoutAddingComponent()
{
    DependencySolver solver;
    solver.addDependency("Child", "Parent");
    QCOMPARE(solver.componentsCount(), 0);
}

//------------------------------------------------------------------------------
void DependencySolverTest::canAddComponentDepedency()
{
    DependencySolver solver;
    solver.addComponent("Parent");
    solver.addComponent("Child");
    solver.addDependency("Child", "Parent");

    QCOMPARE(solver.componentsCount(), 2);
}

//------------------------------------------------------------------------------
void DependencySolverTest::canSolveAcyclicDependencies()
{
    DependencySolver solver;
    solver.addComponent("Child");
    solver.addComponent("Parent");
    solver.addDependency("Child", "Parent");

    QStringList ordered; QStringList orphans; QStringList missing;
    bool result = solver.solve(ordered, orphans, missing);

    QVERIFY(result);
    QCOMPARE(ordered.size(), 2);
    QCOMPARE(missing.size(), 0);
    QCOMPARE(orphans.size(), 0);
    QCOMPARE(QString("Parent"), ordered[0]);
    QCOMPARE(QString("Child"), ordered[1]);
}

//------------------------------------------------------------------------------
void DependencySolverTest::failsWithSimpleCycle()
{
    DependencySolver solver;
    solver.addComponent("Child");
    solver.addDependency("Child", "Child");
    QStringList ordered; QStringList orphans; QStringList missing;
    QCOMPARE(solver.solve(ordered, orphans, missing), false);

    QCOMPARE(ordered.size(), 0);
    QCOMPARE(missing.size(), 0);
    QCOMPARE(orphans.size(), 0);
}

//------------------------------------------------------------------------------
void DependencySolverTest::canSolveBundle()
{
    DependencySolver solver;
    solver.addComponent("ComA");
    solver.addComponent("ComB");
    solver.addComponent("ComC");
    solver.addComponent("ComD");
    solver.addComponent("ComE");
    solver.addComponent("ComF");
    solver.addDependency("ComC", "ComB");
    solver.addDependency("ComB", "ComA");
    solver.addDependency("ComE", "ComD");

    QStringList ordered; QStringList orphans; QStringList missing;
    bool result = solver.solve(ordered, orphans, missing);

    QVERIFY(result);

    QCOMPARE(ordered.size(), 6);
    QCOMPARE(missing.size(), 0);
    QCOMPARE(orphans.size(), 0);

    QVERIFY(ordered.indexOf("ComA") < ordered.indexOf("ComB"));
    QVERIFY(ordered.indexOf("ComB") < ordered.indexOf("ComC"));
    QVERIFY(ordered.indexOf("ComD") < ordered.indexOf("ComE"));
}

//------------------------------------------------------------------------------
void DependencySolverTest::failsWithComplexCycle()
{
    DependencySolver solver;
    solver.addComponent("ComA");
    solver.addComponent("ComB");
    solver.addComponent("ComC");
    solver.addComponent("ComD");
    solver.addComponent("ComE");
    solver.addComponent("ComF");
    solver.addDependency("ComC", "ComB");
    solver.addDependency("ComB", "ComA");
    solver.addDependency("ComE", "ComD");
    solver.addDependency("ComE", "ComC");
    solver.addDependency("ComF", "ComE");
    solver.addDependency("ComD", "ComF");
    solver.addDependency("ComB", "ComD");

    QStringList ordered; QStringList orphans; QStringList missing;
    QCOMPARE(solver.solve(ordered, orphans, missing), false);

    QCOMPARE(ordered.size(), 0);
    QCOMPARE(missing.size(), 0);
    QCOMPARE(orphans.size(), 0);
}

//------------------------------------------------------------------------------
void DependencySolverTest::shouldFillMissingComponents()
{
    DependencySolver solver;
    solver.addComponent("Child");
    solver.addComponent("Component");
    solver.addDependency("Child", "AbsentParent");
    QStringList ordered; QStringList orphans; QStringList missing;
    bool result = solver.solve(ordered, orphans, missing);

    QVERIFY(result);

    QCOMPARE(missing.size(), 1);
    QCOMPARE(missing[0], QString("AbsentParent"));

    QCOMPARE(ordered.size(), 1);
    QCOMPARE(orphans.size(), 1);
}

//------------------------------------------------------------------------------
void DependencySolverTest::shouldFillOrphanComponents()
{
    DependencySolver solver;
    solver.addComponent("Child");
    solver.addComponent("Component");
    solver.addDependency("Child", "AbsentParent");
    QStringList ordered; QStringList orphans; QStringList missing;
    bool result = solver.solve(ordered, orphans, missing);

    QVERIFY(result);

    QCOMPARE(missing.size(), 1);
    QCOMPARE(ordered.size(), 1);

    QCOMPARE(orphans.size(), 1);
    QCOMPARE(orphans[0], QString("Child"));
}

//------------------------------------------------------------------------------

