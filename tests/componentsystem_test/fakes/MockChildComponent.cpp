#include "MockChildComponent.h"

#include <carousel/componentsystem/ComponentDefinition.h>

//------------------------------------------------------------------------------
MockChildComponent::MockChildComponent(const QString &name)
    : BaseComponent(name)
{
}

//------------------------------------------------------------------------------
ParentDefinitions &MockChildComponent::parents()
{
    return const_cast<ParentDefinitions &>(definition()->parents());
}

//------------------------------------------------------------------------------
const ParentDefinitions &MockChildComponent::parents() const
{
    return definition()->parents();
}

//------------------------------------------------------------------------------
bool MockChildComponent::onStartup(IServiceLocator *)
{
    emit whenStarted(name());
    return true;
}

//------------------------------------------------------------------------------
void MockChildComponent::onShutdown()
{
    emit whenShutdown(name());
}

//------------------------------------------------------------------------------
