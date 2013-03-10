#ifndef MOCKCOMPONENTMANAGER_H
#define MOCKCOMPONENTMANAGER_H

#include <componentsystem/ComponentManager.h>

class MockComponentManager : public ComponentManager
{
    Q_OBJECT
public:
    MockComponentManager(ILogger &log, QObject *parent = nullptr);
    MockComponentManager(IComponentInitialiser *initializer, ILogger &log, QObject *parent = nullptr);
    MockComponentManager(IComponentDependencies *dependencies, ILogger &log, QObject *parent = nullptr);
    MockComponentManager(IComponentDependencies *dependencies, IComponentInitialiser *initializer, ILogger &log, QObject *parent = nullptr);

    DependenciesSolvingResult check();

public:
    bool callCheck;
};

#endif // MOCKCOMPONENTMANAGER_H
