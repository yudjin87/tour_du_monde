#include "MockChildComponent.h"

#include <componentsystem/ComponentDefinition.h>

//------------------------------------------------------------------------------
MockChildComponent::MockChildComponent(const QString &name)
    : BaseComponent(name)
{
}

//------------------------------------------------------------------------------
QStringList &MockChildComponent::parents()
{
    return const_cast<QStringList &>(definition()->parents());
}

//------------------------------------------------------------------------------
const QStringList &MockChildComponent::parents() const
{
    return definition()->parents();
}

//------------------------------------------------------------------------------
bool MockChildComponent::_onStartup(QObject *)
{
    emit whenStarted(name());
    return true;
}

//------------------------------------------------------------------------------
void MockChildComponent::_onShutdown()
{
    emit whenShutdown(name());
}

//------------------------------------------------------------------------------
