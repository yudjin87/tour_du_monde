#pragma once
#include <QtCore/QObject>

class DependencySolverTest: public QObject
{
    Q_OBJECT
public:
    DependencySolverTest();

private Q_SLOTS:
    void cannotAddEmptyComponentName();
    void cannotAddDependencyWithoutAddingComponent();
    void canAddComponentDepedency();
    void canSolveAcyclicDependencies();
    void failsWithSimpleCycle();
    void canSolveBundle();
    void canSolveComplexBundleWithMissingComponents();
    void failsWithComplexCycle();
    void shouldFillMissingComponents();
    void shouldFillOrphanComponents();

    // regressions
    void iterationWithReferenceLeadsToBug();
};

