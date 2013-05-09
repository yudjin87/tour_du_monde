#include "MockComponentManager.h"

//------------------------------------------------------------------------------
MockComponentManager::MockComponentManager(QObject *parent)
    : ComponentManager(parent)
    , callCheck(false)
{
}

//------------------------------------------------------------------------------
MockComponentManager::MockComponentManager(IComponentDependencies *dependencies, QObject *parent)
    : ComponentManager(dependencies, parent)
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
