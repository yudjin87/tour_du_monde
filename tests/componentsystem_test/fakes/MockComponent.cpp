#include "MockComponent.h"

#include <componentsystem/ComponentDefinition.h>

//------------------------------------------------------------------------------
MockComponent::MockComponent(const QString &i_name, bool isBuiltIn)
    : BaseComponent(new ComponentDefinition(i_name, isBuiltIn))
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
void MockComponent::loadAvailability()
{
    BaseComponent::loadAvailability();
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
