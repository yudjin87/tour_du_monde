#include "MockChildComponent.h"

#include <carousel/componentsystem/ComponentDefinition.h>

MockChildComponent::MockChildComponent(const QString &name)
    : BaseComponent(name)
{
}

MockChildComponent::MockChildComponent(const QString &name, int major_version, int minor_version, int build_version, int revision_version)
    : BaseComponent(name)
{
    setVersion(major_version, minor_version, build_version, revision_version);
}

ParentDefinitions &MockChildComponent::parents()
{
    return const_cast<ParentDefinitions &>(definition()->parents());
}

const ParentDefinitions &MockChildComponent::parents() const
{
    return definition()->parents();
}

bool MockChildComponent::onStartup(IServiceLocator *)
{
    emit whenStarted(name());
    return true;
}

void MockChildComponent::onShutdown()
{
    emit whenShutdown(name());
}

