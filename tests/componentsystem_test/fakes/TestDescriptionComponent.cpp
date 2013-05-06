#include "TestDescriptionComponent.h"

//------------------------------------------------------------------------------
TestDescriptionComponent::TestDescriptionComponent()
    : BaseComponent("TestDescriptionComponent")
    , m_definition()
    , startUpResult(true)
{
}

//------------------------------------------------------------------------------
TestDescriptionComponent::TestDescriptionComponent(const QString &name)
    : BaseComponent(name)
    , m_definition()
    , startUpResult(true)
{
}

//------------------------------------------------------------------------------
bool TestDescriptionComponent::_onStartup(QObject *)
{
    emit whenStarted(name());
    return startUpResult;
}

//------------------------------------------------------------------------------
ComponentDefinition *TestDescriptionComponent::definition() const
{
    return &const_cast<TestDescriptionComponent *>(this)->m_definition;
}

//------------------------------------------------------------------------------
