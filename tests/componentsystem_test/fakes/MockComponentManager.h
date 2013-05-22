#ifndef MOCKCOMPONENTMANAGER_H
#define MOCKCOMPONENTMANAGER_H

#include <componentsystem/ComponentManager.h>

class MockComponentManager : public ComponentManager
{
    Q_OBJECT
public:
    MockComponentManager(IServiceLocator *serviceLocator, QObject *parent = nullptr);
    MockComponentManager(IServiceLocator *serviceLocator, IComponentDependencies *dependencies, QObject *parent = nullptr);

    DependenciesSolvingResult check();

    bool startCheckedComponent(IComponent *component);
    bool enableAndStartComponent(IComponent *component);
    void shutdownCheckedComponent(IComponent *component);

public:
    bool callCheck;

    QList<IComponent *> m_startupComponents;
    QList<IComponent *> m_shutdownComponents;
};

#endif // MOCKCOMPONENTMANAGER_H
