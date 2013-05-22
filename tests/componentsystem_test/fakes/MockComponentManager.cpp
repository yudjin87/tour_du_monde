#include "MockComponentManager.h"

//------------------------------------------------------------------------------
MockComponentManager::MockComponentManager(IServiceLocator *serviceLocator, QObject *parent)
    : ComponentManager(serviceLocator, parent)
    , callCheck(false)
{
}

//------------------------------------------------------------------------------
MockComponentManager::MockComponentManager(IServiceLocator *serviceLocator, IComponentDependencies *dependencies, QObject *parent)
    : ComponentManager(serviceLocator, dependencies, parent)
    , callCheck(false)
{
}

//------------------------------------------------------------------------------
DependenciesSolvingResult MockComponentManager::check()
{
    callCheck = true;
    return DependenciesSolvingResult();
}

//------------------------------------------------------------------------------
bool MockComponentManager::startCheckedComponent(IComponent *component)
{
    m_startupComponents.push_back(component);
    return ComponentManager::startCheckedComponent(component);
}

//------------------------------------------------------------------------------
bool MockComponentManager::enableAndStartComponent(IComponent *component)
{
    m_startupComponents.push_back(component);
    return ComponentManager::enableAndStartComponent(component);
}

//------------------------------------------------------------------------------
void MockComponentManager::shutdownCheckedComponent(IComponent *component)
{
    m_shutdownComponents.push_back(component);
    return ComponentManager::shutdownCheckedComponent(component);
}

//------------------------------------------------------------------------------
