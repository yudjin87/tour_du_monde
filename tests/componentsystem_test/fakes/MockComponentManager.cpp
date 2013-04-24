#include "MockComponentManager.h"

#include <logging/NullLogger.h>

//------------------------------------------------------------------------------
MockComponentManager::MockComponentManager(ILogger &log, QObject *parent)
    : ComponentManager(log, parent)
    , callCheck(false)
{
}

//------------------------------------------------------------------------------
MockComponentManager::MockComponentManager(IComponentInitialiser *initializer, ILogger &log, QObject *parent)
    : ComponentManager(initializer, log, parent)
    , callCheck(false)
{
}

//------------------------------------------------------------------------------
MockComponentManager::MockComponentManager(IComponentDependencies *dependencies, ILogger &log, QObject *parent)
    : ComponentManager(dependencies, log, parent)
    , callCheck(false)
{
}

//------------------------------------------------------------------------------
MockComponentManager::MockComponentManager(IComponentDependencies *dependencies, IComponentInitialiser *initializer, ILogger &log, QObject *parent)
    : ComponentManager(dependencies, initializer, log, parent)
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
bool MockComponentManager::startCheckedComponent(IComponent *ip_component)
{
    m_startupComponents.push_back(ip_component);
    return ComponentManager::startCheckedComponent(ip_component);
}

//------------------------------------------------------------------------------
void MockComponentManager::shutdownCheckedComponent(IComponent *ip_component)
{
    m_shutdownComponents.push_back(ip_component);
    return ComponentManager::shutdownCheckedComponent(ip_component);
}

//------------------------------------------------------------------------------
