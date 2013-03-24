#include "MockComponent.h"

#include <componentsystem/ComponentDefinition.h>

//------------------------------------------------------------------------------
MockComponent::MockComponent(bool i_returnValue)
    : BaseComponent("MockComponent")
    , mp_initData(nullptr)
    , m_returnValue(i_returnValue)
    , mp_registrator(nullptr)
{
}

//------------------------------------------------------------------------------
MockComponent::MockComponent(const QString &i_name)
    : BaseComponent(i_name)
    , mp_initData(nullptr)
    , m_returnValue(true)
    , mp_registrator(nullptr)
{
}

//------------------------------------------------------------------------------
MockComponent::~MockComponent()
{
}

//------------------------------------------------------------------------------
QObject *MockComponent::data() const
{
    return mp_initData;
}

//------------------------------------------------------------------------------
void MockComponent::setRegistrator(QList<MockComponent *> *ip_registrator)
{
    mp_registrator = ip_registrator;
}

//------------------------------------------------------------------------------
bool MockComponent::_onStartup(QObject *ip_initData)
{
    mp_initData = ip_initData;
    emit whenStarted(name());
    return m_returnValue;
}

//------------------------------------------------------------------------------
void MockComponent::_onShutdown()
{
    if (mp_registrator != nullptr)
        mp_registrator->push_back(this);

    emit whenShutdown(name());
}


//------------------------------------------------------------------------------
