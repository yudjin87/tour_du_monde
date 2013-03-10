#include "MockChildComponent.h"

#include <componentsystem/ComponentDefinition.h>

//------------------------------------------------------------------------------
MockChildComponent::MockChildComponent()
    : BaseComponent("MockChildComponent")
    , mp_def(nullptr)
{
    mp_def = new ComponentDefinition(this);
}

//------------------------------------------------------------------------------
MockChildComponent::~MockChildComponent()
{
    delete mp_def;
    mp_def = nullptr;
}

//------------------------------------------------------------------------------
IComponentDefinition *MockChildComponent::definition() const
{
    return mp_def;
}

//------------------------------------------------------------------------------
QStringList &MockChildComponent::parents()
{
    return const_cast<QStringList &>(mp_def->parents());
}

//------------------------------------------------------------------------------
const QStringList &MockChildComponent::parents() const
{
    return mp_def->parents();
}

//------------------------------------------------------------------------------
void MockChildComponent::setName(const QString &i_name)
{
    m_name = i_name;
    setObjectName(m_name);
}

//------------------------------------------------------------------------------
bool MockChildComponent::_onStartup(QObject *)
{
    emit whenStarted(m_name);
    return true;
}

//------------------------------------------------------------------------------
void MockChildComponent::_onShutdown()
{
    emit whenShutdown(m_name);
}

//------------------------------------------------------------------------------
