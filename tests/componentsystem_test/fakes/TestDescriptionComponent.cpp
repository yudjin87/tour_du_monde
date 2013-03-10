#include "TestDescriptionComponent.h"

//------------------------------------------------------------------------------
TestDescriptionComponent::TestDescriptionComponent()
    : BaseComponent("TestDescriptionComponent")
    , m_definition()
{
}

//------------------------------------------------------------------------------
TestDescriptionComponent::TestDescriptionComponent(const QString &name)
    : BaseComponent(name)
    , m_definition()
{
}

//------------------------------------------------------------------------------
bool TestDescriptionComponent::_onStartup(QObject *)
{
    emit whenStarted(name());
    return true;
}

//------------------------------------------------------------------------------
IComponentDefinition *TestDescriptionComponent::definition() const
{
    return &const_cast<TestDescriptionComponent *>(this)->m_definition;
}

//------------------------------------------------------------------------------
